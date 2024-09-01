#include "user.h"

#define   ROW_Pin_0  GPIO_Pin_0
#define   ROW_Pin_1  GPIO_Pin_1
#define   ROW_Pin_2  GPIO_Pin_3 
#define   ROW_Pin_3  GPIO_Pin_4 
#define KEY_NONE 0xFF  // 定义一个无按键按下的状态码 
uint8_t key_value1 = KEY_NONE;
#define   COL_Pin_0  GPIO_Pin_2
#define   COL_Pin_1  GPIO_Pin_3
#define   COL_Pin_2  GPIO_Pin_7 
#define   COL_Pin_3  GPIO_Pin_11 

void key_4x4_init()
{
  //PD0 1 3 4 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	GPIO_InitTypeDef GPIOD_InitStructure;
	GPIO_InitTypeDef GPIOE_InitStructure;
	
	GPIOD_InitStructure.GPIO_Pin  = ROW_Pin_0|ROW_Pin_1|ROW_Pin_2|ROW_Pin_3;  
	GPIOD_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOD_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
	GPIOD_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIOD_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(GPIOD, &GPIOD_InitStructure);
	 
	//PE2 3 7 11
	GPIOE_InitStructure.GPIO_Pin  = COL_Pin_0|COL_Pin_1|COL_Pin_2|COL_Pin_3; 
	GPIOE_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOE_InitStructure.GPIO_Mode = GPIO_Mode_IN; 	
  GPIOE_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIOE_InitStructure);

}

char key_4x4_scan()  
{  
 char row, key = KEY_NONE;

    // 扫描行线
    for (row = 0; row < 4; row++)
    {
        // 将当前行设置为低电平
        switch (row)
        {
            case 0:
                GPIO_ResetBits(GPIOD, ROW_Pin_0);
                break;
            case 1:
                GPIO_ResetBits(GPIOD, ROW_Pin_1);
                break;
            case 2:
                GPIO_ResetBits(GPIOD, ROW_Pin_2);
                break;
            case 3:
                GPIO_ResetBits(GPIOD, ROW_Pin_3);
                break;
        }

        // 读取列线状态
				if(row == 0)
				{
				if (GPIO_ReadInputDataBit(GPIOE, COL_Pin_0) == 0)
            key = '1';
        if (GPIO_ReadInputDataBit(GPIOE, COL_Pin_1) == 0)
            key = '2';
        if (GPIO_ReadInputDataBit(GPIOE, COL_Pin_2) == 0)
            key = '3';
        if (GPIO_ReadInputDataBit(GPIOE, COL_Pin_3) == 0)
            key = 'A';
				
				}	
				else if(row == 1)
				{
				if (GPIO_ReadInputDataBit(GPIOE, COL_Pin_0) == 0)
            key = '4';
        if (GPIO_ReadInputDataBit(GPIOE, COL_Pin_1) == 0)
            key = '5';
        if (GPIO_ReadInputDataBit(GPIOE, COL_Pin_2) == 0)
            key = '6';
        if (GPIO_ReadInputDataBit(GPIOE, COL_Pin_3) == 0)
            key = 'B';
				
				}
				else if(row == 2)
				{
				if (GPIO_ReadInputDataBit(GPIOE, COL_Pin_0) == 0)
            key = '7';
        if (GPIO_ReadInputDataBit(GPIOE, COL_Pin_1) == 0)
            key = '8';
        if (GPIO_ReadInputDataBit(GPIOE, COL_Pin_2) == 0)
            key = '9';
        if (GPIO_ReadInputDataBit(GPIOE, COL_Pin_3) == 0)
            key = 'C';
				
				}
				else if(row == 3)
				{
				if (GPIO_ReadInputDataBit(GPIOE, COL_Pin_0) == 0)
            key = '*';
        if (GPIO_ReadInputDataBit(GPIOE, COL_Pin_1) == 0)
            key = '0';
        if (GPIO_ReadInputDataBit(GPIOE, COL_Pin_2) == 0)
            key = '#';
        if (GPIO_ReadInputDataBit(GPIOE, COL_Pin_3) == 0)
            key = 'D';
				
				}


        // 将当前行设置为高电平
        switch (row)
        {
            case 0:
                GPIO_SetBits(GPIOD, ROW_Pin_0);
                break;
            case 1:
                GPIO_SetBits(GPIOD, ROW_Pin_1);
                break;
            case 2:
                GPIO_SetBits(GPIOD, ROW_Pin_2);
                break;
            case 3:
                GPIO_SetBits(GPIOD, ROW_Pin_3);
                break;
        }
    }

    return key;
  
}

