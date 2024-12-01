#include "stm32f10x.h" // Device header
extern float CounterSensorNum;
void CounterSensor_Init(void){
//ø™∆Ù ±÷”
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
//AFIOø™∆Ù ±÷”
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//≈‰÷√GPIO

GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Init(GPIOC,&GPIO_InitStructure);
//≈‰÷√AFIO
GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);
//≈‰÷√EXTI

EXTI_InitStructure.EXTI_Line=EXTI_Line5;
EXTI_InitStructure.EXTI_LineCmd=ENABLE;
EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
EXTI_Init(&EXTI_InitStructure);
//≈‰÷√NVIC
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;
NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//0-3
NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
NVIC_Init(&NVIC_InitStructure);
}
uint16_t CounterSensor_Get(void)
{
return CounterSensorNum;
}
void EXTI9_5_IRQHandler(void)
{
if(EXTI_GetITStatus(EXTI_Line5)==SET)
{
CounterSensorNum++;
EXTI_ClearITPendingBit(EXTI_Line5);
}
}