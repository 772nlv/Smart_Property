#ifndef __STM32MP157XXX__
#define __STM32MP157XXX__


#define GPIOZ_Base 0x54004000
#define GPIOE_Base 0x50006000
#define GPIOF_Base 0x50007000


#define RCC_Base 0x50000000


#define __IO  volatile 
#define uint32_t  unsigned int 
#define uint16_t  unsigned short

typedef struct
{
  __IO uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO uint32_t OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
  __IO uint32_t OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
  __IO uint32_t PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  __IO uint32_t IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
  __IO uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
  __IO uint16_t BSRRL;    /*!< GPIO port bit set/reset low register,  Address offset: 0x18      */
  __IO uint16_t BSRRH;    /*!< GPIO port bit set/reset high register, Address offset: 0x1A      */
  __IO uint32_t LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  __IO uint32_t AFR[2];   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
  __IO uint32_t BRR;      /*!< GPIO port bit reset register,          Address offset: 0x28 */
  __IO uint32_t BUF[1];   /*!< NO register,                           Address offset: 0x2C */
  __IO uint32_t SECCFGR;  /*!< GPIO secure configuration register,    Address offset: 0x30 */                      	
} GPIO_TypeDef;

typedef struct {
	__IO unsigned int TZCR;     	// 0x000
	__IO unsigned int res1[2]; 		// 0x004-0x008
	__IO unsigned int OCENSETR;     // 0x00C
	__IO unsigned int OCENCLRR;  	// 0x010
	__IO unsigned int res2[1]; 		// 0x014
	__IO unsigned int HSICFGR; 		// 0x018
	__IO unsigned int CSICFGR; 		// 0x01C
	__IO unsigned int MPCKSELR; 	// 0x020
	__IO unsigned int ASSCKSELR; 	// 0x024
	__IO unsigned int PCK12SELR; 	// 0x028
	__IO unsigned int MPCKDIVR; 	// 0x02C
	__IO unsigned int AXIDIVR; 		// 0x030
	__IO unsigned int res3[2];
	__IO unsigned int APB4DIVR; 	// 0x03C
	__IO unsigned int APB5DIVR; 	// 0x040
	__IO unsigned int RTCDIVR; 		// 0x044
	__IO unsigned int MSSCKSELR;    // 0x048
	__IO unsigned int res4[13];
	__IO unsigned int PLL1CR; 		// 0x080
	__IO unsigned int PLL1CFGR1; 	// 0x084
	__IO unsigned int PLL1CFGR2; 	// 0x088
	__IO unsigned int PLL1FRACR; 	// 0x08C
	__IO unsigned int PLL1CSGR;     // 0x090
	__IO unsigned int PLL2CR; 		// 0x094
	__IO unsigned int PLL2CFGR1; 	// 0x098
	__IO unsigned int PLL2CFGR2; 	// 0x09C
	__IO unsigned int PLL2FRACR;    // 0x0A0
	__IO unsigned int PLL2CSGR;     // 0x0A4
	__IO unsigned int res5[6];
	__IO unsigned int I2C46CKSELR;  // 0x0C0
	__IO unsigned int SPI6CKSELR;   // 0x0C4
	__IO unsigned int UART1CKSELR;  // 0x0C8
	__IO unsigned int RNG1CKSELR;   // 0x0CC
	__IO unsigned int CPERCKSELR;   // 0x0D0
	__IO unsigned int STGENCKSELR;  // 0x0D4
	__IO unsigned int DDRITFCR; 	// 0x0D8
	__IO unsigned int res6[9];
	__IO unsigned int MP_BOOTCR;  	// 0x100
	__IO unsigned int MP_SREQSETR;  // 0x104
	__IO unsigned int MP_SREQCLRR;  // 0x108
	__IO unsigned int MP_GCR;  		// 0x10C
	__IO unsigned int MP_APRSTCR; 	// 0x110
	__IO unsigned int MP_APRSTSR;   // 0x114
	__IO unsigned int res7[10];
	__IO unsigned int BDCR; 		// 0x140
	__IO unsigned int RDLSICR;  	// 0x144
	__IO unsigned int res8[14];
	__IO unsigned int APB4RSTSETR; 	// 0x180
	__IO unsigned int APB4RSTCLRR; 	// 0x184
	__IO unsigned int APB5RSTSETR;  // 0x188
	__IO unsigned int APB5RSTCLRR;  // 0x18C
	__IO unsigned int AHB5RSTSETR;  // 0x190
	__IO unsigned int AHB5RSTCLRR;  // 0x194
	__IO unsigned int AHB6RSTSETR;  // 0x198
	__IO unsigned int AHB6RSTCLRR;  // 0x19C
	__IO unsigned int TZAHB6RSTSELR;// 0x1A0
	__IO unsigned int TZAHB6RSTCLRR;// 0x1A4
	__IO unsigned int res9[22];
	__IO unsigned int MP_APB4ENSETR;// 0x200
	__IO unsigned int MP_APB4ENCLRR;// 0x204
	__IO unsigned int MP_APB5ENSETR;// 0x208
	__IO unsigned int MP_APB5ENCLRR;// 0x20C
	__IO unsigned int MP_AHB5ENSETR;// 0x210
	__IO unsigned int MP_AHB5ENCLRR;// 0x214
	__IO unsigned int MP_AHB6ENSETR;// 0x218
	__IO unsigned int MP_AHB6ENCLRR;// 0x21C
	__IO unsigned int MP_TZAHB6ENSELR;// 0x220
	__IO unsigned int MP_TZAHB6ENCLRR;// 0x224
	__IO unsigned int res10[22];
	__IO unsigned int MC_APB4ENSETR; // 0x280
	__IO unsigned int MC_APB4ENCLRR; // 0x284
	__IO unsigned int MC_APB5ENSETR; // 0x288
	__IO unsigned int MC_APB5ENCLRR; // 0x28C
	__IO unsigned int MC_AHB5ENSETR; // 0x290
	__IO unsigned int MC_AHB5ENCLRR; // 0x294
	__IO unsigned int MC_AHB6ENSETR; // 0x298
	__IO unsigned int MC_AHB6ENCLRR; // 0x29C
	__IO unsigned int res11[24];
	__IO unsigned int MP_APB4LPENSETR; // 0x300
	__IO unsigned int MP_APB4LPENCLRR; // 0x304
	__IO unsigned int MP_APB5LPENSETR; // 0x308
	__IO unsigned int MP_APB5LPENCLRR; // 0x30C
	__IO unsigned int MP_AHB5LPENSETR; // 0x310
	__IO unsigned int MP_AHB5LPENCLRR; // 0x314
	__IO unsigned int MP_AHB6LPENSETR; // 0x318
	__IO unsigned int MP_AHB6LPENCLRR; // 0x31C
	__IO unsigned int MP_TZAHB6LPENSETR; // 0x320
	__IO unsigned int MP_TZAHB6LPENCLRR; // 0x324
	__IO unsigned int res12[22];
	__IO unsigned int MC_APB4LPENSETR; // 0x380
	__IO unsigned int MC_APB4LPENCLRR; // 0x384
	__IO unsigned int MC_APB5LPENSETR; // 0x388
	__IO unsigned int MC_APB5LPENCLRR; // 0x38C
	__IO unsigned int MC_AHB5LPENSETR; // 0x390
	__IO unsigned int MC_AHB5LPENCLRR; // 0x394
	__IO unsigned int MC_AHB6LPENSETR; // 0x398
	__IO unsigned int MC_AHB6LPENCLRR; // 0x39C
	__IO unsigned int res13[24];
	__IO unsigned int BR_RSTSCLRR; 		// 0x400
	__IO unsigned int MP_GRSTCSETR; 	// 0x404
	__IO unsigned int MP_RSTSR; 		// 0x408
	__IO unsigned int MP_IWDGFZSETR; 	// 0x40C
	__IO unsigned int MP_IWDGFZCLRR;  	// 0x410
	__IO unsigned int MP_CIER; 			// 0x414
	__IO unsigned int MP_CIFR; 			// 0x418
	__IO unsigned int PWRLPDLYCR; 		// 0x41C
	__IO unsigned int MP_RSTSS; 		// 0x420
	__IO unsigned int res14[247];
	__IO unsigned int MCO1CFGR; 		// 0x800
	__IO unsigned int MCO2CFGR; 		// 0x804
	__IO unsigned int OCRDYR; 			// 0x808
	__IO unsigned int DBGCFGR; 			// 0x80C
	__IO unsigned int res15[4];
	__IO unsigned int RCK3SELR; 		// 0x820
	__IO unsigned int RCK4SELR; 		// 0x824
	__IO unsigned int TIMG1PRER;  		// 0x828
	__IO unsigned int TIMG2PRER; 		// 0x82C
	__IO unsigned int MCUDIVR; 			// 0x830
	__IO unsigned int APB1DIVR; 		// 0x834
	__IO unsigned int APB2DIVR; 		// 0x838
	__IO unsigned int APB3DIVR; 		// 0x83C
	__IO unsigned int res16[16];
	__IO unsigned int PLL3CR;   		// 0x880
	__IO unsigned int PLL3CFGR1; 		// 0x884
	__IO unsigned int PLL3CFGR2; 		// 0x888
	__IO unsigned int PLL3FRACR; 		// 0x88C
	__IO unsigned int PLL3CSGR; 		// 0x890
	__IO unsigned int PLL4CR; 			// 0x894
	__IO unsigned int PLL4CFGR1; 		// 0x898
	__IO unsigned int PLL4CFGR2; 		// 0x89C
	__IO unsigned int PLL4FRACR; 		// 0x8A0
	__IO unsigned int PLL4CSGR; 		// 0x8A4
	__IO unsigned int res17[6];
	__IO unsigned int I2C12CKSELR; 		// 0x8C0
	__IO unsigned int I2C35CKSELR;  	// 0x8C4
	__IO unsigned int SAI1CKSELR; 		// 0x8C8
	__IO unsigned int SAI2CKSELR; 		// 0x8CC
	__IO unsigned int SAI3CKSELR; 		// 0x8D0
	__IO unsigned int SAI4CKSELR; 		// 0x8D4
	__IO unsigned int SPI2S1CKSELR; 	// 0x8D8
	__IO unsigned int SPI2S23CKSELR; 	// 0x8DC
	__IO unsigned int SPI45CKSELR; 		// 0x8E0
	__IO unsigned int UART6CKSELR; 		// 0x8E4
	__IO unsigned int UART24CKSELR; 	// 0x8E8
	__IO unsigned int UART35CKSELR; 	// 0x8EC
	__IO unsigned int UART78CKSELR; 	// 0x8F0
	__IO unsigned int SDMMC12CKSELR; 	// 0x8F4
	__IO unsigned int SDMMC3CKSELR; 	// 0x8F8
	__IO unsigned int ETHCKSELR; 		// 0x8FC
	__IO unsigned int QSPICKSELR; 		// 0x900
	__IO unsigned int FMCCKSELR; 		// 0x904
	__IO unsigned int res18[1];
	__IO unsigned int FDCANCKSELR; 		// 0x90C
	__IO unsigned int res19[1];
	__IO unsigned int SPDIFCKSELR; 		// 0x914
	__IO unsigned int CECCKSELR; 		// 0x918
	__IO unsigned int USBCKSELR; 		// 0x91C
	__IO unsigned int RNG2CKSELR;  		// 0x920
	__IO unsigned int DSICKSELR; 		// 0x924
	__IO unsigned int ADCCKSELR; 		// 0x928
	__IO unsigned int LPTIM45CKSELR; 	// 0x92C
	__IO unsigned int LPTIM23CKSELR;    // 0x930
	__IO unsigned int LPTIM1CKSELR; 	// 0x934
	__IO unsigned int res20[18];
	__IO unsigned int APB1RSTSETR; 		// 0x980
	__IO unsigned int APB1RSTCLRR; 		// 0x984
	__IO unsigned int APB2RSTSETR; 		// 0x988
	__IO unsigned int APB2RSTCLRR; 		// 0x98C
	__IO unsigned int APB3RSTSETR; 		// 0x990
	__IO unsigned int APB3RSTCLRR; 		// 0x994
	__IO unsigned int AHB2RSTSETR; 		// 0x998
	__IO unsigned int AHB2RSTCLRR;  	// 0x99C
	__IO unsigned int AHB3RSTSETR; 		// 0x9A0
	__IO unsigned int AHB3RSTCLRR; 		// 0x9A4
	__IO unsigned int AHB4RSTSETR; 		// 0x9A8
	__IO unsigned int AHB4RSTCLRR; 		// 0x9AC
	__IO unsigned int res21[20];
	__IO unsigned int MP_APB1ENSETR; 	// 0xA00
	__IO unsigned int MP_APB1ENCLRR; 	// 0xA04
	__IO unsigned int MP_APB2ENSETR; 	// 0xA08
	__IO unsigned int MP_APB2ENCLRR;  	// 0xA0C
	__IO unsigned int MP_APB3ENSETR; 	// 0xA10
	__IO unsigned int MP_APB3ENCLRR; 	// 0xA14
	__IO unsigned int MP_AHB2ENSETR; 	// 0xA18
	__IO unsigned int MP_AHB2ENCLRR; 	// 0xA1C
	__IO unsigned int MP_AHB3ENSETR; 	// 0xA20
	__IO unsigned int MP_AHB3ENCLRR; 	// 0xA24
	__IO unsigned int MP_AHB4ENSETR; 	// 0xA28
	__IO unsigned int MP_AHB4ENCLRR; 	// 0xA2C
	__IO unsigned int res22[2];
	__IO unsigned int MP_MLAHBENSETR; 	// 0xA38
	__IO unsigned int MP_MLAHBENCLRR; 	// 0xA3C
	__IO unsigned int res23[16];
	__IO unsigned int MC_APB1ENSETR; 	// 0xA80
	__IO unsigned int MC_APB1ENCLRR; 	// 0xA84
	__IO unsigned int MC_APB2ENSETR; 	// 0xA88
	__IO unsigned int MC_APB2ENCLRR; 	// 0xA8C
	__IO unsigned int MC_APB3ENSETR; 	// 0xA90
	__IO unsigned int MC_APB3ENCLRR; 	// 0xA94
	__IO unsigned int MC_AHB2ENSETR; 	// 0xA98
	__IO unsigned int MC_AHB2ENCLRR; 	// 0xA9C
	__IO unsigned int MC_AHB3ENSETR; 	// 0xAA0
	__IO unsigned int MC_AHB3ENCLRR; 	// 0xAA4
	__IO unsigned int MC_AHB4ENSETR; 	// 0xAA8
	__IO unsigned int MC_AHB4ENCLRR; 	// 0xAAC
	__IO unsigned int MC_AXIMENSETR; 	// 0xAB0
	__IO unsigned int MC_AXIMENCLRR; 	// 0xAB4
	__IO unsigned int MC_MLAHBENSETR; 	// 0xAB8
	__IO unsigned int MC_MLAHBENCLRR; 	// 0xABC
	__IO unsigned int res24[16];
	__IO unsigned int MP_APB1LPENSETR; 	// 0xB00
	__IO unsigned int MP_APB1LPENCLRR; 	// 0xB04
	__IO unsigned int MP_APB2LPENSETR;  // 0xB08
	__IO unsigned int MP_APB2LPENCLRR; 	// 0xB0C
	__IO unsigned int MP_APB3LPENSETR; 	// 0xB10
	__IO unsigned int MP_APB3LPENCLRR;  // 0xB14
	__IO unsigned int MP_AHB2LPENSETR;  // 0xB18
	__IO unsigned int MP_AHB2LPENCLRR;  // 0xB1C
	__IO unsigned int MP_AHB3LPENSETR;  // 0xB20
	__IO unsigned int MP_AHB3LPENCLRR;  // 0xB24
	__IO unsigned int MP_AHB4LPENSETR;  // 0xB28
	__IO unsigned int MP_AHB4LPENCLRR;  // 0xB2C
	__IO unsigned int MP_AXIMLPENSETR;  // 0xB30
	__IO unsigned int MP_AXIMLPENCLRR;  // 0xB34
	__IO unsigned int MP_MLAHBLPENSETR; // 0xB38
	__IO unsigned int MP_MLAHBLPENCLRR; // 0xB3C
	__IO unsigned int res25[16];
	__IO unsigned int MC_APB1LPENSETR;  // 0xB80
	__IO unsigned int MC_APB1LPENCLRR; 	// 0xB84
	__IO unsigned int MC_APB2LPENSETR;  // 0xB88
	__IO unsigned int MC_APB2LPENCLRR;  // 0xB8C
	__IO unsigned int MC_APB3LPENSETR;  // 0xB90
	__IO unsigned int MC_APB3LPENCLRR;  // 0xB94
	__IO unsigned int MC_AHB2LPENSETR;  // 0xB98
	__IO unsigned int MC_AHB2LPENCLRR;  // 0xB9C
	__IO unsigned int MC_AHB3LPENSETR;  // 0xBA0
	__IO unsigned int MC_AHB3LPENCLRR;  // 0xBA4
	__IO unsigned int MC_AHB4LPENSETR;  // 0xBA8
	__IO unsigned int MC_AHB4LPENCLRR;  // 0xBAC
	__IO unsigned int MC_AXIMLPENSETR;  // 0xBB0
	__IO unsigned int MC_AXIMLPENCLRR;  // 0xBB4
	__IO unsigned int MC_MLAHBLPENSETR; // 0xBB8
	__IO unsigned int MC_MLAHBLPENCLRR; // 0xBBC
	__IO unsigned int res26[16];
	__IO unsigned int MC_RSTSCLRR;  	// 0xC00
	__IO unsigned int res27[4];
	__IO unsigned int MC_CIER;  		// 0xC14
	__IO unsigned int MC_CIFR; 			// 0xC18
	__IO unsigned int res28[246];
	__IO unsigned int VERR; 			// 0xFF4
	__IO unsigned int IDR; 				// 0xFF8
	__IO unsigned int SIDR; 			// 0xFFC
}RCC_TypeDef;


#endif //__STM32MP157XXX__
