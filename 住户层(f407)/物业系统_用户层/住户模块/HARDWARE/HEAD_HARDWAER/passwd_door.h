#ifndef __PASSWD_H
#define __PASSWD_H

void key_4x4_init(void);
#define   ROW_Pin_0  GPIO_Pin_0
#define   ROW_Pin_1  GPIO_Pin_1
#define   ROW_Pin_2  GPIO_Pin_3 
#define   ROW_Pin_3  GPIO_Pin_4 
#define 	KEY_NONE 0xFF  // 定义一个无按键按下的状态码 
#define   COL_Pin_0  GPIO_Pin_2
#define   COL_Pin_1  GPIO_Pin_3
#define   COL_Pin_2  GPIO_Pin_7 
#define   COL_Pin_3  GPIO_Pin_11 
extern uint8_t key_value1;
char key_4x4_scan(void);
extern char passwd[128];


#endif

