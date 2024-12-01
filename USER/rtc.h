#ifndef _DS1302_H_
#define _DS1302_H_
#include "stm32f10x.h"
//#include "misc.h"
#include "delay.h"
#define CE_L GPIO_ResetBits(GPIOC,GPIO_Pin_11)//����ʹ��λ
#define CE_H GPIO_SetBits(GPIOC,GPIO_Pin_11)//����ʹ��λ
#define SCLK_L GPIO_ResetBits(GPIOC,GPIO_Pin_12)//����ʱ����
#define SCLK_H GPIO_SetBits(GPIOC,GPIO_Pin_12)//����ʱ����
#define DATA_L GPIO_ResetBits(GPIOC,GPIO_Pin_10)//����������
#define DATA_H GPIO_SetBits(GPIOC,GPIO_Pin_10)//����������
struct TIMEData
{
u8 day;
u8 hour;
u8 minute;
u8 second;
};//����TIMEData�ṹ�巽��洢ʱ����������
extern struct TIMEData TimeData;//ȫ�ֱ���


void ds1302_init(u8 day,u8 hour,u8 min,u8 sec);//acknowledge hex as  dec:e.g:0x23:23,0x12:12
void ds1302_read_realTime(int m);
#endif