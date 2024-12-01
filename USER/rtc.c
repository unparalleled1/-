#include "rtc.h"
#include "stm32f10x.h"         // Device header
struct TIMEData TimeData;
u8 read_time[7];
void ds1302_gpio_init()//CE,SCLK端口初始化
{
GPIO_InitTypeDef GPIO_InitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11; //PC.11 CE
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC.11
GPIO_ResetBits(GPIOC,GPIO_Pin_12|GPIO_Pin_11);
}
void ds1302_DATAOUT_init()//配置双向I/O端口为输出态
{
GPIO_InitTypeDef GPIO_InitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PC.10 DATA
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC.10
GPIO_ResetBits(GPIOC,GPIO_Pin_10);
}
void ds1302_DATAINPUT_init()//配置双向I/O端口为输入态
{
GPIO_InitTypeDef GPIO_InitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PC.10 DATA
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC.10
}
void ds1302_write_onebyte(u8 data)//向DS1302发送一字节数据
{
u8 count=0;
ds1302_DATAOUT_init();
SCLK_L;
for(count=0;count<8;count++)
{
SCLK_L;
if(data&0x01)
{DATA_H;}
else{DATA_L;}//先准备好数据再发送
SCLK_H;//拉高时钟线，发送数据
data>>=1;
}
}
void ds1302_wirte_rig(u8 address,u8 data)//向指定寄存器地址发送数据
{
u8 temp1=address;
u8 temp2=data;
CE_L;SCLK_L;delay_us(1);
CE_H;delay_us(2);
ds1302_write_onebyte(temp1);
ds1302_write_onebyte(temp2);
CE_L;SCLK_L;delay_us(2);
}
u8 ds1302_read_rig(u8 address)//从指定地址读取一字节数据
{
u8 temp3=address;
u8 count=0;
u8 return_data=0x00;
CE_L;SCLK_L;delay_us(3);
CE_H;delay_us(3);
ds1302_write_onebyte(temp3);
ds1302_DATAINPUT_init();//配置I/O口为输入
delay_us(2);
for(count=0;count<8;count++)
{
delay_us(2);//使电平持续一段时间
return_data>>=1;
SCLK_H;delay_us(4);//使高电平持续一段时间
SCLK_L;delay_us(14);//延时14us后再去读取电压，更加准确
if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10))
{return_data=return_data|0x80;}
}
delay_us(2);
CE_L;DATA_L;
return return_data;
}
void ds1302_init(u8 day,u8 hour,u8 min,u8 sec)
{
ds1302_gpio_init();
//ds1302_wirte_rig(0x8e,0x00);//关闭写保护
//ds1302_wirte_rig(0x80,sec);//seconds37秒
//ds1302_wirte_rig(0x82,min);//minutes58分
//ds1302_wirte_rig(0x84,hour);//hours23时
//ds1302_wirte_rig(0x86,day);//date30日
//ds1302_wirte_rig(0x8e,0x80);//关闭写保护
}
void ds1302_read_time()
{
read_time[0]=ds1302_read_rig(0x81);//读秒
	read_time[1]=ds1302_read_rig(0x83);//读分
read_time[2]=ds1302_read_rig(0x85);//读时
read_time[3]=ds1302_read_rig(0x87);//读日
}
void ds1302_read_realTime(int m)
{
ds1302_read_time(); //BCD码转换为10进制
if(m==24)
{
TimeData.second=(read_time[0]>>4)*10+(read_time[0]&0x0f);
TimeData.minute=((read_time[1]>>4)&(0x07))*10+(read_time[1]&0x0f);
TimeData.hour=(read_time[2]>>4)*10+(read_time[2]&0x0f);
TimeData.day=(read_time[3]>>4)*10+(read_time[3]&0x0f);
}
else if(m==12)
{
TimeData.second=(read_time[0]>>4)*10+(read_time[0]&0x0f);
TimeData.minute=((read_time[1]>>4)&(0x07))*10+(read_time[1]&0x0f);
TimeData.hour=(read_time[2]>>4)*10+(read_time[2]&0x0f);
if(TimeData.hour>12)
TimeData.hour=((read_time[2]>>4)*10+(read_time[2]&0x0f))-12;
else
TimeData.hour=(read_time[2]>>4)*10+(read_time[2]&0x0f);
TimeData.day=(read_time[3]>>4)*10+(read_time[3]&0x0f);
}
}