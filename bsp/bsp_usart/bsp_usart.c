#include "bsp_usart.h"
#include "usart.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"

/*�ο�CSDN
*ԭ�����ӣ�https://blog.csdn.net/m0_63954303/article/details/139794861
*
*/


/* bsp_usart_init�����ڽ��ճ�ʼ������
 * huart	 	��Ҫ��ʼ���Ĵ��ڵľ��
 * huart_type	��Ҫ��ʼ���Ĵ��ڱ�ţ�BSP_USART
 * return		�ɹ�����0��ʧ�ܷ���-1 */
int bsp_usart_init(	USARTInstance* usart, uint8_t *buf )
{
	
	if(usart->usart_handle!=NULL )
	{
			  /* �������ڽ����ж� */
				HAL_UART_Receive_IT(usart->usart_handle, buf, USART_BUF_SIZE);	
				/* ʹ�ܿ����ж� */
		  	__HAL_UART_ENABLE_IT(usart->usart_handle, UART_IT_IDLE);	
				/* �����һ�ο����жϱ�־����������������� */
				__HAL_UART_CLEAR_IDLEFLAG(usart->usart_handle);													
				return 0;
	 }
	return -1;
}                      
/*
*��usart���еײ��װ
*�Դ����ض���
*
*/


//����HAL��usart���ͺ�����װ
 void SensorUartSend(USARTInstance *usart, uint8_t *send_buf, uint16_t send_size,USART_TRANSFER_MODE mode )
{
    switch (mode)
    {
    case USART_TRANSFER_BLOCKING:
        HAL_UART_Transmit(usart->usart_handle, send_buf, send_size, 100);
        break;
    case USART_TRANSFER_IT:
        HAL_UART_Transmit_IT(usart->usart_handle, send_buf, send_size);
        break;
    case USART_TRANSFER_DMA:
        HAL_UART_Transmit_DMA(usart->usart_handle, send_buf, send_size);
        break;
    default:
        while (1)
            ; // illegal mode! check your code context! ��鶨��instance�Ĵ���������,���ܳ���ָ��Խ��
        break;
    }
}

void UART_Receive_IT_enable( USARTInstance *usart,uint8_t *pData,uint16_t Size)
	{
    UART_Start_Receive_IT(usart->usart_handle ,pData ,Size);
	}
	





