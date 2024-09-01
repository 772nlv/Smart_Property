#ifndef    __MENU_H
#define    __MENU_H

typedef struct
{
    u8 current;	    //当前窗口号
    u8 next; 		    //下一个窗口号
    u8 enter; 	    //确定后窗口号
	  u8 back; 		    //退出后窗口号
    void (*current_operation)(void); //当前窗口的函数指针
} Menu_table;

void  Menu_key_set(void);

void home(void);

void Temperature(void);
void light(void);
void Setting(void);
void Info(void);

void TestTemperature(void);
void TestLight(void);
void Set(void);
void Information(void);
void gif(void);

#endif


