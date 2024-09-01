#include "user.h"
//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);


//2.采集数据任务
//任务优先级
#define DATA_TASK_PRIO		3
//任务堆栈大小	
#define DATA_STK_SIZE 		200  
//任务句柄
TaskHandle_t DATAtask_Handler;
//任务函数
void getdata_task(void *pvParameters);

//按键扫秒任务
//任务优先级
#define KEY_TASK_PRIO		5
//任务堆栈大小	
#define EKY_STK_SIZE 		200  
//任务句柄
TaskHandle_t KEYTask_Handler;
//任务函数
void KEY_task(void *pvParameters);

//LED3闪烁任务
//任务优先级
#define LED3_TASK_PRIO		4
//任务堆栈大小	
#define LED3_STK_SIZE 		50  
//任务句柄
TaskHandle_t LED3Task_Handler;
//任务函数
void led3_task(void *pvParameters);


//任务优先级
#define FLOAT_TASK_PRIO		2
//任务堆栈大小	
#define FLOAT_STK_SIZE 		128
//任务句柄
TaskHandle_t FLOATTask_Handler;
//任务函数
void float_task(void *pvParameters);


//任务优先级
#define PASSWD_TASK_PRIO		6
//任务堆栈大小	
#define PASSWD_STK_SIZE 		200
//任务句柄
TaskHandle_t PASSWDTask_Handler;
//任务函数
void passwd_task(void *pvParameters);

extern EventGroupHandle_t  statehandle;

extern char buff[5];
extern unsigned char state[4];
extern unsigned short int lightint;
//1.主函数
int main(void)
{ 
	//设置系统中断优先级分组4
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	delay_init(168);								//延时函数初始化
	uart_init(115200);     					//串口初始化
	uart2init(115200);							//串口二初始化
	LED_Init();		       						//LED1-3初始化
	BEEP_Config();									//蜂鸣器初始化
	Key_Config();										//按键1-3初始化
	KEY_4_Config();									//按键4初始化
	scanfkey();											//按键监测初始化				
	IIC_Config();										//IIC初始化	
	DHT11_Config();									//温湿度初始化
	OLED_Init();										//OLED屏幕初始化
	My_RTC_Init();									//时钟初始化
	ADC1_GUANG_INO_Config();				//光照初始化
	TIM4_PWM_Init(200-1,8400-1);		//舵机模块初始化
	//OLED2PWM_Init(10000-1,84-1);
	FINGER_Init();									//指纹模块初始化
	key_4x4_init();
	TIMER12_CH2_PWM_PB15_Config();	//pwm风扇初始化
	INTERRUPT_KEY1_Config();				//按键1-4初始化函数
	INTERRUPT_KEY2_Config();
	INTERRUPT_KEY3_Config();
	INTERRUPT_KEY4_Config();
	setWifi();
	printf("函数初始化完毕...");
	
		//创建开始任务函数
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄 								
		//开启任务调度函数
    vTaskStartScheduler();       
}
 
//2 开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
    //创建LED1任务
    xTaskCreate((TaskFunction_t )led3_task,     	
                (const char*    )"led3_task",   	
                (uint16_t       )LED3_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED3_TASK_PRIO,	
                (TaskHandle_t*  )&LED3Task_Handler); 				
    //创建按键扫描任务(多级oled菜单任务)
    xTaskCreate((TaskFunction_t )KEY_task,     
                (const char*    )"KEY_task",   
                (uint16_t       )EKY_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )KEY_TASK_PRIO,
                (TaskHandle_t*  )&KEYTask_Handler);
    //创建LED2任务
    xTaskCreate((TaskFunction_t )getdata_task,     
                (const char*    )"led2_task",   
                (uint16_t       )DATA_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )DATA_TASK_PRIO,
                (TaskHandle_t*  )&DATAtask_Handler);        
    //浮点测试任务
    xTaskCreate((TaskFunction_t )float_task,     
                (const char*    )"float_task",   
                (uint16_t       )FLOAT_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )FLOAT_TASK_PRIO,
                (TaskHandle_t*  )&FLOATTask_Handler);  
			//密码键盘任务
		 xTaskCreate((TaskFunction_t )passwd_task,     
                (const char*    )"passwd_task",   
                (uint16_t       )PASSWD_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )PASSWD_TASK_PRIO,
                (TaskHandle_t*  )&PASSWDTask_Handler); 
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

//3 LED3闪烁系统正常运行
void led3_task(void *pvParameters)
{
    while(1)
    { 
				LED_TurnOff(3);
        vTaskDelay(1000);
        LED_TurnOn(3);
        vTaskDelay(1000);
				//TIM_SetCompare4(TIM4,15);  
    }
}   

//4.数据采集任务函数
void getdata_task(void *pvParameters)
{
    while(1)
    {
				getdata();							//读取外界数据
				senddata();							//发送数据到物业
				vTaskDelay(8000);
    }
}


//5 指纹测试任务 
void float_task(void *pvParameters)
{	
	while(1)
	{
			  if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8))  
        {  
            TIM_SetCompare4(TIM4,5);
						LED_TurnOn(1);
        }
				else{
						TIM_SetCompare4(TIM4,15);
						LED_TurnOff(1);
				}
        vTaskDelay(10);  
   } 
} 
//按键任务函数
void KEY_task(void *pvParameters)
{  
    while(1)
    {
      Menu_key_set();
			if(buff[2]<30)
			{
			 	BEEP = state[1];
			}				
      vTaskDelay(10);
      			
    }
}
char passwd[128] = "22";
char userpasswd[128] = "";
int i = 0;	
void passwd_task(void *pvParameters)
{  
	while(1)
	{
	 char key = key_4x4_scan(); 
	 if (key != KEY_NONE && key != 'D') 
    {  
			 userpasswd[i++]=key;
		   printf("%c\n\r",key);
			 key = KEY_NONE;
		}
		else if(key == 'D')
		{
		   printf("%s\n\r",userpasswd);
			userpasswd[i] = '\0';
			if (strcmp(userpasswd,passwd) == 0)
			{ 
				Beep_Open(); 
				TIM_SetCompare4(TIM4,5);
				vTaskDelay(1000);
				printf("yes");
			}
			else
			{
			Beep_Alarm();
			printf("no");
			}
       userpasswd[0] = '\0';
       i = 0;			
		}
		vTaskDelay(100);
	}
}
