KERNEL_DIR=/home/linux/fs_mp157a/kernel/stm32mp1-openstlinux-5.4-dunfell-mp1-20-06-24/sources/arm-ostl-linux-gnueabi/linux-stm32mp-5.4.31-r0/linux-5.4.31
CUR_DIR=${shell pwd}
APP=test
all:
	make -C $(KERNEL_DIR) M=$(CUR_DIR) modules
	$(CC) $(APP).c -o $(APP)
clean:
	make -C $(KERNEL_DIR) M=$(CUR_DIR) clean
	rm -r test
install:
	sudo cp *.ko $(APP) /opt/rootfs/drv_module
obj-m = drv_iic.o
obj-m += drv_spi.o
obj-m += drv_led.o
obj-m += drv_fan.o
obj-m += drv_beep.o
obj-m += drv_key.o