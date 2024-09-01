#ifndef __PWM_FAN_H
#define __PWM_FAN_H


//风扇初始化函数
void TIMER12_CH2_PWM_PB15_Config(void);
//打开关闭风扇
void Fan_TurnOn(void);
void Fan_TurnOff(void);
//风速控制函数
void Fan_Control(unsigned int cvalue);
#endif


