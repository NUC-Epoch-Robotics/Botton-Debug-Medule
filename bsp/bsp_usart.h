#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "gpio.h"

#define USART_BUF_SIZE	256

typedef enum
{
    USART_TRANSFER_NONE=0,
    USART_TRANSFER_BLOCKING,
    USART_TRANSFER_IT,
    USART_TRANSFER_DMA,
} USART_TRANSFER_MODE;

typedef struct
{
	
  UART_HandleTypeDef   *usart_handle;
  uint8_t              recv_buff;          // ģ�����һ�����ݵĴ�С
  USART_TRANSFER_MODE  TRANSFER_MODE;
} USARTInstance;


//���ڳ�ʼ��
int bsp_usart_init(	USARTInstance* usart, uint8_t *buf );
              
//����HAL��usart���ͺ�����װ
void SensorUartSend(USARTInstance *usart, uint8_t *send_buf, uint16_t send_size,USART_TRANSFER_MODE mode );

void UART_Receive_IT_enable( USARTInstance *usart,uint8_t *pData,uint16_t Size);

#endif


