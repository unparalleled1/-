#include "ds18b20.h"
#include "delay.h"
#include "stm32f10x_gpio.h"
void mode_output(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
GPIO_Init(GPIOG, &GPIO_InitStructure);
}
void mode_input(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
/* Configure Ports */
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
GPIO_Init(GPIOG, &GPIO_InitStructure);
}
void d_rst(void)
{
mode_output();        //���ģʽ
GPIO_ResetBits(GPIOG,GPIO_Pin_11);       //����DQ����
delay_us(600);     //��ʱ480-960us
GPIO_SetBits(GPIOG,GPIO_Pin_11);       //����DQ���� 
mode_input();
while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_11));     //�ȴ�����Ӧ���������ͣ���Լ15-60us��
while(!GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_11));    //Ӧ��������ֺ󣬵ȴ��������ߣ�Լ60-240us��
}
void d_write_zero(void)
{
mode_output();          //���ģʽ
GPIO_ResetBits(GPIOG,GPIO_Pin_11);          //��������
delay_us(80);       //��ʱ60-120us
GPIO_SetBits(GPIOG,GPIO_Pin_11);         //��������
delay_us(2);
}
void d_write_one(void)
{
mode_output();              //���ģʽ
	GPIO_ResetBits(GPIOG,GPIO_Pin_11);
delay_us(2);
GPIO_SetBits(GPIOG,GPIO_Pin_11);
delay_us(80);
}
unsigned char d_read_bit(void)
{
unsigned char data;
mode_output();
GPIO_ResetBits(GPIOG,GPIO_Pin_11);
delay_us(2);
GPIO_SetBits(GPIOG,GPIO_Pin_11);;
mode_input();
delay_us(5);
if(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_11))
 data=1;
else
 data=0;
delay_us(500); 
return data;
}
void d_write_byte(unsigned char data)
{
unsigned char i,testb;
mode_output();
for(i=0;i<8;i++)
{
 testb=data&0x01;         //�ӵ�λ��ʼд
 data>>=1;
 if(testb)
  d_write_one();
 else
  d_write_zero();
}
}
unsigned char d_read_byte(void)
{
unsigned char i,j,data=0;
for(i=0;i<8;i++)
{
 j=d_read_bit();
 data=(j<<7)|(data>>1);   //�ӵ�λ��ʼ��
}
return data;
}
void d_start(void)
{ 
d_rst(); 
	d_write_byte(0xcc);  // ����ROM
 d_write_byte(0x44);  //�¶�ת��
}
void d_init(void)
{
 mode_output();
mode_input();
d_rst();
}
short get_tempetature(void)
{
 unsigned char TL,TH;
 short tem;
 d_start();      //��ʼת��
 delay_us(700);       //�ȴ�ת�����
 d_init();  
 d_write_byte(0xcc);  //����ROM
 d_write_byte(0xbe);  //��ȡ�ݴ�Ĵ���  
 TL=d_read_byte();   //�Ͱ�λ
 TH=d_read_byte();   //�߰�λ��ע��ǰ��λΪ����λֻ��ȫΪ0��ʱ���¶�������   
 tem=TH;           //��ø߰�λ
 tem<<=8; 
 tem+=TL;           //��õװ�λ
 return tem/10-20;  
}