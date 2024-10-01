#include "button_motor.h"
#include "freertos.h"
#include "task.h"
#include "self_def_massage.h"
#include "KEY.h"
#include "bsp_usart.h"
#include "multi_button.h"
#include "OLED_IIC_Config.h"
#include "OLED_Function.h"
#include "OLED_Front.h"
#include "Buzzer.h"
#include "tim.h"
#include "stdio.h"
#include "usart.h"
#include "Buzzer.h"


uint8_t rx_data[BUF_SIZE];
  
extern USARTInstance Uart_frame;
extern uint8_t DataBuff[BUF_SIZE]; 
	


	
//freeRTOSִ�а�������
/***   ִ�а�������  ***/
void button_task()
{
		while(1)
		{
			
		button_ticks();
		vTaskDelay(2);
		}
}
/***   ִ�з���������  ***/
void buzzer_task()
{
		while(1)
		{
			//Buzzer_SetFreq(1000);
			
		vTaskDelay(2);
		}
}

/***   ִ��OLED����  ***/
void oled_task()
{

		while(1)
		{
			
			
		vTaskDelay(2);
		}
}




/*  ���лص�����  */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart,uint16_t Size)
{
	
	uint8_t cnt =0;
//	int commit;//���մ�����ָ��      
	memset(rx_data,0,sizeof(rx_data));
				
 if( huart->Instance == USART1)
   {   
				if(DataBuff[0] == usart_frame_hand1&&
					 DataBuff[1] == usart_frame_hand2&& 
					 DataBuff[2] == usart_frame_hand1  )   //����Ƿ��ǰ�ͷ  DataBuff[%d]=
			 {  
		  	//  commit= DataBuff[3];                 //���շ������������ִ�в�ͬ�Ĵ��룬����ûд�Ժ󲹳�
					cnt =  DataBuff[4];
			
			 //CRC���� && ����Ƿ��ǰ�β
			uint16_t CRC16= CRC16_Check(rx_data,cnt);
		  uint16_t  crc=(DataBuff[cnt+5]<< 8) | DataBuff[cnt+6];

			if(CRC16==crc&&DataBuff[cnt+7] == usart_frame_end ) 
				{ 
					for(int i=0;i<=cnt;i++){
			uint8_t 		data= DataBuff[i+5];
						User_rx_Callback(data);		
					}						
				} 
			else  
			 {
					memset(rx_data,0,sizeof(rx_data));
			 } 
	  } 
  }
}



/*���ջص�*/
void User_rx_Callback(uint8_t data)
{
	if( data==0x11){
HAL_GPIO_TogglePin (LED1_GPIO_Port,LED1_Pin);
	//����
	
	}
	if( data== 0x22){
HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
	//����
	}
	if( data== 0x33){
HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
	//����
	}
}



void HAL_UART_ErrorCallback(UART_HandleTypeDef * huart)
{
    if(huart->Instance == USART1)
    {
		  Uart_Idle_rcDMA(Uart_frame.usart_handle, DataBuff); // ���շ������������
      memset(DataBuff, 0, sizeof(DataBuff));
    }
}







