#include "ring_buffer.h"
#include "stddef.h"



//�ж������Ƿ�д��
int IsRingBufferFull(stRingBuff *ringBuf)
{
  if (ringBuf == NULL)
    {
        return 0;    
    }
  if(((ringBuf->in+1) % RING_BUFF_SIZE) == ringBuf->out)
    {
        return 1;
    }
    return 0;
	}

	

void WriteOneByteToRingBuffer(stRingBuff *ringBuf,char data)
{
 if (ringBuf == NULL || IsRingBufferFull(ringBuf))//д֮ǰ���ж϶����Ƿ�д��
    {     
        return;
    }
    ringBuf->buffer[ringBuf->in] = data;
    ringBuf->in = (++ringBuf->in) % RING_BUFF_SIZE;    //��ֹԽ��
 
}



//��дһ���ֽ�
void ReadOneByteFromRingBuffer(stRingBuff *ringBuf,char *data)
{
 if (ringBuf == NULL||IsRingBufferEmpty(ringBuf)) //��֮ǰ�ж϶����Ƿ�Ϊ��
    {
       
        return;
    }
		
    *data = ringBuf->buffer[ringBuf->out];
    ringBuf->out = (++ringBuf->out) % RING_BUFF_SIZE;    //��ֹԽ�� 
}


//д�����ֽ�
void WriteRingBuffer(stRingBuff *ringBuf,char *writeBuf,unsigned int len)
{
    unsigned int i;
 
 if (ringBuf == NULL)
    {
        return ;
    }
    
    for(i = 0; i < len; i++)
    {
        WriteOneByteToRingBuffer(ringBuf,writeBuf[i]);
    }
}
	
	
//�������ֽ�
void ReadRingBuffer(stRingBuff *ringBuf,char *readBuf,unsigned int len)
{
    unsigned int i;
	
 if (ringBuf == NULL)
    {       
        return;
    }
    for(i = 0; i < len; i++)
    {
        ReadOneByteFromRingBuffer(ringBuf,&readBuf[i]);
    }
}

//��ȡ�Ѿ�д����е����ݳ���
int GetRingBufferLength(stRingBuff *ringBuf)
{
    if (ringBuf == NULL)
    {
        return 0;
    }
 
    return (ringBuf->in - ringBuf->out + RING_BUFF_SIZE) % RING_BUFF_SIZE;
}

int IsRingBufferEmpty(stRingBuff *ringBuf)
{ 
 if (ringBuf == NULL)
    {     
        return 0;
    }
    
 if(ringBuf->in == ringBuf->out)   //д��λ�úͶ���λ�����ʱΪ��
    {
        return 1;
    }
    return 0;
}

