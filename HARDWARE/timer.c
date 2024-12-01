#include "stm32f10x.h" // Device header
extern int n;
//T=��arr+1��*(PSC+1)/Tck  tck=72M
void Timer_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure1;
	NVIC_InitTypeDef NVIC_InitStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
//ѡ��ʱ����Ԫʱ�ӣ��ڲ�ʱ��
TIM_InternalClockConfig(TIM3);
//��ʼ��ʱ����Ԫ

TIM_TimeBaseInitStructure1.TIM_ClockDivision=TIM_CKD_DIV1;
TIM_TimeBaseInitStructure1.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���
TIM_TimeBaseInitStructure1.TIM_Period=10000-1;//��0������9999��1s����һ���ж� 
TIM_TimeBaseInitStructure1.TIM_Prescaler=7200-1;//��ȥ��һ��0������Ƶ��Ϊԭ��ʮ��
TIM_TimeBaseInitStructure1.TIM_RepetitionCounter=0;
TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure1);
//����ճ�ʼ����ͽ����ж�
TIM_ClearFlag(TIM3,TIM_FLAG_Update);
//ʹ���ж�
TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
//����NVIC
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
NVIC_Init(&NVIC_InitStructure);
//������ʱ��
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