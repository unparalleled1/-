#include "ultrasonsic.h"
#include "delay.h"
#include "stm32f10x.h"         // Device header
u8 msHcCount = 0;//ms����
static void NVIC_Config()
{
NVIC_InitTypeDef NVIC_InitStruct;
//�����ж���Ϊ2
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//�����ж���Դ
NVIC_InitStruct.NVIC_IRQChannel =TIM4_IRQn;
NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//���������ȼ�
NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
//���ô����ȼ�
NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
//��ʼ��
NVIC_Init(&NVIC_InitStruct);
}
void H_Init(void)
{ 
 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;   //�������ڶ�ʱ�����õĽṹ��
 GPIO_InitTypeDef GPIO_InitStructure;
/*����GPIOBʱ��*/
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
 
   //IO��ʼ��
 GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1;  //���͵�ƽ����TX
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�����������
 GPIO_Init(GPIOB, &GPIO_InitStructure);
 GPIO_ResetBits(GPIOB,GPIO_Pin_1);//һ��ʼ�͵�ƽ
 
 GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;   //���ص�ƽ����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
 GPIO_Init(GPIOB, &GPIO_InitStructure); 
 GPIO_ResetBits(GPIOB,GPIO_Pin_2); //Ĭ�ϵ͵�ƽ 
 
  //��ʱ����ʼ�� ʹ�û�����ʱ��TIM4
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  //ʹ�ܶ�ӦRCCʱ��
  //���ö�ʱ�������ṹ��
 TIM_DeInit(TIM4);
  //�Զ���װ��ֵ�Ĵ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
TIM_TimeBaseStructure.TIM_Period = 1000;//��������Ϊ1000us
//ʱ��Ԥ��Ƶ��
TIM_TimeBaseStructure.TIM_Prescaler = 72;//��Ƶ��72
//ʱ�ӷ�Ƶ����
TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
//����������ģʽ���������ϼ�����
TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
//�ظ���������ֵ
// TIM_TimeBaseStructure.TIM_RepetitionCounter=0 ;
 TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ    
   
 // TIM_ClearFlag(TIM4, TIM_FLAG_Update);  //��������жϣ����һ���ж����������ж�
TIM_ClearITPendingBit(TIM4, TIM_FLAG_Update); //��������жϣ����һ���ж����������ж�
 TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);  //�򿪶�ʱ�������ж�
NVIC_Config();
 TIM_Cmd(TIM4,DISABLE);  
}
void initH_(void)
{
H_Init();
//TIM4_NVIC_Config();
}
static void OpenTimer()    //�򿪶�ʱ��
{
   // /*���������*/
TIM_SetCounter(TIM4,0);
msHcCount = 0;
TIM_Cmd(TIM4,ENABLE);//ʹ�ܶ�ʱ��
}
static void CloseTimer()    //�رն�ʱ��
{
   // /*�رռ�����ʹ��*/
TIM_Cmd(TIM4,DISABLE);
}
//��ʱ��2�жϷ������
void TIM4_IRQHandler(void)  //TIM4�ж�
{
   // /*�ж��ж��ַ���Ĳ���*/
if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET){
/*��������жϱ�־λ*/
TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
msHcCount++;
}
}
//��ȡ��ʱ��ʱ��
u32 GetEchoTimer(void)
{
 u32 time = 0;
/*//�������źźܳ��ǣ�����ֵ������ظ�������overCount���ж��������������*/
time = msHcCount*1000;//overCountÿ++һ�Σ�����overCount���룬time΢��
time += TIM_GetCounter(TIM4);//��ȡ��TIM4���Ĵ����еļ���ֵ��һ�߼�������ź�ʱ��
TIM4->CNT = 0; //��TIM4�����Ĵ����ļ���ֵ����
delay_ms(5);
return time;
}
float H_GetLength(void )
{
/*��5�����ݼ���һ��ƽ��ֵ*/
float length = 0;
float t = 0;
float sum = 0;
u16 i = 0;
while(i != 5){
GPIO_SetBits(GPIOB,GPIO_Pin_1);//trig�����źţ������ߵ�ƽ
delay_us(20);//����ʱ�䳬��10us
GPIO_ResetBits(GPIOB,GPIO_Pin_1);
/*Echo�����ź� �ȴ������ź�*/
/*���뷽����ģ����Զ�����8��40KHz�����������ͬʱ�ز����ţ�echo���˵ĵ�ƽ����0��Ϊ
1��
����ʱӦ��������ʱ����ʱ���������������ر�ģ����յ�ʱ���ز��� �Ŷ˵ĵ�ƽ����1��Ϊ0��
����ʱӦ��ֹͣ��ʱ������������ʱ�����µ����ʱ�伴Ϊ
�������ɷ��䵽���ص���ʱ����*/
while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2) == 0);//echo�ȴ�����
/*������ʱ��*/
OpenTimer();
i = i+1; //ÿ�յ�һ�λ����ź�+1���յ�5�ξͼ����ֵ
while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2) == 1);
/*�رն�ʱ��*/
CloseTimer();
/*��ȡEcho�ߵ�ƽʱ��ʱ��*/
t = GetEchoTimer();
length = (float)t/58;//��λʱcm
sum += length;
}
length = sum/5;//���ƽ��ֵ
return length;
}