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
#include <linux/interrupt.h>
#include <linux/of_irq.h>
#include <linux/poll.h>
#include <linux/device.h>
#include "stm32mp157xxx.h"
struct stm32mp157 {
	unsigned int major;
	struct class *cls;
	struct device *dev;
	GPIO_TypeDef *gpio;
	unsigned int *rcc;
	unsigned int count;
	struct resource *resource[10];
	struct Platform_data_spex *spex;
	struct gpio_desc **get_gpio;
	unsigned int have_data;
	struct wait_queue_head wq_head;
	struct timer_list time;
};
struct stm32mp157 *drv_key;
struct key_info{
	char name[10];
	u32 irq;
	u32 trig;
	u32 value;
};
struct key_info keys[10]={
[0]={

	},
};
struct key_info key0;
unsigned int key_irq_value = 0;

//自旋锁
spinlock_t lock;

int drv_key_open(struct inode *ide, struct file *flp)
{
	int ret=0;
	drv_key->have_data =0;
	return ret;
}
int drv_key_close(struct inode *ide, struct file *flp)
{
	int ret=0;
	return ret;
}
ssize_t drv_key_write(struct file *flp, const char __user *buf, size_t len, loff_t *flags)
{
	ssize_t ret=0;
	return ret;
}
ssize_t drv_key_read(struct file *flp, char __user *buf, size_t len, loff_t *flags)
{
	ssize_t ret = 0;
	wait_event_interruptible(drv_key->wq_head, drv_key->have_data);
	
	//有数据时have_data=1，不阻塞，上传数据，没有数据have_data=0就阻塞
	spin_lock(&lock);
	ret = copy_to_user(buf, &key_irq_value, len);
	if(ret !=0)
	{
		printk("copy_from_user_err\n");
		return ret;
	}
	drv_key->have_data =0;
	memset(&key0,0,sizeof(key0));
	spin_unlock(&lock);
	return len;
}

const struct file_operations key_fops={
	.open = drv_key_open,
	.release = drv_key_close,
	.write = drv_key_write,
	.read = drv_key_read,
};

irqreturn_t drv_key_irq(int irq, void *data)
{
	drv_key->have_data = 1;
	return IRQ_WAKE_THREAD;
}
//定义一个延迟处理函数，20ms后判断按键引脚的电平
irqreturn_t drv_key_thread_irq(int irq, void *data)
{
	if(irq == keys[0].irq)
	{
		key_irq_value = 0;
	}
	else
	{
		key_irq_value = 1;
	}
	mod_timer(&drv_key->time, jiffies+HZ/50);
	return IRQ_HANDLED;
}

void drv_key0_timer(struct timer_list *tim)
{
	int ret = gpiod_get_value(drv_key->get_gpio[1]);
	int ret2 = gpiod_get_value(drv_key->get_gpio[0]);
	if(!ret || !ret2)
	{	
		wake_up_interruptible(&drv_key->wq_head);
	}
}


