#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/mod_devicetable.h>
#include "platform_data_special.h"
#include <linux/fs.h>
#include <linux/io.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include "stm32mp157xxx.h"
#include <linux/of.h>
#include <linux/i2c.h>
#include <linux/spi/spi.h>

#define TEMPERARURE _IOR('T', 0x01, unsigned short)
#define HUMIDITY _IOR('H', 0x02, unsigned short)

char seg_code[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//共阴极数码管显示0-f

struct stm32mp157a{
	unsigned int major;
	struct class *cls;
	struct device *dev;
	struct resource * resource[10];
	struct Platform_data_spex *spex;	
	struct i2c_client * clt;
};
struct stm32mp157a *drv_i2c;

int drv_i2c_open(struct inode *ino, struct file *fop)
{
	int ret = 0;
	return ret;
}
int drv_i2c_close(struct inode *ino, struct file *fop)
{
	int ret = 0;
	return ret;

}
ssize_t drv_i2c_read (struct file * ino, char __user *buf, size_t len, loff_t * lof)
{
	int ret = 0;
	
	return ret;
}
ssize_t drv_i2c_write(struct file * ino, const char __user * buf, size_t len , loff_t * lof)
{
	int ret = 0;
	return ret;	
}



long drv_i2c_ioctl (struct file *fip, unsigned int cmd, unsigned long data)
{
	long ret = 0;
	unsigned short temp_data;
	
	switch(cmd)
	{
		//读取温度
		case TEMPERARURE:
			temp_data = i2c_smbus_read_word_data(drv_i2c->clt, 0xe3);
			break;
		
		case HUMIDITY:
			temp_data = i2c_smbus_read_word_data(drv_i2c->clt, 0xe5);
			break;
		default:
		printk("ioctl error\r\n");
			break;
	}
	ret = copy_to_user((void __user *)data, &temp_data, sizeof(temp_data));
	if(ret < 0)
	{
		printk("copy_to_user_err\r\n");
		return ret;
	}
	return ret;	
}

const struct file_operations hello_fop={
	.open = drv_i2c_open,
	.release = drv_i2c_close,
	.read = drv_i2c_read,
	.write = drv_i2c_write,
	.unlocked_ioctl = drv_i2c_ioctl,
};


int drv_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int ret = 0;
	printk("------%s-----\r\n",__FUNCTION__);
	//1、实例化对象
	drv_i2c = kzalloc(sizeof(struct stm32mp157a), GFP_KERNEL);
	if(IS_ERR(drv_i2c))
	{
		printk("kzalloc_err\r\n");
		ret = PTR_ERR(drv_i2c);
		return ret;
	}
	drv_i2c->spex = kzalloc(sizeof(struct Platform_data_spex), GFP_KERNEL);
	if(IS_ERR(drv_i2c->spex))
	{
		printk("spex_kzalloc_err\r\n");
		ret = PTR_ERR(drv_i2c->spex);
		goto spex_kzalloc_err;
	}

	//验证从设备端发过来的资源是否正确
	//获取资源
	of_property_read_u32_index(client->dev.of_node, "minum", 0, &drv_i2c->spex->minum);
	printk("out_value=%d\r\n",drv_i2c->spex->minum);
	of_property_read_string(client->dev.of_node, "dev_name", &drv_i2c->spex->name);
	printk("name=%s\r\n",drv_i2c->spex->name);


	//申请设备号
	drv_i2c->major = register_chrdev(0, drv_i2c->spex->name, &hello_fop);
	if(drv_i2c->major < 0)
	{
		printk(" register_chrdev_err\r\n");
		ret = drv_i2c->major;
		goto register_chrdev_err;
	}
	//创建类
	drv_i2c->cls = class_create(THIS_MODULE, drv_i2c->spex->name);
	if(IS_ERR(drv_i2c->cls))
	{
		printk(" register_chrdev_err\r\n");
		ret = PTR_ERR(drv_i2c->cls);
		goto class_create_err;
	}
	//创建设备节点
	drv_i2c->dev = device_create(drv_i2c->cls, NULL, MKDEV(drv_i2c->major,drv_i2c->spex->minum), NULL, drv_i2c->spex->name);
	if(IS_ERR(drv_i2c->dev))
	{
		printk(" register_chrdev_err\r\n");
		ret = PTR_ERR(drv_i2c->dev);
		goto device_create_err;
	}
	drv_i2c->clt = client;
	return ret;
device_create_err:
	class_destroy(drv_i2c->cls);
class_create_err:
	unregister_chrdev(drv_i2c->major, drv_i2c->spex->name);
register_chrdev_err:
	kfree(drv_i2c->spex);
spex_kzalloc_err:
	kfree(drv_i2c);
	return ret;
}
int drv_i2c_remove(struct i2c_client *client)
{	
	int ret = 0;
	printk("------%s-----\r\n",__FUNCTION__);
	device_destroy(drv_i2c->cls, MKDEV(drv_i2c->major, drv_i2c->spex->minum));
	class_destroy(drv_i2c->cls);
	unregister_chrdev(drv_i2c->major, drv_i2c->spex->name);
	kfree(drv_i2c->spex);
	kfree(drv_i2c);
	return ret;
}
	
const struct of_device_id i2c_of_match_table[]={
	{ .compatible = "i2c_si7006" },
};


struct i2c_driver i2c_drv={
	.probe = drv_i2c_probe,
	.remove = drv_i2c_remove,
	.driver = {
			.name = "i2c",
			.owner = THIS_MODULE,
			.of_match_table  = i2c_of_match_table,
	},
};

static int __init drv_i2c_init(void)
{
	int ret=0;
	printk("-------%s------\r\n",__FUNCTION__);
	i2c_add_driver(&i2c_drv);
	return ret;
}

static void __exit drv_i2c_exit(void)
{
	printk("-------%s------\r\n",__FUNCTION__);
	i2c_del_driver(&i2c_drv);
}


module_init(drv_i2c_init);
module_exit(drv_i2c_exit);
MODULE_LICENSE("GPL");
