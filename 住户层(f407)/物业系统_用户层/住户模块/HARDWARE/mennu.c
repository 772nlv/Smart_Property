#include "user.h"
#include "bmp.h"
extern char humi[3]; //湿度字符串
extern char temp[3];//温度字符串
extern unsigned short int guangnum; //光照
unsigned char keynum=0; 
char date[20]; 
char time[20];
EventGroupHandle_t  statehandle=0;
unsigned char func_index = 0;	//主程序此时所在函数的索引值
unsigned char control_index=0;//设置-->及led2,beep,pwm的索引值
unsigned char state[4]={0,0,0,0};//设置led2,beep,pwm的状态

RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;


void (* current_operation_index)(void);

 Menu_table  table[30]=
{
    {0,0,1,0,(*home)},	//一级界面（主页面） 索引，向下一个，确定(进入下一级)，退出
		
    {1,2,5,0,(*Temperature)},	//二级界面 温湿度
    {2,3,6,0,(*light)},	//二级界面 光照强度
    {3,4,7,0,(*Setting)},	//二级界面 设置
    {4,1,8,0,(*Info)},	//二级界面   信息
		 
	  {5,5,5,1,(*TestTemperature)},		//三级界面：DHT11测量温湿度
	  {6,6,6,2,(*TestLight)},				//三级界面：查看光敏电阻值
	  {7,7,7,3,(*Set)},								//三级界面：设置普通外设状态 LED，BEEP,PWM
	  {8,8,9,4,(*Information)},				//三级界面：作者和相关项目信息
		
		{9,9,9,8,(*gif)},
};

void  Menu_key_set(void)
{
	keynum=scanfkey();
if(keynum)
 {
	  if((keynum == 1) && (func_index != 7))        //屏蔽掉索引7下的情况
  { 
    func_index=table[func_index].next;	//按键next按下后的索引号
    OLED_Clear(); 
  }
	
  else if((keynum == 2) && (func_index != 7))
  {
    func_index=table[func_index].enter;	//按键enter按下后的索引号
    OLED_Clear();
  }
	
	else if(keynum == 3)
  {
		control_index=0;
    func_index=table[func_index].back;	//按键back按下后的索引号
    OLED_Clear(); 
  }
	else if((keynum == 1) && (func_index == 7))
	{
	  control_index++;
	}
		else if((keynum == 2) && (func_index == 7))
	{
	  state[control_index]=!state[control_index];
	}
 }
  RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
	//获取RTC时间
	sprintf(time,"%02d:%02d:%02d",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds); 
	
  current_operation_index=table[func_index].current_operation;	//执行当前索引号所对应的功能函数
  current_operation_index();//执行当前操作函数
}

void home(void)
{
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
	//获取RTC日期
	sprintf(date,"20%02d-%02d-%02d",RTC_DateStruct.RTC_Year,RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date); 
  OLED_ShowPicture(0,0,128,64,BMP1,1);
  
  OLED_ShowString(16,12,(unsigned char *)time,24,1);
	
  OLED_ShowString(34,36,(unsigned char *)date,12,1);
	
	OLED_Refresh();
}
void Temperature(void)
{
  OLED_ShowPicture(0,0,128,64,bmp_temp,1);
	OLED_ShowString(38,0,(unsigned char *)time,12,1);
  OLED_Refresh();
}
void light(void)
{
  OLED_ShowPicture(0,0,128,64,bmp_light,1);
	OLED_ShowString(38,0,(unsigned char *)time,12,1);
	OLED_Refresh();
}
void Setting(void)
{
 OLED_ShowPicture(0,0,128,64,bmp_set,1);	
 OLED_ShowString(38,0,(unsigned char *)time,12,1);
 OLED_Refresh();
}
void Info(void)
{
 OLED_ShowPicture(0,0,128,64,bmp_info,1);
 OLED_ShowString(38,0,(unsigned char *)time,12,1);
 OLED_Refresh();
}
 

void TestTemperature(void)
{	
	 char tempStr[10], humiStr[10];
  sprintf(tempStr,"%d.%d", temp[0],temp[1]); // 将温度转换为字符串  
  sprintf(humiStr,"%d.%d", humi[0],humi[1]); // 将湿度转换为字符串  
	OLED_ShowString(32,0,(unsigned char *)time,16,1);
	OLED_ShowString(0,16,"temp:",16,1);
	OLED_ShowString(50, 16, (unsigned char *)tempStr, 16, 1);
	OLED_ShowString(0,32,"humi:",16,1); 
	OLED_ShowString(50, 32, (unsigned char *)humiStr, 16, 1); 
	OLED_ShowString(0,48,"threshold:30.0",16,1);
	OLED_Refresh();	
	
}
void TestLight(void)
{	
	char str[20]={0};
	sprintf(str, "%d", guangnum);  
	OLED_ShowString(0,16,"light:",16,1); 
	OLED_ShowString(50,16,(unsigned char *)str,16,1);
	OLED_ShowString(0,48,"threshold:2000lx",16,1);
	OLED_Refresh();	
}

void Set(void)
{
 
 OLED_ShowString(32,0,"led1",16,1);
 OLED_ShowString(32,16,"beep",16,1);
 OLED_ShowString(32,32,"fans",16,1);
 OLED_ShowString(32,48,"led2",16,1);
 OLED_ShowString(0,(control_index-1)*16,(unsigned char *)"    ",16,1);
 control_index=control_index%4;
 OLED_ShowString(0,control_index*16,(unsigned char *)"--> ",16,1);
 for(int i=0;i<4;i++)
  {
	 if(state[i]==0){
	  OLED_ShowString(104,i*16,(unsigned char *)"OFF",16,1);
	 }
	 else
	 {
	  OLED_ShowString(104,i*16,(unsigned char *)" ON",16,1);
	 }
 }
	if(state[3]==1){
	xEventGroupSetBits(statehandle,1<<0);
	}
	else{
	xEventGroupClearBits(statehandle,1<<0);
	TIM_SetCompare2(TIM1,0);
	}
 OLED_Refresh();	
}

void Information(void)
{
	OLED_ShowChinese(0,0,0,16,1);//作
	OLED_ShowChinese(16,0,1,16,1);//者
	OLED_ShowString(20,24,(unsigned char *)"TianMY",16,1);
	
	
	OLED_ShowString(0,48,(unsigned char *)"version:1.0",8,1);
	OLED_ShowString(0,56,(unsigned char *)"date:2023-12-16",8,1);
	OLED_Refresh();	
	
}
unsigned  char bmp_index=0;
void gif(void)
{
 OLED_ShowPicture(0,0,128,64,bmp_tai[bmp_index],0);
 bmp_index=(bmp_index+1)%20;
 delay_xms(50);
 OLED_Refresh();	
}
