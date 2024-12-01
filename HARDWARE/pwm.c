#include "stm32f10x.h" // Device header
//PA0 pwm25起步
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
//选择时基单元时钟，内部时钟
TIM_InternalClockConfig(TIM2);
//初始化时基单元

TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
TIM_TimeBaseInitStructure.TIM_Period=100-1;//从0自增到9999，1s产生一次中断 ARR
TIM_TimeBaseInitStructure.TIM_Prescaler=720-1;//若去掉一个0，计数频率为原来十倍 PSC
TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);

//给成员赋初始值
TIM_OCStructInit(&TIM_OCInitStructure);
TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
TIM_OCInitStructure.TIM_Pulse=0;//CCR
//占空比： CRR/(ARR+1)
TIM_OC1Init(TIM2,&TIM_OCInitStructure);
//启动定时器
TIM_Cmd(TIM2,ENABLE);
}
void PWM_SetCompare1(uint16_t Compare){
TIM_SetCompare1(TIM2,Compare);
}