#include <stdbool.h>
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "MatrixKey.h"
#include "ad.h"
#include "timer.h"
#include "pwm.h"
#include "esp8266.h"


 	extern int Serial_RxFlag;
	extern uint8_t Serial_RxData;
	int key_num;
	int flag_num;
	uint16_t advalue;
	float pwm_value;
	float CounterSensorNum;
	short tempurature;
	int n;
	float cm;
	
 int main(void)
 {	 
 
	u8 lcd_id[12];			//存放LCD ID字符串
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化
	LCD_Init();
	 Timer_Init();
	 AD_Init();
	 Matrix_ssKey_Pin_Init();
	POINT_COLOR=RED;
	//sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。
 LCD_Clear(WHITE); 

  	while(1) 
	{		

		uint16_t advalue=AD_GetValue();
	uint16_t	pwm_value=(float)advalue/4095*100;
		
		LCD_ShowString(0,0,16*14,16,16,"Alcohol Concentration:");
//		LCD_ShowNum(175,0,pwm_value,4,16); //显示酒精浓度
//		LCD_ShowString(0,30,16*8,16,16,"Trigger Point:");
//		LCD_ShowNum(120,30,Danger_Val,4,16); //显示警报值
//		LCD_ShowString(0,60,16*4,16,16,"State:");//当前状态
//		
//		printf("酒精浓度：%d\r\n",pwm_value);
//	
		
		key_num=Matrix_Key_Scan();
			switch(key_num){
			case 0:
			break;
			case 1:
			
			flag_num=1;
			break;
			case 2:

			flag_num=2;
			break;
			case 3:
			flag_num=3;
			break;
			case 4:
			flag_num=4;
			break;
			case 5:
			flag_num=5;
			 break;
			case 6:
			flag_num=6;
			break;
			case 7:
			flag_num=7;
			break;
			case 8:
			flag_num=8;
			break;
			case 9:
			flag_num=9;
			break;
			case 10:
			flag_num=10;
			break;
			case 11:
			flag_num=11;
			break;
			case 12:
			flag_num=12;
			break;
			case 13:			
			flag_num=13;
			break;
			case 14:
			flag_num=14;
			break;
			case 15:
			flag_num=15;
			break;
			flag_num=15;
			break;
			default:
			break;
			}
			switch(flag_num){
			case 0:
			break;
			case 1:
			break;
			case 2:
			break;
			case 3:
			break;
			case 4:
			break;
			case 5:
			break;
			case 6:
			break;
			case 7:
			break;
			case 8:
			break;
			case 9:
			break;
			case 10:
			break;
			case 11:
			break;
			case 12:
			break;
			case 13:
			break;
			case 14:
			break;
			case 15:
			break;
			case 16:
			break;
			default: break;
			}
		while(key_num!=0){key_num=Matrix_Key_Scan();}
		
		
	} 
}
