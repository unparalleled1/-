#include "esp8266.h"
#include "string.h"
#include "delay.h"
#include <stdarg.h>
#define NUMBER "34848854007540710077"
#define NUMM "12345678"
//UART_HandleTypeDef g_uart_handle;
uint8_t g_uart_rx_buf[ESP8266_UART_RX_BUF_SIZE];
uint8_t g_uart_tx_buf[ESP8266_UART_TX_BUF_SIZE];
uint16_t esp8266_cnt = 0, esp8266_cntPre = 0;

int my_esp8266_init(void)
{
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	printf("AT+CWJAP=\"%s\",\"%s\"\r\n", "unp", "lllllllk");
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);

	printf("AT+ATKCLDSTA=\"%s\",\"%s\"\r\n", NUMBER, NUMM);
	return 1;
}
/**
 * @brief       ESP8266 UART初始化
 * @param       baudrate: UART通讯波特率
 * @retval      无
 */
 
 /*
void esp8266_uart_init(uint32_t baudrate)
{
    g_uart_handle.Instance          = ESP8266_UART_INTERFACE;       /* ESP8266 UART 
    g_uart_handle.Init.BaudRate     = baudrate;                     /* 波特率 
    g_uart_handle.Init.WordLength   = UART_WORDLENGTH_8B;           /* 数据位 
    g_uart_handle.Init.StopBits     = UART_STOPBITS_1;              /* 停止位 
    g_uart_handle.Init.Parity       = UART_PARITY_NONE;             /* 校验位 
    g_uart_handle.Init.Mode         = UART_MODE_TX_RX;              /* 收发模式 
    g_uart_handle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;          /* 无硬件流控 
    g_uart_handle.Init.OverSampling = UART_OVERSAMPLING_16;         /* 过采样 
    HAL_UART_Init(&g_uart_handle);                                  /* 使能ESP8266 UART 
}
*/

/**
 * @brief       ESP8266 UART中断回调函数
 * @param       无
 * @retval      无
 
void ESP8266_UART_IRQHandler(void)
{
    uint8_t receive_data = 0;   
    if(__HAL_UART_GET_FLAG(&g_uart_handle, UART_FLAG_RXNE) != RESET){
		if(esp8266_cnt >= sizeof(g_uart_rx_buf))
            esp8266_cnt = 0; //防止串口被刷爆
        HAL_UART_Receive(&g_uart_handle, &receive_data, 1, 1000);//串口2接收1位数据
		g_uart_rx_buf[esp8266_cnt++] = receive_data;  
    }
    HAL_UART_IRQHandler(&g_uart_handle);
}
*/
/**
 * @brief       ESP8266 循环调用检测是否接收完成
 * @param       无
 * @retval      ESP8266_EOK-接收完成		ESP8266_ERROR-接收超时未完成
 */
uint8_t esp8266_wait_receive(void)
{

	if(esp8266_cnt == 0) 							//如果接收计数为0 则说明没有处于接收数据中，所以直接跳出，结束函数
		return ESP8266_ERROR;
		
	if(esp8266_cnt == esp8266_cntPre) {				//如果上一次的值和这次相同，则说明接收完毕
		esp8266_cnt = 0;							//清0接收计数
		return ESP8266_EOK;							//返回接收完成标志
	}
		
	esp8266_cntPre = esp8266_cnt;					//置为相同
	return ESP8266_ERROR;							//返回接收未完成标志
}

/**
 * @brief       ESP8266 清空串口接收缓存
 * @param       无
 * @retval      无
 */
void esp8266_clear(void)
{
	memset(g_uart_rx_buf, 0, sizeof(g_uart_rx_buf));
	esp8266_cnt = 0;
}

/**
 * @brief       ESP8266 发送命令
 * @param       cmd-待发送的AT命令，res-期待接收到的字符串
 * @retval      ESP8266_EOK-成功  ESP8266_ERROR-失败
 */
uint8_t esp8266_send_command(char *cmd, char *res)
{
	
	uint8_t timeOut = 250;

    esp8266_clear();
//	HAL_UART_Transmit(&g_uart_handle, (unsigned char *)cmd, strlen((const char *)cmd), 100);

	while(timeOut--) {
		if(esp8266_wait_receive() == ESP8266_EOK) {						//如果收到数据
			if(strstr((const char *)g_uart_rx_buf, res) != NULL)		//如果检索到关键词
				return ESP8266_EOK;
		}
		delay_ms(10);
	}

	return ESP8266_ERROR;

}

