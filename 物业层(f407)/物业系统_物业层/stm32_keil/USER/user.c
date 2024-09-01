#include "user.h"
//温度、湿度数组

unsigned short ret = 0;
extern char tempvalue_1[128];
extern char humivalue_1[128];
extern char lihgtvalue_1[128];
extern char potenvalue_1[128];
extern char Client_temp[2];

extern uint8_t HZ66[];
extern uint8_t HZ67[];
extern uint8_t HZ68[];
extern uint8_t HZ69[];
extern uint8_t HZ50[];
extern uint8_t HZ51[];
	
char tempvalue_1[128] = {0};
char humivalue_1[128] = {0};
char lihgtvalue_1[128] = {0};
char potenvalue_1[128] = {0};
char passwd[128] = "123456";
char temp[2] = "";
char humi[2] = "";
char Send_Client_Data_Buff[13] = "";
extern int PWM_LED2_flag;
extern int Index_1;
extern int _dsd;
//开机标志
extern int SYSTEM_ON_FLAG;
int SYSTEM_ON_FLAG = 0;
extern char Client_Data[24];
//采集数据状态位
extern int COLLECT_DATA_ON_FLAG;
int COLLECT_DATA_ON_FLAG = 1;

//PWM蜂鸣器数据状态位
extern int PWM_BEEP_flag;
int PWM_BEEP_flag = 0;
//w25q128 以及 a24c04读取数据数组
extern int flg ;
//------父任务
//任务调度
//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);



//-------------LED3闪烁
//任务优先级
#define LIGHT_TASK_PRIO		4
//任务堆栈大小	
#define LIGHT_STK_SIZE 		50  
//任务句柄
TaskHandle_t LIGHTTask_Handler;
//任务函数
void light_task(void *pvParameters);

//-------------语音播报
//任务优先级
//#define SYSN6288_TASK_PRIO		4
////任务堆栈大小	
//#define SYSN6288_STK_SIZE 		50  
////任务句柄
//TaskHandle_t SYSN6288Task_Handler;
////任务函数
//void syn6288_task(void *pvParameters);

//-------------获取信息
//任务优先级
#define GETCLIENT_TASK_PRIO		4
//任务堆栈大小	
#define GETCLIENT_STK_SIZE 		50  
//任务句柄
TaskHandle_t GETCLIENTTask_Handler;
//任务函数
void GetClient_task(void *pvParameters);

//-------------警报
////任务优先级
//#define ALARM_TASK_PRIO		4
////任务堆栈大小	
//#define ALARM_STK_SIZE 		50  
////任务句柄
//TaskHandle_t ALARMTask_Handler;
////任务函数
//void alarm_task(void *pvParameters);

int main()
{
	//中段分组函数
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	//初始化LED；
	LED_config();
	//延迟初始化
	delay_init(168);
	//初始化BEEP
	BEEP_Config();
	//1、初始化按键__PE_456
	KEY1_2_3_Config();
	//初始化key4
	KEY4_Config();
	//串口初始化
	USART1_Config();
	uart2init();
	//中断初始化
	INTERRUPT_KEY1_Config();
	INTERRUPT_KEY2_Config();
	INTERRUPT_KEY3_Config();
	INTERRUPT_KEY4_Config();
  uart6_init();
	//初始化IIC
	IIC_Config();
	InitOLed();
	//初始化wifi
	setWifi();
  //LCD初始化
	LCD_Init();
	//计时时间到，读取温湿度
	//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度
}

//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
							
				
	//LED3闪烁
	xTaskCreate((TaskFunction_t )light_task,     
                (const char*    )"LED2_task",   
                (uint16_t       )LIGHT_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LIGHT_TASK_PRIO,
                (TaskHandle_t*  )&LIGHTTask_Handler);   
		
	//LED3闪烁
//	xTaskCreate((TaskFunction_t )syn6288_task,     
//                (const char*    )"sysn6288_task",   
//                (uint16_t       )SYSN6288_STK_SIZE, 
//                (void*          )NULL,
//                (UBaseType_t    )SYSN6288_TASK_PRIO,
//                (TaskHandle_t*  )&SYSN6288Task_Handler);  
								
									//
	xTaskCreate((TaskFunction_t )GetClient_task,     
                (const char*    )"GetClient_task",   
                (uint16_t       )GETCLIENT_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )GETCLIENT_TASK_PRIO,
                (TaskHandle_t*  )&GETCLIENTTask_Handler); 
								
//	xTaskCreate((TaskFunction_t )alarm_task,     
//                (const char*    )"alarm_task",   
//                (uint16_t       )ALARM_STK_SIZE, 
//                (void*          )NULL,
//                (UBaseType_t    )ALARM_TASK_PRIO,
//                (TaskHandle_t*  )&ALARMTask_Handler); 
								
								
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}



//闪烁
void light_task(void *pvParameters)
{  
	while(1)
	{
	OLed_Fill(0);
	Start_screen();
	English_Font_test();
	vTaskDelay(1000);
	}	
	
}

//void syn6288_task(void *pvParameters)
//{
//	while(1)
// {
// vTaskDelay(1000);
// }
//}

void GetClient_task(void *pvParameters)
{
  while(1)
  {
	   int i1 = 0;	
		 if(_dsd == 1)
		{	
			
			for(int i = 0; i < 24 ; i ++)
			{	
			  if(i >= 12)
				{
					Send_Client_Data_Buff[i1] = Client_Data[i];
			    i1++;
					flg = 1;
				}
      }
			Show_Client_Data();
			
			  if(flg == 1)
      {
				Send_Client_Data();
			}		
      _dsd = 0; 
			Index_1 = 0;
		}
		vTaskDelay(200);
	}
}


//void alarm_task(void *pvParameters)
//{

//  while(1)
//	{
//	  vTaskDelay(200);
//	}



//}















