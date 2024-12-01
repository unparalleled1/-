#include "stm32f10x.h" 

//PA1   
//advalue=AD_GetValue();
//		LCD_ShowNum(0,0,advalue,5,16);
//		pwm_value=100-(float)advalue/4095*100;
//		LCD_ShowNum(0,30,pwm_value,4,16);
void AD_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
RCC_ADCCLKConfig(RCC_PCLK2_Div6); //12M hz

GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Init(GPIOA,&GPIO_InitStructure);
ADC_RegularChannelConfig(ADC2,ADC_Channel_1,1,ADC_SampleTime_55Cycles5);

ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//软件触发
ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;
ADC_InitStructure.ADC_ScanConvMode=DISABLE;
ADC_InitStructure.ADC_NbrOfChannel=1;
ADC_Init(ADC2,&ADC_InitStructure);
ADC_Cmd(ADC2,ENABLE);
//校准
ADC_ResetCalibration(ADC2);
while(ADC_GetResetCalibrationStatus(ADC2)==SET);
ADC_StartCalibration(ADC2);
while(ADC_GetCalibrationStatus(ADC2)==SET);
}
uint16_t AD_GetValue(void)
{
ADC_SoftwareStartConvCmd(ADC2,ENABLE);
while(ADC_GetFlagStatus(ADC2,ADC_FLAG_EOC)==RESET);
return ADC_GetConversionValue(ADC2);
}