int drv_key_probe(struct platform_device *pdv)
{
	int ret = 0,i;
	char name_string[20];
	printk("-------%s------\r\n",__FUNCTION__);
	
	//1、实例化对象
	drv_key = kzalloc(sizeof(struct stm32mp157), GFP_KERNEL);
	if(IS_ERR(drv_key))
	{
		printk("kzalloc_err\r\n");
		ret = PTR_ERR(drv_key);
		return ret;
	}
	drv_key->spex = kzalloc(sizeof(struct Platform_data_spex), GFP_KERNEL);
	if(IS_ERR(drv_key->spex))
	{
		printk("spex_kzalloc_err\r\n");
		ret = PTR_ERR(drv_key->spex);
		goto spex_kzalloc_err;
	}
	of_property_read_u32_index(pdv->dev.of_node, "minum", 1, &drv_key->spex->minum);
	of_property_read_string(pdv->dev.of_node, "dev_name", &drv_key->spex->name);
	printk("name=%s\r\n",drv_key->spex->name);
	
	//2、申请设备号
	drv_key->major = register_chrdev(0,drv_key->spex->name, &key_fops);
	if(drv_key->major<0)
	{
		printk("register_chrdev_err\n");
		ret =drv_key->major;
		goto register_chrdev_err;
	}
	
	//3、创建类
	drv_key->cls = class_create(THIS_MODULE, drv_key->spex->name);
	if(IS_ERR(drv_key->cls))
	{
		printk("class_create_err\n");
		ret =PTR_ERR(drv_key->cls);
		goto class_create_err;
	}
	
	//4、创建设备节点
	drv_key->dev = device_create(drv_key->cls, NULL, MKDEV(drv_key->major, drv_key->spex->minum), NULL,drv_key->spex->name);
	if(IS_ERR(drv_key->dev))
	{
		printk("device_create_err\n");
		ret =PTR_ERR(drv_key->dev);
		goto device_create_err;
	}

	//初始化工作队列头
	init_waitqueue_head(&drv_key->wq_head);
	//初始化自旋锁
	spin_lock_init(&lock);

	//初始化timer
	timer_setup(&drv_key->time, drv_key0_timer, 0);
	add_timer(&drv_key->time);
	//获取设备树中GPIO的数量
	drv_key->count = gpiod_count(&pdv->dev, "keys");
	if(drv_key->count < 0)
	{
		printk("of_gpio_count_err\r\n");
	}
	printk("drv_key->count=%d\r\n",drv_key->count);
	drv_key->get_gpio = kzalloc(sizeof(struct gpio_desc *)*10, GFP_KERNEL);
	if(IS_ERR(drv_key->get_gpio))
	{
		printk("get_gpio_kzalloc_err\n");
		ret =PTR_ERR(drv_key->get_gpio);
		goto get_gpio_kzalloc_err;
	}
	//根gpio数量去获取标号
	for(i=0;i<drv_key->count;i++)
	{
		sprintf(name_string, "key%d", i);
		drv_key->get_gpio[i] = devm_gpiod_get_index(&pdv->dev, "keys",i, GPIOD_IN);
		keys[i].irq = irq_of_parse_and_map(pdv->dev.of_node, i);
		keys[i].trig = irq_get_trigger_type(keys[i].irq);
		keys[i].value = i;
		request_threaded_irq(keys[i].irq, drv_key_irq, drv_key_thread_irq, keys[i].trig, name_string, &keys[i].value);
	}
	return ret;
get_gpio_kzalloc_err:
	device_destroy(drv_key->cls, MKDEV(drv_key->major, drv_key->spex->minum));
device_create_err:
	class_destroy(drv_key->cls);
class_create_err:
	unregister_chrdev(drv_key->major, drv_key->spex->name);
register_chrdev_err:
	kfree(drv_key);
spex_kzalloc_err:
	kfree(drv_key);
	return ret;


}
int drv_key_remove(struct platform_device *pdv)
{
	int ret = 0,i;
	printk("-------%s------\r\n",__FUNCTION__);
	for(i=0;i<drv_key->count;i++)
	{
		free_irq(keys[i].irq, &keys[i].value);
	}
	kfree(drv_key->get_gpio); 
	device_destroy(drv_key->cls, MKDEV(drv_key->major, drv_key->spex->minum));
	class_destroy(drv_key->cls);
	unregister_chrdev(drv_key->major, drv_key->spex->name);
	kfree(drv_key->spex);
	kfree(drv_key);
	return ret;
}

const struct of_device_id key_of_match_table[]={
	{ .compatible = "stm32mp157a_key" },

};
struct platform_driver key_drv={
	.probe = drv_key_probe,
	.remove = drv_key_remove,
	.driver = {
			.name = "key",
			.of_match_table = key_of_match_table,
	},
};

static int __init drv_key_init(void)
{
	int ret=0;
	printk("-------%s------\r\n",__FUNCTION__);
	platform_driver_register(&key_drv);
	return ret;
}

static void __exit drv_key_exit(void)
{
	printk("-------%s------\r\n",__FUNCTION__);
	platform_driver_unregister(&key_drv);
}

module_init(drv_key_init);
module_exit(drv_key_exit);
MODULE_LICENSE("GPL");

