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
 
	u8 lcd_id[12];			//���LCD ID�ַ���
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
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
	//sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣
 LCD_Clear(WHITE); 
	 Danger_Val=50;//����ֵ��ʼ��Ϊ50
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
		LCD_ShowNum(175,0,pwm_value,4,16); //��ʾ�ƾ�Ũ��
		LCD_ShowString(0,30,16*8,16,16,"Trigger Point:");
		LCD_ShowNum(120,30,Danger_Val,4,16); //��ʾ����ֵ
		LCD_ShowString(0,60,16*4,16,16,"State:");//��ǰ״̬
		
		printf("�ƾ�Ũ�ȣ�%d\r\n",pwm_value);
		if(pwm_value<Danger_Val)
		{
			LCD_ShowString(60,60,16*4,16,16,"Normal");//����
		}
		else
		{
			LCD_ShowString(60,60,16*4,16,16,"DUI   ");//����
		}
		LCD_ShowString(0,90,16*8,16,16,"Reset Trigger:");//�������þ���ֵ
		if(Set_Mode==1)
		{
			LCD_ShowString(120,90,16*4,16,16,"Yes");//��ǰ״̬
		}
		else
		{
			LCD_ShowString(120,90,16*4,16,16,"NO ");//��ǰ״̬
		}
		
			LCD_ShowString(0,120,16*6,16,16,"Trigger Num:");//����
			LCD_ShowNum(95,120,Set_Arr[0],4,16); //��һλ
			LCD_ShowNum(130,120,Set_Arr[1],4,16); //�ڶ�λ

		key_num=Matrix_Key_Scan();

		if(Set_Mode==1)//���뿪ʼ
		{
			if(key_num>0&&key_num<10){
			Set_Arr[Set_Val_Num]=key_num;
			Set_Val_Num++;
			Set_Mode2=2;
			
		}
		}
		
		if(Set_Mode2==2)
		{
			if(key_num==14)//����ֹͣ
			{
				
				if(Set_Val_Num==0) //δ���뾯��ֵ
				{}
				else if(Set_Val_Num==1)//����һ������
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
				//�޸ľ���ֵ
			Set_Mode=1;
			
			flag_num=13;
			break;
			case 14:
				//ֹͣ����
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
