#include "stm32f10x.h" // Device header
//PA0 pwm25��
void PWM_Init(void)
{TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Init(GPIOA,&GPIO_InitStructure);
//ѡ��ʱ����Ԫʱ�ӣ��ڲ�ʱ��
TIM_InternalClockConfig(TIM2);
//��ʼ��ʱ����Ԫ

TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���
TIM_TimeBaseInitStructure.TIM_Period=100-1;//��0������9999��1s����һ���ж� ARR
TIM_TimeBaseInitStructure.TIM_Prescaler=720-1;//��ȥ��һ��0������Ƶ��Ϊԭ��ʮ�� PSC
TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);

//����Ա����ʼֵ
TIM_OCStructInit(&TIM_OCInitStructure);
TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
TIM_OCInitStructure.TIM_Pulse=0;//CCR
//ռ�ձȣ� CRR/(ARR+1)
TIM_OC1Init(TIM2,&TIM_OCInitStructure);
//������ʱ��
TIM_Cmd(TIM2,ENABLE);
}
void PWM_SetCompare1(uint16_t Compare){
TIM_SetCompare1(TIM2,Compare);
}