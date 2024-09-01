#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/mod_devicetable.h>
#include "platform_data_special.h"
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/device.h>
#include "stm32mp157xxx.h"

struct stm32mp157 {
	unsigned int major;
	struct class *cls;
	struct device *dev;
	GPIO_TypeDef *gpio;
	unsigned int *rcc;
	unsigned int count;
	struct gpio_desc **get_gpio;
	struct resource *resource[10];
	struct Platform_data_spex *spex;
};
struct stm32mp157 *drv_led;

int drv_led_open(struct inode *ide, struct file *flp)
{
	int ret=0;
	return ret;
}
int drv_led_close(struct inode *ide, struct file *flp)
{
	int ret=0;
	return ret;
}
ssize_t drv_led_write(struct file *flp, const char __user *buf, size_t len, loff_t *flags)
{
	ssize_t ret=0;
	int i = 0;
	int led_status = 0;
	ret = copy_from_user(&led_status, buf, len);
	if(ret != 0)
	{
		printk("drv_led_copy_from_user_err\r\n");
		return ret;
	}
	if(led_status)
	{
		//open led
		for(i = 0;i< drv_led->count;i++)
		{
			gpiod_set_value(drv_led->get_gpio[i], 1);
		}
	}
	else
	{
		for(i = 0;i< drv_led->count;i++)
		{
			gpiod_set_value(drv_led->get_gpio[i], 0);
		}
	}
	
	return ret;
}

const struct file_operations led_fops={
	.open = drv_led_open,
	.release = drv_led_close,
	.write = drv_led_write,
};

int drv_led_probe(struct platform_device *pdv)
{
	int ret = 0,i;
	//char name_string[20];
	printk("-------%s------\r\n",__FUNCTION__);
	
	//1、实例化对象
	drv_led = kzalloc(sizeof(struct stm32mp157), GFP_KERNEL);
	if(IS_ERR(drv_led))
	{
		printk("kzalloc_err\r\n");
		ret = PTR_ERR(drv_led);
		return ret;
	}
	drv_led->spex = kzalloc(sizeof(struct Platform_data_spex), GFP_KERNEL);
	if(IS_ERR(drv_led->spex))
	{
		printk("spex_kzalloc_err\r\n");
		ret = PTR_ERR(drv_led->spex);
		goto spex_kzalloc_err;
	}
	of_property_read_u32_index(pdv->dev.of_node, "minum", 1, &drv_led->spex->minum);
	of_property_read_string(pdv->dev.of_node, "dev_name", &drv_led->spex->name);
	printk("name=%s\r\n",drv_led->spex->name);
	
	//2、申请设备号
	drv_led->major = register_chrdev(0,drv_led->spex->name, &led_fops);
	if(drv_led->major<0)
	{
		printk("register_chrdev_err\n");
		ret =drv_led->major;
		goto register_chrdev_err;
	}
	
	//3、创建类
	drv_led->cls = class_create(THIS_MODULE, drv_led->spex->name);
	if(IS_ERR(drv_led->cls))
	{
		printk("class_create_err\n");
		ret =PTR_ERR(drv_led->cls);
		goto class_create_err;
	}
	
	//4、创建设备节点
	drv_led->dev = device_create(drv_led->cls, NULL, MKDEV(drv_led->major, drv_led->spex->minum), NULL,drv_led->spex->name);
	if(IS_ERR(drv_led->dev))
	{
		printk("device_create_err\n");
		ret =PTR_ERR(drv_led->dev);
		goto device_create_err;
	}
	//获取设备树中GPIO的数量
	drv_led->count = gpiod_count(&pdv->dev,  "leds");
	if(drv_led->count < 0)
	{
		printk("gpiod_count_err\r\n");
	}
	printk("drv_led->count=%d\r\n",drv_led->count);
	drv_led->get_gpio = kzalloc(sizeof(struct gpio_desc *)*10, GFP_KERNEL);
	if(IS_ERR(drv_led->get_gpio))
	{
		printk("get_gpio_kzalloc_err\n");
		ret =PTR_ERR(drv_led->get_gpio);
		goto get_gpio_kzalloc_err;
	}
	//根gpio数量去获取标号
	for(i=0;i<drv_led->count;i++)
	{
		drv_led->get_gpio[i] = devm_gpiod_get_index(&pdv->dev,"leds",i,GPIOD_OUT_HIGH );
		//sprintf(name_string,"led%d",i);
		//gpio_request(drv_led->get_gpio[i], name_string);
		gpiod_direction_output(drv_led->get_gpio[i], 0);	
	}
	return ret;
get_gpio_kzalloc_err:
	device_destroy(drv_led->cls, MKDEV(drv_led->major, drv_led->spex->minum));
device_create_err:
	class_destroy(drv_led->cls);
class_create_err:
	unregister_chrdev(drv_led->major, drv_led->spex->name);
register_chrdev_err:
	kfree(drv_led);
spex_kzalloc_err:
	kfree(drv_led);
	return ret;


}
int drv_led_remove(struct platform_device *pdv)
{
	int ret = 0,i;
	printk("-------%s------\r\n",__FUNCTION__);
	for(i=0;i<drv_led->count;i++)
	{
		gpiod_set_value(drv_led->get_gpio[i], 0);
		//gpiod_put(drv_led->get_gpio[i]);
	}
	kfree(drv_led->get_gpio); 
	device_destroy(drv_led->cls, MKDEV(drv_led->major, drv_led->spex->minum));
	class_destroy(drv_led->cls);
	unregister_chrdev(drv_led->major, drv_led->spex->name);
	kfree(drv_led->spex);
	kfree(drv_led);
	return ret;
}

const struct of_device_id led_of_match_table[]={
	{ .compatible = "stm32mp157a_led" },

};
struct platform_driver led_drv={
	.probe = drv_led_probe,
	.remove = drv_led_remove,
	.driver = {
			.name = "led0",
			.of_match_table = led_of_match_table,
	},
};

static int __init drv_led_init(void)
{
	int ret=0;
	printk("-------%s------\r\n",__FUNCTION__);
	platform_driver_register(&led_drv);
	return ret;
}

static void __exit drv_led_exit(void)
{
	printk("-------%s------\r\n",__FUNCTION__);
	platform_driver_unregister(&led_drv);
}

module_init(drv_led_init);
module_exit(drv_led_exit);
MODULE_LICENSE("GPL");


