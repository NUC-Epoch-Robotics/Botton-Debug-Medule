#ifndef __SELF_DEF_MASSAGE_H
#define __SELF_DEF_MASSAGE_H

#include "gpio.h"

#define usart_frame_hand1 0x5A    //֡ͷ
#define usart_frame_hand2 0xA5    //֡ͷ

#define usart_frame_end2  0xD0    //֡β

#define usart_W_REG            0x80                     //USARTд�Ĵ���ָ��
#define usart_R_REG            0x81                     //USART���Ĵ���ָ��
#define usart_W_DATA           0x82                     //USARTд����ָ��
#define usart_R_DATA           0x83                     //USART������ָ��
 
#define USART_PACKAGE_LEN  1024

/*����֡*/
/*����֡���ͽṹ��*/  
typedef struct 
{  
    uint16_t send_sum_len;          //Ҫ���͵�֡���ݳ���  
    uint8_t  send_cur_len;          //��ǰ�Ѿ����͵����ݳ���  
    uint8_t  send_flag;             //�Ƿ��ͱ�־  
    uint8_t * send_data;            //ָ��Ҫ���͵����ݻ�����  
}uart_send_struct;  

typedef struct 
{  
    uint8_t * dst_buf;                  //ָ����ջ���  
    uint8_t sfd;                        //֡�ױ�־,Ϊ0xFF����0xEE  
    uint8_t sfd_flag;                   //�ҵ�֡��,һ����3~5��FF��EE  
    uint8_t sfd_count;                  //֡�׵ĸ���,һ��3~5��  
    uint8_t received_len;               //�Ѿ����յ��ֽ���  
    uint8_t find_fram_flag;             //�ҵ�����֡��,��1  
    uint8_t frame_len;                  //��֡�����ܳ��ȣ���������ǿ�ѡ��  
}find_frame_struct;


#endif


