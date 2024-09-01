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
	unsigned int count;
	struct gpio_desc **get_gpio;
	struct resource *resource[10];
	struct Platform_data_spex *spex;
};
struct stm32mp157 *drv_fan;

int drv_fan_open(struct inode *ide, struct file *flp)
{
	int ret=0;
	return ret;
}
int drv_fan_close(struct inode *ide, struct file *flp)
{
	int ret=0;
	return ret;
}
ssize_t drv_fan_write(struct file *flp, const char __user *buf, size_t len, loff_t *flags)
{
	ssize_t ret=0;
	int fan_statu = 0;
	ret = copy_from_user(&fan_statu, buf, len);
	if(ret != 0)
	{
		printk("drv_fan_copy_from_user_err\r\n");
		return ret;
	}
	if(fan_statu)
	{
		//打开风扇
		gpiod_set_value(drv_fan->get_gpio[0], 1);
	}
	else
	{
		//关风扇
		gpiod_set_value(drv_fan->get_gpio[0], 0);
	}
	return ret;
}

const struct file_operations fan_fops={
	.open = drv_fan_open,
	.release = drv_fan_close,
	.write = drv_fan_write,
};

int drv_fan_probe(struct platform_device *pdv)
{
	int ret = 0,i;
	//char name_string[20];
	printk("-------%s------\r\n",__FUNCTION__);
	
	//1、实例化对象
	drv_fan = kzalloc(sizeof(struct stm32mp157), GFP_KERNEL);
	if(IS_ERR(drv_fan))
	{
		printk("kzalloc_err\r\n");
		ret = PTR_ERR(drv_fan);
		return ret;
	}
	drv_fan->spex = kzalloc(sizeof(struct Platform_data_spex), GFP_KERNEL);
	if(IS_ERR(drv_fan->spex))
	{
		printk("spex_kzalloc_err\r\n");
		ret = PTR_ERR(drv_fan->spex);
		goto spex_kzalloc_err;
	}
	of_property_read_u32_index(pdv->dev.of_node, "minum", 1, &drv_fan->spex->minum);
	of_property_read_string(pdv->dev.of_node, "dev_name", &drv_fan->spex->name);
	printk("name=%s\r\n",drv_fan->spex->name);
	
	//2、申请设备号
	drv_fan->major = register_chrdev(0,drv_fan->spex->name, &fan_fops);
	if(drv_fan->major<0)
	{
		printk("register_chrdev_err\n");
		ret =drv_fan->major;
		goto register_chrdev_err;
	}
	
	//3、创建类
	drv_fan->cls = class_create(THIS_MODULE, drv_fan->spex->name);
	if(IS_ERR(drv_fan->cls))
	{
		printk("class_create_err\n");
		ret =PTR_ERR(drv_fan->cls);
		goto class_create_err;
	}
	
	//4、创建设备节点
	drv_fan->dev = device_create(drv_fan->cls, NULL, MKDEV(drv_fan->major, drv_fan->spex->minum), NULL,drv_fan->spex->name);
	if(IS_ERR(drv_fan->dev))
	{
		printk("device_create_err\n");
		ret =PTR_ERR(drv_fan->dev);
		goto device_create_err;
	}
	//获取设备树中GPIO的数量
	drv_fan->count = gpiod_count(&pdv->dev,  "fans");
	if(drv_fan->count < 0)
	{
		printk("gpiod_count_err\r\n");
	}
	printk("drv_fan->count=%d\r\n",drv_fan->count);
	drv_fan->get_gpio = kzalloc(sizeof(struct gpio_desc *)*10, GFP_KERNEL);
	if(IS_ERR(drv_fan->get_gpio))
	{
		printk("get_gpio_kzalloc_err\n");
		ret =PTR_ERR(drv_fan->get_gpio);
		goto get_gpio_kzalloc_err;
	}
	//根gpio数量去获取标号
	for(i=0;i<drv_fan->count;i++)
	{
		drv_fan->get_gpio[i] = devm_gpiod_get_index(&pdv->dev,"fans",i,GPIOD_OUT_HIGH );
		gpiod_direction_output(drv_fan->get_gpio[i], 0);	
		
	}
	return ret;
get_gpio_kzalloc_err:
	device_destroy(drv_fan->cls, MKDEV(drv_fan->major, drv_fan->spex->minum));
device_create_err:
	class_destroy(drv_fan->cls);
class_create_err:
	unregister_chrdev(drv_fan->major, drv_fan->spex->name);
register_chrdev_err:
	kfree(drv_fan);
spex_kzalloc_err:
	kfree(drv_fan);
	return ret;


}
int drv_fan_remove(struct platform_device *pdv)
{
	int ret = 0,i;
	printk("-------%s------\r\n",__FUNCTION__);
	for(i=0;i<drv_fan->count;i++)
	{
		gpiod_set_value(drv_fan->get_gpio[i], 0);
		//gpiod_put(drv_fan->get_gpio[i]);
	}
	kfree(drv_fan->get_gpio); 
	device_destroy(drv_fan->cls, MKDEV(drv_fan->major, drv_fan->spex->minum));
	class_destroy(drv_fan->cls);
	unregister_chrdev(drv_fan->major, drv_fan->spex->name);
	kfree(drv_fan->spex);
	kfree(drv_fan);
	return ret;
}

const struct of_device_id fan_of_match_table[]={
	{ .compatible = "stm32mp157a_fan" },

};
struct platform_driver fan_drv={
	.probe = drv_fan_probe,
	.remove = drv_fan_remove,
	.driver = {
			.name = "fan0",
			.of_match_table = fan_of_match_table,
	},
};

static int __init drv_fan_init(void)
{
	int ret=0;
	printk("-------%s-------\r\n",__FUNCTION__);
	platform_driver_register(&fan_drv);
	return ret;
}

static void __exit drv_fan_exit(void)
{
	printk("-------%s------\r\n",__FUNCTION__);
	platform_driver_unregister(&fan_drv);
}

module_init(drv_fan_init);
module_exit(drv_fan_exit);
MODULE_LICENSE("GPL");