/**
 * @brief       ESP8266恢复出厂设置
 * @param       无
 * @retval      ESP8266_EOK  : 恢复出场设置成功
 *              ESP8266_ERROR: 恢复出场设置失败
 */
uint8_t esp8266_restore(void)
{
    return esp8266_send_command("AT+RESTORE", "ready");
}

/**
 * @brief       ESP8266 AT指令测试
 * @param       无
 * @retval      ESP8266_EOK  : AT指令测试成功
 *              ESP8266_ERROR: AT指令测试失败
 */
uint8_t esp8266_at_test(void)
{
    return esp8266_send_command("AT\r\n", "OK");
}

/**
 * @brief       设置ESP8266工作模式
 * @param       mode: 1，Station模式
 *                    2，AP模式
 *                    3，AP+Station模式
 * @retval      ESP8266_EOK   : 工作模式设置成功
 *              ESP8266_ERROR : 工作模式设置失败
 *              ESP8266_EINVAL: mode参数错误，工作模式设置失败
 */
uint8_t esp8266_set_mode(uint8_t mode)
{
    switch (mode) {
        case ESP8266_STA_MODE:
            return esp8266_send_command("AT+CWMODE=1\r\n", "OK");    /* Station模式 */
        
        case ESP8266_AP_MODE:
            return esp8266_send_command("AT+CWMODE=2\r\n", "OK");    /* AP模式 */
        
        case ESP8266_STA_AP_MODE:
            return esp8266_send_command("AT+CWMODE=3\r\n", "OK");    /* AP+Station模式 */
        
        default:
            return ESP8266_EINVAL;
    }
}

/**
 * @brief       ESP8266软件复位
 * @param       无
 * @retval      ESP8266_EOK  : 软件复位成功
 *              ESP8266_ERROR: 软件复位失败
 */
uint8_t esp8266_sw_reset(void)
{
    return esp8266_send_command("AT+RST\r\n", "OK");
}

/**
 * @brief       ESP8266设置回显模式
 * @param       cfg: 0，关闭回显
 *                   1，打开回显
 * @retval      ESP8266_EOK  : 设置回显模式成功
 *              ESP8266_ERROR: 设置回显模式失败
 */
uint8_t esp8266_ate_config(uint8_t cfg)
{
    switch (cfg) {
        case 0:
            return esp8266_send_command("ATE0\r\n", "OK");   /* 关闭回显 */
        
        case 1:
            return esp8266_send_command("ATE1\r\n", "OK");   /* 打开回显 */
        
        default:
            return ESP8266_EINVAL;
    }
}

/**
 * @brief       ESP8266连接WIFI
 * @param       ssid: WIFI名称
 *              pwd : WIFI密码
 * @retval      ESP8266_EOK  : WIFI连接成功
 *              ESP8266_ERROR: WIFI连接失败
 */
uint8_t esp8266_join_ap(char *ssid, char *pwd)
{
    char cmd[64];
    
    sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, pwd);
    
    return esp8266_send_command(cmd, "WIFI GOT IP");
}

/**
 * @brief       ESP8266获取IP地址
 * @param       buf: IP地址，需要16字节内存空间
 * @retval      ESP8266_EOK  : 获取IP地址成功
 *              ESP8266_ERROR: 获取IP地址失败
 */
uint8_t esp8266_get_ip(char *buf)
{
    char *p_start;
    char *p_end;

    if (esp8266_send_command("AT+CIFSR\r\n", "STAIP") != ESP8266_EOK)
        return ESP8266_ERROR;

    p_start = strstr((const char *)g_uart_rx_buf, "\"");
    p_end = strstr(p_start + 1, "\"");
    *p_end = '\0';
    sprintf(buf, "%s", p_start + 1);
    
    return ESP8266_EOK;
}

/**
 * @brief       ESP8266连接TCP服务器
 * @param       server_ip  : TCP服务器IP地址
 *              server_port: TCP服务器端口号
 * @retval      ESP8266_EOK  : 连接TCP服务器成功
 *              ESP8266_ERROR: 连接TCP服务器失败
 */
