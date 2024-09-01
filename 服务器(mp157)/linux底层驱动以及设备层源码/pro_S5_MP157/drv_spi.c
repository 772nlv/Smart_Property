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
#include <linux/spi/spi.h>

#define SHOW_DATA _IOR('S', 0x01, unsigned short)
char seg_code[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//共阴极数码管显示0-f

struct stm32mp157a{
	unsigned int major;
	struct class *cls;
	struct device *dev;
	struct resource * resource[10];
	struct Platform_data_spex *spex;	
	struct spi_device *spi;
};
struct stm32mp157a *drv_spi;

int drv_spi_open(struct inode *ino, struct file *fop)
{
	int ret = 0;
	return ret;
}
int drv_spi_close(struct inode *ino, struct file *fop)
{
	int ret = 0;
	return ret;

}
ssize_t drv_spi_read (struct file * ino, char __user *buf, size_t len, loff_t * lof)
{
	int ret = 0;
	return ret;
}
ssize_t drv_spi_write(struct file * ino, const char __user * buf, size_t len , loff_t * lof)
{
	int ret = 0;
	return ret;	
}

void show_spi_data(char code,char idex)
{
	//定义一个spi消息队列头
	struct spi_message message;
	//定义传输数据队列
	struct spi_transfer xfer[]={0};
	char tx_buf[2];//传输数据
	spi_message_init(&message);//初始化队列头
	memset(&xfer[0], 0, sizeof(xfer[0]));//在使用前将其清0
	//放入传输的数据
	tx_buf[0]=idex;
	tx_buf[1]=code;
	xfer[0].tx_buf = tx_buf;
	xfer[0].len = ARRAY_SIZE(tx_buf);
	//加到消息队列
	spi_message_add_tail(&xfer[0], &message);
	//spi发送信息
	spi_sync(drv_spi->spi, &message);
}
long drv_spi_ioctl (struct file *fip, unsigned int cmd, unsigned long data)
{
	long ret = 0;
	char code;
	char idex;
	switch(cmd)
	{
		case SHOW_DATA:
			//显示数据函数
			idex = data&0xff;//取第八位的位选信号
			code = seg_code[(data>>8)&0xff];//取数码管需要显示的数据
			if(idex == 0x02)
			{	
				code |= 0x80;
			}
			show_spi_data(code,idex);

			break;

		default:
		printk("ioctl error\r\n");
			break;
	}
	return ret;	
}

const struct file_operations hello_fop={
	.open = drv_spi_open,
	.release = drv_spi_close,
	.read = drv_spi_read,
	.write = drv_spi_write,
	.unlocked_ioctl = drv_spi_ioctl,
};


int drv_spi_probe(struct spi_device *pdv)
{
	int ret = 0;
	printk("------%s-----\r\n",__FUNCTION__);
	//1、实例化对象
	drv_spi = kzalloc(sizeof(struct stm32mp157a), GFP_KERNEL);
	if(IS_ERR(drv_spi))
	{
		printk("kzalloc_err\r\n");
		ret = PTR_ERR(drv_spi);
		return ret;
	}
	drv_spi->spex = kzalloc(sizeof(struct Platform_data_spex), GFP_KERNEL);
	if(IS_ERR(drv_spi->spex))
	{
		printk("spex_kzalloc_err\r\n");
		ret = PTR_ERR(drv_spi->spex);
		goto spex_kzalloc_err;
	}

	//验证从设备端发过来的资源是否正确
	//获取资源
	of_property_read_u32_index(pdv->dev.of_node, "minum", 0, &drv_spi->spex->minum);
	of_property_read_string(pdv->dev.of_node, "spi_name", &drv_spi->spex->name);
	printk("name=%s\r\n",drv_spi->spex->name);


	//申请设备号
	drv_spi->major = register_chrdev(0, drv_spi->spex->name, &hello_fop);
	if(drv_spi->major < 0)
	{
		printk(" register_chrdev_err\r\n");
		ret = drv_spi->major;
		goto register_chrdev_err;
	}
	//创建类
	drv_spi->cls = class_create(THIS_MODULE, drv_spi->spex->name);
	if(IS_ERR(drv_spi->cls))
	{
		printk(" register_chrdev_err\r\n");
		ret = PTR_ERR(drv_spi->cls);
		goto class_create_err;
	}
	//创建设备节点
	drv_spi->dev = device_create(drv_spi->cls, NULL, MKDEV(drv_spi->major,drv_spi->spex->minum), NULL, drv_spi->spex->name);
	if(IS_ERR(drv_spi->dev))
	{
		printk(" register_chrdev_err\r\n");
		ret = PTR_ERR(drv_spi->dev);
		goto device_create_err;
	}
	drv_spi->spi = pdv;
	return ret;
device_create_err:
	class_destroy(drv_spi->cls);
class_create_err:
	unregister_chrdev(drv_spi->major, drv_spi->spex->name);
register_chrdev_err:
	kfree(drv_spi->spex);
spex_kzalloc_err:
	kfree(drv_spi);
	return ret;
}
int drv_spi_remove(struct spi_device *spi)
{	
	int ret = 0;
	printk("-------%s------\r\n",__FUNCTION__);
	device_destroy(drv_spi->cls, MKDEV(drv_spi->major, drv_spi->spex->minum));
	class_destroy(drv_spi->cls);
	unregister_chrdev(drv_spi->major, drv_spi->spex->name);
	kfree(drv_spi->spex);
	kfree(drv_spi);
	return ret;
}
	
const struct of_device_id spi_of_match_table[]={
	{ .compatible = "spi_m74hc595" },
};


struct spi_driver spi_drv={
	.probe = drv_spi_probe,
	.remove = drv_spi_remove,
	.driver = {
			.name = "spi",
			.owner = THIS_MODULE,
			.of_match_table  = spi_of_match_table,
	},
};

static int __init drv_spi_init(void)
{
	int ret=0;
	printk("-------%s------\r\n",__FUNCTION__);
	spi_register_driver(&spi_drv);
	return ret;
}

static void __exit drv_spi_exit(void)
{
	printk("-------%s------\r\n",__FUNCTION__);
	spi_unregister_driver(&spi_drv);
}


module_init(drv_spi_init);
module_exit(drv_spi_exit);
MODULE_LICENSE("GPL");
