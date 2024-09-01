#ifndef __BEEP_H
#define __BEEP_H

#define BEEP PBout(10)

//蜂鸣器初始化-打开-关闭-警报函数
void BEEP_Config(void);
void Beep_Open(void);
void Beep_Close(void);
void Beep_Alarm(void);


#endif