uint8_t esp8266_connect_tcp_server(char *server_ip, char *server_port)
{
    char cmd[64];

    sprintf(cmd, "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n", server_ip, server_port);

    return esp8266_send_command(cmd, "CONNECT");
}

/**
 * @brief       ESP8266断开TCP服务器
 * @param       无
 * @retval      ESP8266_EOK  : 断开TCP服务器成功
 *              ESP8266_ERROR: 断开TCP服务器失败
 */
uint8_t esp8266_disconnect_tcp_server(void)
{
    return esp8266_send_command("AT+CIPCLOSE\r\n", "");

}

/**
 * @brief       ESP8266进入透传
 * @param       无
 * @retval      ESP8266_EOK  : 进入透传成功
 *              ESP8266_ERROR: 进入透传失败
 */
uint8_t esp8266_enter_unvarnished(void)
{
    uint8_t ret;
    
    ret  = esp8266_send_command("AT+CIPMODE=1\r\n", "OK");
    ret += esp8266_send_command("AT+CIPSEND\r\n", ">");
    if (ret == ESP8266_EOK)
        return ESP8266_EOK;
    else
        return ESP8266_ERROR;
}

/**
 * @brief       ESP8266退出透传
 * @param       无
 * @retval      ESP8266_EOK  : 退出透传成功
 *              ESP8266_ERROR: 退出透传失败
 */
uint8_t esp8266_exit_unvarnished(void)
{
    return esp8266_send_command("+++", "");

}

/**
 * @brief       ESP8266进入单连接
 * @param       无
 * @retval      ESP8266_EOK  : 进入单连接成功
 *              ESP8266_ERROR: 进入单连接失败
 */
uint8_t esp8266_single_connection(void)
{
    return esp8266_send_command("AT+CIPMUX=0\r\n", "OK");
}

/**
 * @brief       ESP8266初始化
 * @param       baudrate: ESP8266 UART通讯波特率
 * @retval      ESP8266_EOK  : ESP8266初始化成功，函数执行成功
 *              ESP8266_ERROR: ESP8266初始化失败，函数执行失败
 */
uint8_t esp8266_init(uint32_t baudrate)
{
    char ip_buf[16];

    //esp8266_uart_init(baudrate);                /* ESP8266 UART初始化 */

    /* 让WIFI退出透传模式 */
	while(esp8266_exit_unvarnished())
        delay_ms(500);

	printf("1.AT\r\n");
	while(esp8266_at_test())
        delay_ms(500);
	
	printf("2.RST\r\n");
    while(esp8266_sw_reset())
        delay_ms(500);
	while(esp8266_disconnect_tcp_server())
        delay_ms(500);
	
	printf("3.CWMODE\r\n");
	while(esp8266_set_mode(ESP8266_STA_MODE))
        delay_ms(500);
	
	printf("4.AT+CIPMUX\r\n");  //设置单路连接模式，透传只能使用此模式
	while(esp8266_single_connection())
        delay_ms(500);
	
	printf("5.CWJAP\r\n");      //连接WIFI
	while(esp8266_join_ap(WIFI_SSID, WIFI_PWD))
        delay_ms(1000);
    
    printf("6.CIFSR\r\n");
    while(esp8266_get_ip(ip_buf))
        delay_ms(500);

    printf("ESP8266 IP: %s\r\n", ip_buf);
    
//    printf("7.CIPSTART\r\n");
//    while(esp8266_connect_tcp_server(TCP_SERVER_IP, TCP_SERVER_PORT))
//        delay_ms(500);
//    
//    printf("8.CIPMODE\r\n");
//    while(esp8266_enter_unvarnished())
//        delay_ms(500);
    
    printf("ESP8266_Init OK\r\n");
    return ESP8266_EOK;
}

/**
 * @brief       ESP8266 UART printf
 * @param       fmt: 待打印的数据
 * @retval      无
 */
void esp8266_uart_printf(char *fmt, ...)
{
    va_list ap;
    uint16_t len;
    
    va_start(ap, fmt);
    vsprintf((char *)g_uart_tx_buf, fmt, ap);
    va_end(ap);
    
    len = strlen((const char *)g_uart_tx_buf);
  //  HAL_UART_Transmit(&g_uart_handle, g_uart_tx_buf, len, HAL_MAX_DELAY);
}
