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
mode_output();        //输出模式
GPIO_ResetBits(GPIOG,GPIO_Pin_11);       //拉低DQ引脚
delay_us(600);     //延时480-960us
GPIO_SetBits(GPIOG,GPIO_Pin_11);       //拉高DQ引脚 
mode_input();
while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_11));     //等待器件应答（器件拉低），约15-60us后
while(!GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_11));    //应答脉冲出现后，等待器件拉高，约60-240us后
}
void d_write_zero(void)
{
mode_output();          //输出模式
GPIO_ResetBits(GPIOG,GPIO_Pin_11);          //拉低引脚
delay_us(80);       //延时60-120us
GPIO_SetBits(GPIOG,GPIO_Pin_11);         //拉高引脚
delay_us(2);
}
void d_write_one(void)
{
mode_output();              //输出模式
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
 testb=data&0x01;         //从低位开始写
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
 data=(j<<7)|(data>>1);   //从低位开始读
}
return data;
}
void d_start(void)
{ 
d_rst(); 
	d_write_byte(0xcc);  // 跳过ROM
 d_write_byte(0x44);  //温度转换
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
 d_start();      //开始转换
 delay_us(700);       //等待转换完成
 d_init();  
 d_write_byte(0xcc);  //跳过ROM
 d_write_byte(0xbe);  //读取暂存寄存器  
 TL=d_read_byte();   //低八位
 TH=d_read_byte();   //高八位，注意前五位为符号位只有全为0的时候温度是正的   
 tem=TH;           //获得高八位
 tem<<=8; 
 tem+=TL;           //获得底八位
 return tem/10-20;  
}