 #include "stm32f10x.h"                  // Device header
#include "delay.h"
  
//R4--PF1 //R3--PF2 //R2--PF3 //R1--PF4 //C1--PF5 //C2--PF6 //C3--PF7 //C4--PF8 
void Matrix_ssKey_Pin_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; 
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_Init(GPIOF,&GPIO_InitStructure);
}	

int Matrix_Key_Scan(void)
{
	GPIO_ResetBits(GPIOF,GPIO_Pin_1);	
	GPIO_SetBits(GPIOF,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);
	if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5) == 0)
	{
		delay_ms(5);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5) == 0)
			return 4;
		else
			return 0;
	}
	else if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6) == 0)
	{
		delay_ms(5);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6) == 0)
			return 3;
		else
			return 0;
	}
		else if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7) == 0)
	{
		delay_ms(5);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7) == 0)
			return 2;
		else
			return 0;
	}
		else if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8) == 0)
	{
		delay_ms(5);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8) == 0)
			return 1;
		else
			return 0;
	}
	
	GPIO_ResetBits(GPIOF,GPIO_Pin_2);	
	GPIO_SetBits(GPIOF,GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4);
	if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5) == 0)
	{
		delay_ms(5);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5) == 0)
			return 8;
		else
			return 0;
	}
	else if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6) == 0)
	{
		delay_ms(5);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6) == 0)
			return 7;
		else
			return 0;
	}
		else if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7) == 0)
	{
		delay_ms(5);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7) == 0)
			return 6;
		else
			return 0;
	}
		else if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8) == 0)
	{
		delay_ms(5);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8) == 0)
			return 5;
		else
			return 0;
	}
	
	GPIO_ResetBits(GPIOF,GPIO_Pin_3);	
	GPIO_SetBits(GPIOF,GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_4);
	if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5) == 0)
	{
		delay_ms(5);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5) == 0)
			return 12;
		else
			return 0;
	}
	else if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6) == 0)
	{
		delay_ms(5);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6) == 0)
			return 11;
		else
			return 0;
	}
		else if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7) == 0)
	{
		delay_ms(5);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7) == 0)
			return 10;
		else
			return 0;
	}
		else if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8) == 0)
	{
		delay_ms(5);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8) == 0)
			return 9;
		else
			return 0;
	}
	
	GPIO_ResetBits(GPIOF,GPIO_Pin_4);	
	GPIO_SetBits(GPIOF,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_1);
	if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5) == 0)
	{
		delay_ms(5);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5) == 0)
			return 16;
		else
			return 0;
	}
	else if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6) == 0)
	{
		delay_ms(5);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6) == 0)
			return 15;
		else
			return 0;
	}
		else if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7) == 0)
	{
		delay_ms(5);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7) == 0)
			return 14;
		else
			return 0;
	}
		else if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8) == 0)
	{
		delay_ms(5);
		if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8) == 0)
			return 13;
		else
			return 0;
	}
	else
		return 0;
//	delay_us(10);
// 
//	temp=(GPIO_ReadInputData(GPIOF) >> 8)&0xff;	
//	
//	//没有按键按下时扫描
//	if (temp == 0xf0) 
//	{
//			delay_ms(50); 
//			GPIO_ResetBits(GPIOF,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);			//拉低行线
//			delay_us(10);
//			temp=(GPIO_ReadInputData(GPIOF) >> 8)&0xff;	
//		
//			if (temp != 0xf0) //按键按下时，对键值进行赋值
//			{
//				//第一行
//				GPIO_Write(GPIOF,0);
//				delay_ms(5);
//				GPIO_Write(GPIOF,(uint16_t)(0xFE << 8)); 
//				
//				if(((GPIO_ReadInputData(GPIOF) >> 8) & 0XF0) != 0XF0)
//				{
//						delay_ms(20);//消抖
// 
//						if(((GPIO_ReadInputData(GPIOF) >> 8) & 0XF0) != 0XF0)
//						{
//								temp=((GPIO_ReadInputData(GPIOF) >> 8) & 0XFE);		//对列进行扫描
//								switch(temp)
//								{
//										case 0xEE:  key_val = 1;   break;
//										case 0xDE:  key_val = 2;   break;
//										case 0xBE:  key_val = 3;   break;
//										case 0x7E:  key_val = 4;   break;
//										default:    key_val = -1;   break;
//								}
//						}
//				}
//				
//				//第二行
//				GPIO_Write(GPIOF,0);
//				delay_ms(5);
//				GPIO_Write(GPIOF,(uint16_t)(0xFD << 8));
//				
//				if(((GPIO_ReadInputData(GPIOF) >> 8) & 0XF0)!= 0XF0)
//				{
//						delay_ms(20);
// 
//						if(((GPIO_ReadInputData(GPIOF) >> 8) & 0XF0) != 0XF0)
//						{
//								temp=((GPIO_ReadInputData(GPIOF) >> 8) & 0XFD);
//								switch(temp)
//								{
//										case 0xED:  key_val = 5;   break;
//										case 0xDD:  key_val = 6;   break;
//										case 0xBD:  key_val = 7;   break;
//										case 0x7D:  key_val = 8;   break;
//										default:    key_val = -1;   break;
//								}
//						}
//				}
//				
//				//第三行
//				GPIO_Write(GPIOF,0);
//				delay_ms(5);
//				GPIO_Write(GPIOF,(uint16_t)(0xFB << 8));
//				
//				if(((GPIO_ReadInputData(GPIOF) >> 8) & 0XF0) != 0XF0)
//				{
//						delay_ms(20);
// 
//						if(((GPIO_ReadInputData(GPIOF) >> 8) & 0XF0) != 0XF0)
//						{
//								temp=((GPIO_ReadInputData(GPIOF) >> 8) & 0XFB);
//								switch(temp)
//								{
//										case 0xEB:  key_val = 9;   break;
//										case 0xDB:  key_val = 10;   break;
//										case 0xBB:  key_val = 11;   break;
//										case 0x7B:  key_val = 12;   break;
//										default:    key_val = -1;   break;
//								}
//						}
//				}
//				
//				//第四行
//				GPIO_Write(GPIOF,0);
//				delay_ms(5);
//				GPIO_Write(GPIOF,(uint16_t)(0xF7 << 8));
//				
//				if(((GPIO_ReadInputData(GPIOF) >> 8) & 0XF0) !=0XF0)
//				{
//						delay_ms(20);
// 
//						if(((GPIO_ReadInputData(GPIOF) >> 8) & 0XF0) != 0XF0)
//						{
//								temp=((GPIO_ReadInputData(GPIOF) >> 8) & 0XF7);
//								switch(temp)
//								{
//										case 0xE7:  key_val = 13;   break;
//										case 0xD7:  key_val = 14;   break;
//										case 0xB7:  key_val = 15;   break;
//										case 0x77:  key_val = 16;   break;
//										default:    key_val = -1;   break;
//								}
//						}
//					}
//				}
//			}
//	
//	return key_val;
 
}
