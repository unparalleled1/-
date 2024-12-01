#include "step_motor.h"
#include "delay.h"
#include "stm32f10x.h" // Device header
u8 STEP;
void S_Init(void){ //接口初始化
GPIO_InitTypeDef GPIO_InitStruct;
RCC_APB2PeriphClockCmd(S_CLK, ENABLE);
 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStruct.GPIO_Pin = S_A;
 GPIO_Init(S_PORT, &GPIO_InitStruct);
 GPIO_InitStruct.GPIO_Pin = S_B;
 GPIO_Init(S_PORT, &GPIO_InitStruct);
 GPIO_InitStruct.GPIO_Pin = S_C;
 GPIO_Init(S_PORT, &GPIO_InitStruct);
 GPIO_InitStruct.GPIO_Pin = S_D;
 GPIO_Init(S_PORT, &GPIO_InitStruct);
 GPIO_ResetBits(S_PORT, S_A);
 GPIO_ResetBits(S_PORT, S_B);
 GPIO_ResetBits(S_PORT, S_C);
 GPIO_ResetBits(S_PORT, S_D);
}
void S_OFF (void) //电机断电 全拉低
{
GPIO_ResetBits(S_PORT,S_A | S_B | S_C | S_D);//各接口置0
}
void S_8A (u8 a,u16 speed) //电机单步8拍
{
switch (a){
case 0:
GPIO_ResetBits(S_PORT,S_B | S_C | S_D);//0
GPIO_SetBits(S_PORT,S_A);//1
break;
case 1:
GPIO_ResetBits(S_PORT,S_C | S_D);//0
GPIO_SetBits(S_PORT,S_A | S_B);//1
break;
case 2:
GPIO_ResetBits(S_PORT,S_A | S_C | S_D);//0
GPIO_SetBits(S_PORT,S_B);//1
break;
case 3:
GPIO_ResetBits(S_PORT,S_A | S_D);//
GPIO_SetBits(S_PORT,S_B | S_C);//1
break;
case 4:
GPIO_ResetBits(S_PORT,S_A | S_B | S_D);//0
GPIO_SetBits(S_PORT,S_C);//1
break;
case 5:
GPIO_ResetBits(S_PORT,S_A | S_B);//0
GPIO_SetBits(S_PORT,S_C | S_D);//1
break;
case 6:
GPIO_ResetBits(S_PORT,S_A | S_B | S_C);//0
GPIO_SetBits(S_PORT,S_D);//1
break;
case 7:
GPIO_ResetBits(S_PORT,S_B | S_C);//0
GPIO_SetBits(S_PORT,S_A | S_D);//1
break;
default:
break;
}
delay_ms(speed); //延时
S_OFF();//进入断电状态，防电机过热
}
void S_NUM (u8 RL,u16 num,u8 speed) //电机按步数运行
{
u16 i;
for(i=0;i<num;i++)
 {
if(RL==1){ //当RL=1右转，RL=0左转
STEP++;
if(STEP>7)STEP=0;
}else{
if(STEP==0)STEP=8;
STEP--;
}
S_8A(STEP,speed);
}
}
void S_LOOP (u8 RL,u8 LOOP,u8 speed) //电机按圈数运行
{
S_NUM(RL,LOOP*4076,speed);
//S_NUM(RL,LOOP*2,speed);
}