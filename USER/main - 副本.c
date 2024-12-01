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
	
	int Danger_Val;
	int Set_Mode=0;
	int Set_Mode2=0;
	int Set_Val_Num;
	int Set_Val;
	int Set_Arr[2]={0,0};
	int esp_flag=0;
 int main(void)
 {	 
 
	u8 lcd_id[12];			//存放LCD ID字符串
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化
	LCD_Init();
	 Timer_Init();
	// PWM_Init();
	// S_Init();
	// initH_();
	// CounterSensor_Init();
	 AD_Init();
	 Matrix_ssKey_Pin_Init();
	// d_init();
	POINT_COLOR=RED;
	//sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。
 LCD_Clear(WHITE); 
	 Danger_Val=50;//报警值初始化为50
  	while(1) 
	{		
		
		if(esp_flag==0)
		{
			if(my_esp8266_init()==1)
				esp_flag=1;
		}
		
		
		
		
		uint16_t advalue=AD_GetValue();
	uint16_t	pwm_value=(float)advalue/4095*100;
		LCD_ShowString(0,0,16*14,16,16,"Alcohol Concentration:");
		LCD_ShowNum(175,0,pwm_value,4,16); //显示酒精浓度
		LCD_ShowString(0,30,16*8,16,16,"Trigger Point:");
		LCD_ShowNum(120,30,Danger_Val,4,16); //显示警报值
		LCD_ShowString(0,60,16*4,16,16,"State:");//当前状态
		
		printf("酒精浓度：%d\r\n",pwm_value);
		if(pwm_value<Danger_Val)
		{
			LCD_ShowString(60,60,16*4,16,16,"Normal");//正常
		}
		else
		{
			LCD_ShowString(60,60,16*4,16,16,"DUI   ");//饮酒
		}
		LCD_ShowString(0,90,16*8,16,16,"Reset Trigger:");//重新设置警报值
		if(Set_Mode==1)
		{
			LCD_ShowString(120,90,16*4,16,16,"Yes");//当前状态
		}
		else
		{
			LCD_ShowString(120,90,16*4,16,16,"NO ");//当前状态
		}
		
			LCD_ShowString(0,120,16*6,16,16,"Trigger Num:");//数字
			LCD_ShowNum(95,120,Set_Arr[0],4,16); //第一位
			LCD_ShowNum(130,120,Set_Arr[1],4,16); //第二位

		key_num=Matrix_Key_Scan();

		if(Set_Mode==1)//输入开始
		{
			if(key_num>0&&key_num<10){
			Set_Arr[Set_Val_Num]=key_num;
			Set_Val_Num++;
			Set_Mode2=2;
			
		}
		}
		
		if(Set_Mode2==2)
		{
			if(key_num==14)//输入停止
			{
				
				if(Set_Val_Num==0) //未输入警报值
				{}
				else if(Set_Val_Num==1)//输入一个数字
				{
					Danger_Val=Set_Arr[0];
				}
				else if(Set_Val_Num==2)
				{
					Danger_Val=Set_Arr[0]*10+Set_Arr[1];
				}
				Set_Val_Num=0;
			}
		}
		 
		// printf("%d \n",pwm_value);
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
				//修改警报值
			Set_Mode=1;
			
			flag_num=13;
			break;
			case 14:
				//停止输入
			Set_Mode=0;
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
