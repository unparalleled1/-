#include "stm32f10x.h"                  // Device header
#include  "Delay.h"                     //—” ±∫Ø ˝
#include  "lcd.h"
#include "usart.h"      

#include "MPU6050.h"
#include "inv_mpu.h"
<<<<<<< HEAD
#include "ad.h" sssssssssssssss 11
=======
#include "ad.h"

>>>>>>> parent of 2948ea8 (Á¨¨‰∏ÄÊ¨°ÊµãËØï)
float Pitch,Roll,Yaw;	
int16_t ax,ay,az,gx,gy,gz;	
float anglea;
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz);
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az);
int main(void)
{
	//sys_stm32_clock_init(9);    /* …Ë÷√ ±÷”, 72Mhz */
	delay_init();             /* —” ±≥ı ºªØ */
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

