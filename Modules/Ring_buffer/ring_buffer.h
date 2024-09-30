#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

#define RING_BUFF_SIZE 200

typedef struct ringBuff{
    unsigned int in;                             //д���λ��
    unsigned int out;                            //������λ��
    unsigned char buffer[RING_BUFF_SIZE];     //������
}stRingBuff;

//�ж϶����Ƿ�Ϊ��
int IsRingBufferEmpty(stRingBuff *ringBuf);

//�ж϶����Ƿ�Ϊ��
int IsRingBufferFull(stRingBuff *ringBuf);

//дһ���ֽ�	
void WriteOneByteToRingBuffer(stRingBuff *ringBuf,char data);

//��һ���ֽ�
void ReadOneByteFromRingBuffer(stRingBuff *ringBuf,char *data);
	
//д�����ֽ�
void WriteRingBuffer(stRingBuff *ringBuf,char *writeBuf,unsigned int len);
	
//�������ֽ�
void ReadRingBuffer(stRingBuff *ringBuf,char *readBuf,unsigned int len);

//��ȡ���г���
int GetRingBufferLength(stRingBuff *ringBuf);

#endif

