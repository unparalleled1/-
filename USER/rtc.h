#ifndef _DS1302_H_
#define _DS1302_H_
#include "stm32f10x.h"
//#include "misc.h"
#include "delay.h"
#define CE_L GPIO_ResetBits(GPIOC,GPIO_Pin_11)//拉低使能位
#define CE_H GPIO_SetBits(GPIOC,GPIO_Pin_11)//拉高使能位
#define SCLK_L GPIO_ResetBits(GPIOC,GPIO_Pin_12)//拉低时钟线
#define SCLK_H GPIO_SetBits(GPIOC,GPIO_Pin_12)//拉高时钟线
#define DATA_L GPIO_ResetBits(GPIOC,GPIO_Pin_10)//拉低数据线
#define DATA_H GPIO_SetBits(GPIOC,GPIO_Pin_10)//拉高数据线
struct TIMEData
{
u8 day;
u8 hour;
u8 minute;
u8 second;
};//创建TIMEData结构体方便存储时间日期数据
extern struct TIMEData TimeData;//全局变量


void ds1302_init(u8 day,u8 hour,u8 min,u8 sec);//acknowledge hex as  dec:e.g:0x23:23,0x12:12
void ds1302_read_realTime(int m);
#endif