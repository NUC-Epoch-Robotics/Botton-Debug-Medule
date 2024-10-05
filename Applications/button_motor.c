#include "button_motor.h"
#include "freertos.h"
#include "task.h"
#include "self_def_massage.h"
#include "KEY.h"
#include "multi_button.h"
#include "OLED_IIC_Config.h"
#include "OLED_Function.h"
#include "OLED_Front.h"
#include "Buzzer.h"
#include "tim.h"
#include "stdio.h"
#include "usart.h"
#include "ring_buffer.h"
#include "cmsis_os.h"
#include "queue.h"
#include "event_groups.h"

/*************** freeRTOS��������� ****************/
extern osThreadId LED1_taskHandle;
extern osThreadId LED2_taskHandle;
extern osThreadId LED3_taskHandle;
//extern osEventFlagsId_t EventKey1Handle;
/* ���� */
extern osMessageQId queuekey1Handle;
/** �¼���궨�� **/
#define Event_0 (1<<0)
#define Event_1 (1<<1)
#define Event_2 (1<<2)

/*********���ڷ��ͱ�������*****************/
FrameInstance frame1;
uint8_t Data1[3];
	
/*********���ڽ��ձ�������*****************/
extern uint8_t DataBuff[BUF_SIZE]; 
stRingBuff Ring_Buff;            //ѭ������
uint8_t ringbuff[RING_BUFF_SIZE];

/*********�����ṹ��*****************/
extern	KEY_Configure_TypeDef KeyCfg;	



//�ų�ʼ���Ĵ���   ֮����freertos�е�����ɳ�ʼ��
void Buttonmotorinit()
{
  RingBufferinit(&Ring_Buff,ringbuff,RING_BUFF_SIZE );
	Data1[0]=0x11;
	Data1[1]=0x22;
	Data1[2]=0x33;
  key_init(&KeyCfg);
  OLED_Init();
  Buzzer_on();
  HAL_TIM_Base_Start_IT(&htim2); //ʹ�ܶ�ʱ���ж�
	HAL_TIM_Base_Start(&htim2);  //������ʱ��
     printf("��ʼ��\r\n");
  frameInstance_init(&frame1,usart_W_DATA);
//  	osThreadSuspend(LED1_taskHandle);//�����������
//		osThreadSuspend(LED2_taskHandle);//�����������
//		osThreadSuspend(LED3_taskHandle);//�����������
//    osThreadSuspend(LED2_taskHandle);

}

//freeRTOSִ�а�������
/***   ִ�а�������  ***/
void button_task()
{

		while(1)
		{
		

		}
}
/***   ִ�з���������  ***/
void buzzer_task()
{	
	int i=0;
	  osThreadSuspend(LED1_taskHandle);//�����������
		osThreadSuspend(LED2_taskHandle);//�����������
		osThreadSuspend(LED3_taskHandle);//�����������
		while(1)
		{
			    if (xQueueReceive(queuekey1Handle, &i, NULL) == pdPASS) {
            switch(i)
						{
							printf("666666\r\n");
							case 1:
								osThreadSuspend(LED2_taskHandle);//�����������
	            	osThreadSuspend(LED3_taskHandle);//�����������
								osThreadResume(LED1_taskHandle);
							break;
							case 2:
								osThreadSuspend(LED1_taskHandle);//�����������
	            	osThreadSuspend(LED3_taskHandle);//�����������
								osThreadResume(LED2_taskHandle);	
							break;
							case 3:
								osThreadSuspend(LED2_taskHandle);//�����������
		            osThreadSuspend(LED1_taskHandle);//�����������
								osThreadResume(LED3_taskHandle);
							}
						}
		
						
          }
						vTaskDelay(2);
					}

/***   ִ��OLED����  ***/
void oled_task()
{
		while(1)
		{
			
	
		vTaskDelay(200);
		}
}
/*   ִ��LED */
void led1_task()
{
	//EventBits_t myEventBits_1=0;
		while(1)
		{
		//	myEventBits_1=xEventGroupWaitBits(EventKey1Handle,Event_0,pdTRUE,pdTRUE,portMAX_DELAY);
//			if(myEventBits_1 & Event_0)
//			{
			  HAL_GPIO_TogglePin (LED1_GPIO_Port,LED1_Pin);
	 		  printf("��ƽ��ת1\r\n");
	     	vTaskDelay(200);
		   
		}
}
		
void led2_task()
{
	//EventBits_t myEventBits_2=0;
		while(1)
		{
			//	myEventBits_2=xEventGroupWaitBits(EventKey1Handle,Event_1,pdTRUE,pdTRUE,portMAX_DELAY);
//			if(myEventBits_2&Event_1)
//			{
		HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
		printf("��ƽ��ת2\r\n");
		vTaskDelay(200);
		
			}
}
void led3_task()
{
	
    //EventBits_t myEventBits_3=0;
		while(1)
		{
//			
//	//		myEventBits_3=xEventGroupWaitBits(EventKey1Handle,Event_2,pdTRUE,pdTRUE,portMAX_DELAY);
//			if(myEventBits_3&Event_2)
//			{
	  HAL_GPIO_TogglePin (LED3_GPIO_Port,LED3_Pin);
	  printf("��ƽ��ת3\r\n");
			vTaskDelay(200);
			}
			
//		}
}



