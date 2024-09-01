#include "user.h"
//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);


//2.�ɼ���������
//�������ȼ�
#define DATA_TASK_PRIO		3
//�����ջ��С	
#define DATA_STK_SIZE 		200  
//������
TaskHandle_t DATAtask_Handler;
//������
void getdata_task(void *pvParameters);

//����ɨ������
//�������ȼ�
#define KEY_TASK_PRIO		5
//�����ջ��С	
#define EKY_STK_SIZE 		200  
//������
TaskHandle_t KEYTask_Handler;
//������
void KEY_task(void *pvParameters);

//LED3��˸����
//�������ȼ�
#define LED3_TASK_PRIO		4
//�����ջ��С	
#define LED3_STK_SIZE 		50  
//������
TaskHandle_t LED3Task_Handler;
//������
void led3_task(void *pvParameters);


//�������ȼ�
#define FLOAT_TASK_PRIO		2
//�����ջ��С	
#define FLOAT_STK_SIZE 		128
//������
TaskHandle_t FLOATTask_Handler;
//������
void float_task(void *pvParameters);


//�������ȼ�
#define PASSWD_TASK_PRIO		6
//�����ջ��С	
#define PASSWD_STK_SIZE 		200
//������
TaskHandle_t PASSWDTask_Handler;
//������
void passwd_task(void *pvParameters);

extern EventGroupHandle_t  statehandle;

extern char buff[5];
extern unsigned char state[4];
extern unsigned short int lightint;
//1.������
int main(void)
{ 
	//����ϵͳ�ж����ȼ�����4
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	delay_init(168);								//��ʱ������ʼ��
	uart_init(115200);     					//���ڳ�ʼ��
	uart2init(115200);							//���ڶ���ʼ��
	LED_Init();		       						//LED1-3��ʼ��
	BEEP_Config();									//��������ʼ��
	Key_Config();										//����1-3��ʼ��
	KEY_4_Config();									//����4��ʼ��
	scanfkey();											//��������ʼ��				
	IIC_Config();										//IIC��ʼ��	
	DHT11_Config();									//��ʪ�ȳ�ʼ��
	OLED_Init();										//OLED��Ļ��ʼ��
	My_RTC_Init();									//ʱ�ӳ�ʼ��
	ADC1_GUANG_INO_Config();				//���ճ�ʼ��
	TIM4_PWM_Init(200-1,8400-1);		//���ģ���ʼ��
	//OLED2PWM_Init(10000-1,84-1);
	FINGER_Init();									//ָ��ģ���ʼ��
	key_4x4_init();
	TIMER12_CH2_PWM_PB15_Config();	//pwm���ȳ�ʼ��
	INTERRUPT_KEY1_Config();				//����1-4��ʼ������
	INTERRUPT_KEY2_Config();
	INTERRUPT_KEY3_Config();
	INTERRUPT_KEY4_Config();
	setWifi();
	printf("������ʼ�����...");
	
		//������ʼ������
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������ 								
		//����������Ⱥ���
    vTaskStartScheduler();       
}
 
//2 ��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
    //����LED1����
    xTaskCreate((TaskFunction_t )led3_task,     	
                (const char*    )"led3_task",   	
                (uint16_t       )LED3_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED3_TASK_PRIO,	
                (TaskHandle_t*  )&LED3Task_Handler); 				
    //��������ɨ������(�༶oled�˵�����)
    xTaskCreate((TaskFunction_t )KEY_task,     
                (const char*    )"KEY_task",   
                (uint16_t       )EKY_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )KEY_TASK_PRIO,
                (TaskHandle_t*  )&KEYTask_Handler);
    //����LED2����
    xTaskCreate((TaskFunction_t )getdata_task,     
                (const char*    )"led2_task",   
                (uint16_t       )DATA_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )DATA_TASK_PRIO,
                (TaskHandle_t*  )&DATAtask_Handler);        
    //�����������
    xTaskCreate((TaskFunction_t )float_task,     
                (const char*    )"float_task",   
                (uint16_t       )FLOAT_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )FLOAT_TASK_PRIO,
                (TaskHandle_t*  )&FLOATTask_Handler);  
			//�����������
		 xTaskCreate((TaskFunction_t )passwd_task,     
                (const char*    )"passwd_task",   
                (uint16_t       )PASSWD_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )PASSWD_TASK_PRIO,
                (TaskHandle_t*  )&PASSWDTask_Handler); 
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

//3 LED3��˸ϵͳ��������
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

//4.���ݲɼ�������
void getdata_task(void *pvParameters)
{
    while(1)
    {
				getdata();							//��ȡ�������
				senddata();							//�������ݵ���ҵ
				vTaskDelay(8000);
    }
}


//5 ָ�Ʋ������� 
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
//����������
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
