#ifndef __S_H
#define __S_H
#include "sys.h"
#include "delay.h"
extern u8 STEP; //���嵥������ ȫ�ֱ���
#define S_PORT GPIOD //����IO�ӿ�������
#define S_A GPIO_Pin_2 //����IO�ӿ�
#define S_B GPIO_Pin_3 //����IO�ӿ�
#define S_C GPIO_Pin_4 //����IO�ӿ�
#define S_D GPIO_Pin_5 //����IO�ӿ�
#define S_CLK RCC_APB2Periph_GPIOF
void S_Init(void);//��ʼ��
void S_OFF (void);//�ϵ�״̬
void S_8A (u8 a,u16 speed);
void S_NUM (u8 RL,u16 num,u8 speed);//�������������
void S_LOOP (u8 RL,u8 LOOP,u8 speed);//�����Ȧ������
#endif