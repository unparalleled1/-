#include "stm32f10x.h"                  // Device header
#include  "Delay.h"                     //延时函数
#include  "lcd.h"
#include "usart.h"      

#include "MPU6050.h"
#include "inv_mpu.h"
#include "ad.h"

float Pitch,Roll,Yaw;	
int16_t ax,ay,az,gx,gy,gz;	
float anglea;
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz);
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az);
int main(void)
{
	//sys_stm32_clock_init(9);    /* 设置时钟, 72Mhz */
	delay_init();             /* 延时初始化 */
	uart_init(115200);
	LCD_Init();
	LCD_Clear(WHITE);

	
AD_Init();
	
	while (1)
	{
 uint16_t advalue=AD_GetValue();
		LCD_ShowNum(0,0,advalue,5,16);
	uint16_t	pwm_value=(float)advalue/4095*100;
		LCD_ShowNum(0,30,pwm_value,4,16);

	}
	
}

