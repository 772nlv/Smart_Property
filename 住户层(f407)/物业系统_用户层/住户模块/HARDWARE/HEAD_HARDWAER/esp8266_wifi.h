#ifndef __ESP8266_WIFI_H
#define __ESP8266_WIFI_H


void uart2init(u32 bound);
void usart_sendstr(USART_TypeDef * USATRX , char * str,int size);
void setWifi(void);
void senddata(void);


#endif
