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
struct stm32mp157 *drv_beep;

int drv_beep_open(struct inode *ide, struct file *flp)
{
	int ret=0;
	
	return ret;
}
int drv_beep_close(struct inode *ide, struct file *flp)
{
	int ret=0;
	int i;
	for(i=0;i<drv_beep->count;i++)
	{
		gpiod_set_value(drv_beep->get_gpio[i], 0);
		//gpiod_put(drv_beep->get_gpio[i]);
	}
	return ret;
}
ssize_t drv_beep_write(struct file *flp, const char __user *buf, size_t len, loff_t *flags)
{
	ssize_t ret=0;
	int i = 0;
	int beep_statu = 0;
	ret = copy_from_user(&beep_statu, buf, len);
	if(ret != 0)
	{
		printk("drv_beep_copy_from_user_err\r\n");
		return ret;
	}
	if(beep_statu)
	{
		//打开蜂鸣器
		if(beep_statu == 1)
		{
			gpiod_set_value(drv_beep->get_gpio[0], 1);
		}
		//close beep
		else if(beep_statu == 2)
		{
			gpiod_set_value(drv_beep->get_gpio[0], 0);
		}
		//打开马达
		else if(beep_statu == 3)
		{
			gpiod_set_value(drv_beep->get_gpio[1], 1);
		}
		//关闭马达
		else if(beep_statu == 4)
		{
			gpiod_set_value(drv_beep->get_gpio[1], 0);
		}
		//同时打开
		else
		{
			gpiod_set_value(drv_beep->get_gpio[1], 1);
			gpiod_set_value(drv_beep->get_gpio[0], 1);
		}
		
	}
	else
	{
		//关蜂鸣器
		for(i =0 ;i < drv_beep->count;i++)
		{
			gpiod_set_value(drv_beep->get_gpio[i], 0);
		}
	}
	return ret;
}

const struct file_operations beep_fops={
	.open = drv_beep_open,
	.release = drv_beep_close,
	.write = drv_beep_write,
};

int drv_beep_probe(struct platform_device *pdv)
{
	int ret = 0,i;
	//char name_string[20];
	printk("-------%s------\r\n",__FUNCTION__);
	
	//1、实例化对象
	drv_beep = kzalloc(sizeof(struct stm32mp157), GFP_KERNEL);
	if(IS_ERR(drv_beep))
	{
		printk("kzalloc_err\r\n");
		ret = PTR_ERR(drv_beep);
		return ret;
	}
	drv_beep->spex = kzalloc(sizeof(struct Platform_data_spex), GFP_KERNEL);
	if(IS_ERR(drv_beep->spex))
	{
		printk("spex_kzalloc_err\r\n");
		ret = PTR_ERR(drv_beep->spex);
		goto spex_kzalloc_err;
	}
	of_property_read_u32_index(pdv->dev.of_node, "minum", 1, &drv_beep->spex->minum);
	of_property_read_string(pdv->dev.of_node, "dev_name", &drv_beep->spex->name);
	printk("name=%s\r\n",drv_beep->spex->name);
	
	//2、申请设备号
	drv_beep->major = register_chrdev(0,drv_beep->spex->name, &beep_fops);
	if(drv_beep->major<0)
	{
		printk("register_chrdev_err\n");
		ret =drv_beep->major;
		goto register_chrdev_err;
	}
	
	//3、创建类
	drv_beep->cls = class_create(THIS_MODULE, drv_beep->spex->name);
	if(IS_ERR(drv_beep->cls))
	{
		printk("class_create_err\n");
		ret =PTR_ERR(drv_beep->cls);
		goto class_create_err;
	}
	
	//4、创建设备节点
	drv_beep->dev = device_create(drv_beep->cls, NULL, MKDEV(drv_beep->major, drv_beep->spex->minum), NULL,drv_beep->spex->name);
	if(IS_ERR(drv_beep->dev))
	{
		printk("device_create_err\n");
		ret =PTR_ERR(drv_beep->dev);
		goto device_create_err;
	}
	//获取设备树中GPIO的数量
	drv_beep->count = gpiod_count(&pdv->dev,  "beeps");
	if(drv_beep->count < 0)
	{
		printk("gpiod_count_err\r\n");
	}
	printk("drv_beep->count=%d\r\n",drv_beep->count);
	drv_beep->get_gpio = kzalloc(sizeof(struct gpio_desc *)*10, GFP_KERNEL);
	if(IS_ERR(drv_beep->get_gpio))
	{
		printk("get_gpio_kzalloc_err\n");
		ret =PTR_ERR(drv_beep->get_gpio);
		goto get_gpio_kzalloc_err;
	}
	//根据gpio数量去获取标号
	for(i=0;i<drv_beep->count;i++)
	{
		drv_beep->get_gpio[i] = devm_gpiod_get_index(&pdv->dev,"beeps",i,GPIOD_OUT_HIGH );
		gpiod_direction_output(drv_beep->get_gpio[i], 0);	
	}
	return ret;
get_gpio_kzalloc_err:
	device_destroy(drv_beep->cls, MKDEV(drv_beep->major, drv_beep->spex->minum));
device_create_err:
	class_destroy(drv_beep->cls);
class_create_err:
	unregister_chrdev(drv_beep->major, drv_beep->spex->name);
register_chrdev_err:
	kfree(drv_beep);
spex_kzalloc_err:
	kfree(drv_beep);
	return ret;


}
int drv_beep_remove(struct platform_device *pdv)
{
	int ret = 0,i;
	printk("-------%s------\r\n",__FUNCTION__);
	for(i=0;i<drv_beep->count;i++)
	{
		gpiod_set_value(drv_beep->get_gpio[i], 0);
		//gpiod_put(drv_beep->get_gpio[i]);
	}
	kfree(drv_beep->get_gpio); 
	device_destroy(drv_beep->cls, MKDEV(drv_beep->major, drv_beep->spex->minum));
	class_destroy(drv_beep->cls);
	unregister_chrdev(drv_beep->major, drv_beep->spex->name);
	kfree(drv_beep->spex);
	kfree(drv_beep);
	return ret;
}

const struct of_device_id beep_of_match_table[]={
	{ .compatible = "stm32mp157a_beep" },

};
struct platform_driver beep_drv={
	.probe = drv_beep_probe,
	.remove = drv_beep_remove,
	.driver = {
			.name = "beep0",
			.of_match_table = beep_of_match_table,
	},
};

static int __init drv_beep_init(void)
{
	int ret=0;
	printk("-------%s-------\r\n",__FUNCTION__);
	platform_driver_register(&beep_drv);
	return ret;
}

static void __exit drv_beep_exit(void)
{
	printk("-------%s------\r\n",__FUNCTION__);
	platform_driver_unregister(&beep_drv);
}

module_init(drv_beep_init);
module_exit(drv_beep_exit);
MODULE_LICENSE("GPL");



