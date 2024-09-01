#ifndef __PLATFORM_DATA_SPECIAL__
#define __PLATFORM_DATA_SPECIAL__

struct Platform_data_spex{
	const char *name;  // 设备�?
	unsigned int minum;// 次设备号
	unsigned int MODER_SET;
	unsigned int MODER_RESET;

	unsigned int OTYPER_SET;
	unsigned int OTYPER_RESET;

	unsigned int OSPEEDR_SET;
	unsigned int OSPEEDR_RESET;

	unsigned int PUPDR_SET;
	unsigned int PUPDR_RESET;

	unsigned int IDR_SET;
	unsigned int IDR_RESET;

	unsigned int ODR_SET;
	unsigned int ODR_RESET;

	unsigned int BSRRL_SET;
	unsigned int BSRRL_RESET;

	unsigned int BSRRH_SET;
	unsigned int BSRRH_RESET;

	unsigned int LCKR_SET;
	unsigned int LCKR_RESET;

	unsigned int BRR_SET;
	unsigned int BRR_RESET;

	unsigned int SECCFGR_SET;
	unsigned int SECCFGR_RESET;

	unsigned int RCC_MP_REGISTER; //操作寄存器的哪一个位

	unsigned int RCC_OFFSET;
};


#endif //__PLATFORM_DATA_SPECIAL__
