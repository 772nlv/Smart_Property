#include "user.h"
char bufs[50] = "";
char tempo[3] = "";
char tempo2[3] = "";
char humio[3] = "";
char humio2[3] = "";
char lighto[10] ="";
char lighto2[10] ="";
char vo[10] ="";
char vo2[10] ="";
void showat24c02hisdata()
{			
			OLed_Fill(0);
			//顶部数据标识符
			Oled_print(0,0,"T:");
			Oled_print(0,2,"H:");
			Oled_print(0,4,"lT:");
			Oled_print(0,6,"V:");
			//读取数据出来
			bufs[0] = AT24c02_read_bytes(0);
			bufs[1] = AT24c02_read_bytes(1);
			bufs[2] = AT24c02_read_bytes(2);
			bufs[3] = AT24c02_read_bytes(3);
			bufs[4] = AT24c02_read_bytes(4);
			bufs[5] = AT24c02_read_bytes(5);
			bufs[6] = AT24c02_read_bytes(6);
			bufs[7] = AT24c02_read_bytes(7);
			sprintf(tempo,"%u",bufs[0]);
			sprintf(tempo2,"%u",bufs[1]);
			sprintf(humio,"%u",bufs[2]);
			sprintf(humio2,"%u",bufs[3]);
			sprintf(lighto,"%u",bufs[4]);
			sprintf(lighto2,"%u",bufs[5]);
			sprintf(vo,"%u",bufs[6]);
			sprintf(vo2,"%u",bufs[7]);
			Oled_print(20,0,tempo);
			Oled_print(35,0,".");
			Oled_print(45,0,tempo2);
			
			Oled_print(20,2,humio);
			Oled_print(35,2,".");
			Oled_print(45,2,humio2);
			
			Oled_print(25,4,lighto);
			Oled_print(42,4,lighto2);
			
			Oled_print(25,6,vo);
			Oled_print(35,6,vo2);
}
char tempbuf1[128] = "";
char wtemp1[3] = "";
char wtemp2[3] = "";
char whumi[3] = "";
char whumi2[3] = "";
char wlight[3] = "";
char wlight2[3] = "";
char wv1[3] = "";
char wv2[3] = "";
int readflag = 1;
void show_w25q64hisdata()
{
			OLed_Fill(0);
			//顶部数据标识符
			Oled_print(0,0,"T:");
			Oled_print(0,2,"H:");
			Oled_print(0,4,"lT:");
			Oled_print(0,6,"V:");
			//从w25读出数据	
			w25q128_read_data(0,tempbuf1,10);
			sprintf(wtemp1,"%u",tempbuf1[0]);
			sprintf(wtemp2,"%u",tempbuf1[1]);
			sprintf(whumi,"%u",tempbuf1[2]);
			sprintf(whumi2,"%u",tempbuf1[3]);
			sprintf(wlight,"%u",tempbuf1[4]);
			sprintf(wlight2,"%u",tempbuf1[5]);
			sprintf(wv1,"%u",tempbuf1[6]);
			sprintf(wv2,"%u",tempbuf1[7]);
			//printf("%d",tempbuf1[0]);;
//			wtemp1[2] = tempbuf1[0];
//			wtemp2[2] = tempbuf1[1];
			Oled_print(20,0,wtemp1);
			Oled_print(35,0,".");
			Oled_print(45,0,wtemp2);
			
			Oled_print(20,2,whumi);
			Oled_print(35,2,".");
			Oled_print(45,2,whumi2);
			
			Oled_print(25,4,"1200");
//			Oled_print(25,4,wlight);
//			Oled_print(40,4,wlight2);
			
			Oled_print(25,6,"560");
//			Oled_print(20,6,wv1);
//			Oled_print(32,6,wv2);
			//printf("end");
}
