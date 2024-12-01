#include "stm32f10x.h" // Device header
extern int n;
//T=（arr+1）*(PSC+1)/Tck  tck=72M
void Timer_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure1;
	NVIC_InitTypeDef NVIC_InitStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
//选择时基单元时钟，内部时钟
TIM_InternalClockConfig(TIM3);
//初始化时基单元

TIM_TimeBaseInitStructure1.TIM_ClockDivision=TIM_CKD_DIV1;
TIM_TimeBaseInitStructure1.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
TIM_TimeBaseInitStructure1.TIM_Period=10000-1;//从0自增到9999，1s产生一次中断 
TIM_TimeBaseInitStructure1.TIM_Prescaler=7200-1;//若去掉一个0，计数频率为原来十倍
TIM_TimeBaseInitStructure1.TIM_RepetitionCounter=0;
TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure1);
//避免刚初始化完就进入中断
TIM_ClearFlag(TIM3,TIM_FLAG_Update);
//使能中断
TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
//配置NVIC
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
NVIC_Init(&NVIC_InitStructure);
//启动定时器
TIM_Cmd(TIM3,ENABLE);
}
void TIM3_IRQHandler(void)
{
if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET){
	n++;
	if(n==2000)
	{n=0;
	}
TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}
}