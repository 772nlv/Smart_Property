#include "user.h"
//�¶ȡ�ʪ������

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
//������־
extern int SYSTEM_ON_FLAG;
int SYSTEM_ON_FLAG = 0;
extern char Client_Data[24];
//�ɼ�����״̬λ
extern int COLLECT_DATA_ON_FLAG;
int COLLECT_DATA_ON_FLAG = 1;

//PWM����������״̬λ
extern int PWM_BEEP_flag;
int PWM_BEEP_flag = 0;
//w25q128 �Լ� a24c04��ȡ��������
extern int flg ;
//------������
//�������
//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);



//-------------LED3��˸
//�������ȼ�
#define LIGHT_TASK_PRIO		4
//�����ջ��С	
#define LIGHT_STK_SIZE 		50  
//������
TaskHandle_t LIGHTTask_Handler;
//������
void light_task(void *pvParameters);

//-------------��������
//�������ȼ�
//#define SYSN6288_TASK_PRIO		4
////�����ջ��С	
//#define SYSN6288_STK_SIZE 		50  
////������
//TaskHandle_t SYSN6288Task_Handler;
////������
//void syn6288_task(void *pvParameters);

//-------------��ȡ��Ϣ
//�������ȼ�
#define GETCLIENT_TASK_PRIO		4
//�����ջ��С	
#define GETCLIENT_STK_SIZE 		50  
//������
TaskHandle_t GETCLIENTTask_Handler;
//������
void GetClient_task(void *pvParameters);

//-------------����
////�������ȼ�
//#define ALARM_TASK_PRIO		4
////�����ջ��С	
//#define ALARM_STK_SIZE 		50  
////������
//TaskHandle_t ALARMTask_Handler;
////������
//void alarm_task(void *pvParameters);

int main()
{
	//�жη��麯��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	//��ʼ��LED��
	LED_config();
	//�ӳٳ�ʼ��
	delay_init(168);
	//��ʼ��BEEP
	BEEP_Config();
	//1����ʼ������__PE_456
	KEY1_2_3_Config();
	//��ʼ��key4
	KEY4_Config();
	//���ڳ�ʼ��
	USART1_Config();
	uart2init();
	//�жϳ�ʼ��
	INTERRUPT_KEY1_Config();
	INTERRUPT_KEY2_Config();
	INTERRUPT_KEY3_Config();
	INTERRUPT_KEY4_Config();
  uart6_init();
	//��ʼ��IIC
	IIC_Config();
	InitOLed();
	//��ʼ��wifi
	setWifi();
  //LCD��ʼ��
	LCD_Init();
	//��ʱʱ�䵽����ȡ��ʪ��
	//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
}

//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
							
				
	//LED3��˸
	xTaskCreate((TaskFunction_t )light_task,     
                (const char*    )"LED2_task",   
                (uint16_t       )LIGHT_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LIGHT_TASK_PRIO,
                (TaskHandle_t*  )&LIGHTTask_Handler);   
		
	//LED3��˸
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
								
								
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}



//��˸
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