/*****  ���������ж�  ��TIM2�ж���ִ��  ****/
void user_TIM2_IRQHandler(void)   
{
	uint8_t queue_flag=0;
	KEY_ReadStateMachine();  //����״̬��
		
			if(KeyCfg.KEY_Event == KEY_Event_SingleClick)
			{
//		xEventGroupSetBitsFromISR(EventKey1Handle ,Event_0 ,NULL);
				queue_flag=1;
				xQueueSendFromISR(queuekey1Handle, &queue_flag, NULL);
				frame_buf(&frame1,&Data1[0],1);	
			  printf("111\r\n");//�¼�����
			}
			else if(KeyCfg.KEY_Event == KEY_Event_DoubleClick)
			{ 
//		xEventGroupSetBitsFromISR(EventKey1Handle,Event_1,NULL);
				queue_flag=2;				
				xQueueSendFromISR(queuekey1Handle, &queue_flag, NULL);
			  frame_buf(&frame1,&Data1[1],1);		
        printf("222\r\n");//�¼�����				
			}
			else if(KeyCfg.KEY_Event == KEY_Event_LongPress)
			{
//		xEventGroupSetBitsFromISR(EventKey1Handle ,Event_2,NULL);
				queue_flag=3;
				xQueueSendFromISR(queuekey1Handle, &queue_flag, NULL);
				frame_buf(&frame1,&Data1[2],1);	
			 	printf("333\r\n");//�¼�����
			}
}



/*���ڽ��ջص�*/
/* ���ذ������ʹ�ù�����ʹ���񵥸�ִ��*/
/*ͨ��������У����յ����ݺ�д���У�֮���ڵ�����һ�������н����������*/
/****   ʹ���¼���������񵥸�����ִ��    *****/
void User_rx_Callback(uint8_t data)
{
	uint8_t queue_flag=0;
	if( data==0x11)
	 {
	  //����
		queue_flag=1;
	//	printf("��ƽ��ת11\r\n");
		/* д���� */
		xQueueSendFromISR(queuekey1Handle, &queue_flag, NULL);
	 }
	if( data== 0x22)
	 {
	  //����
		queue_flag=2;
  //  printf("��ƽ��ת22\r\n");
		/* д���� */
		xQueueSendFromISR(queuekey1Handle, &queue_flag, NULL);
	 }
	if( data== 0x33)
	 {
	  //����
		queue_flag=3;
		printf("��ƽ��ת33\r\n");
		/* д���� */
		xQueueSendFromISR(queuekey1Handle, &queue_flag, NULL);
 	 }
}


/*  ���лص�����  */
/*���������Ļ���ʹ��commit���Ͳ�ͬ���������ٿظ��������ʵ�ֲ�ͬ����*/
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart,uint16_t Size)
{
	uint8_t cnt =0;
	uint8_t ring_data[RING_BUFF_SIZE];
//	uint32_t data_32;
//	uint32_t crc;
//	int commit;//���մ�����ָ��      
	memset(ring_data,0,sizeof(ring_data));
	
	WriteRingBuffer(&Ring_Buff,DataBuff, DataBuff[4]+6);
	ReadRingBuffer(&Ring_Buff,ring_data , DataBuff[4]+6);   
//	for(int i=0;i<7;i++){
//	printf("ring_data[%d]=%u\r\n",i,ring_data[i]);
//	}
 if( huart->Instance == USART1)
   {   
				if(ring_data[0] == usart_frame_hand1&&
					 ring_data[1] == usart_frame_hand2&& 
					 ring_data[2] == usart_frame_hand1  )   //����Ƿ��ǰ�ͷ  DataBuff[%d]=	 
			 {  
		  	//  commit= DataBuff[3];                 //���շ������������ִ�в�ͬ�Ĵ��룬����ûд�Ժ󲹳�
			cnt =  ring_data[4];
			cnt+=4;
			 //CRC���� && ����Ƿ��ǰ�β
				// 	memcpy(&data_32, ring_data, 4);
//	 crc=CRC16_Check(&data_32, cnt+1);
//   data_32 = ((uint32_t)ring_data[cnt+1]<< 24)|((uint32_t)ring_data[cnt+2]<<16)|((uint32_t)ring_data[cnt+3]<<8)|(uint32_t)ring_data[cnt+4];
//				  printf("crc=%u\r\n",crc);
//				   printf("data_32=%u\r\n",data_32);
			if(ring_data[cnt+1] == usart_frame_end ) 
				{ 
					  for(int i=0;i<=cnt;i++){
			      uint8_t data= ring_data[i+5];
						User_rx_Callback(data);		
					}						
				} 
			else  
			 {
					memset(ring_data,0,sizeof(ring_data));
			 } 
	  } 
  }
}






