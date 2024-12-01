#ifndef __S_H
#define __S_H
#include "sys.h"
#include "delay.h"
extern u8 STEP; //定义单步计数 全局变量
#define S_PORT GPIOD //定义IO接口所在组
#define S_A GPIO_Pin_2 //定义IO接口
#define S_B GPIO_Pin_3 //定义IO接口
#define S_C GPIO_Pin_4 //定义IO接口
#define S_D GPIO_Pin_5 //定义IO接口
#define S_CLK RCC_APB2Periph_GPIOF
void S_Init(void);//初始化
void S_OFF (void);//断电状态
void S_8A (u8 a,u16 speed);
void S_NUM (u8 RL,u16 num,u8 speed);//电机按步数运行
void S_LOOP (u8 RL,u8 LOOP,u8 speed);//电机按圈数运行
#endif