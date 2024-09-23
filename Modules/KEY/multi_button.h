/*
 * Copyright (c) 2016 Zibin Zheng <znbin@qq.com>
 * All rights reserved
 */

#ifndef _MULTI_BUTTON_H_
#define _MULTI_BUTTON_H_

#include <stdint.h>
#include <string.h>

//According to your need to modify the constants.
#define TICKS_INTERVAL    5	//ms
#define DEBOUNCE_TICKS    3	//MAX 7 (0 ~ 7)
#define SHORT_TICKS       (300 /TICKS_INTERVAL)
#define LONG_TICKS        (1000 /TICKS_INTERVAL)


typedef void (*BtnCallback)(void*);

typedef enum {
	PRESS_DOWN = 0,     // �������£�ÿ�ΰ��¶�����
	PRESS_UP,			// ��������ÿ���ɿ�������			
	PRESS_REPEAT,		// �ظ����´���������repeat������������
	SINGLE_CLICK,		// ���������¼�
	DOUBLE_CLICK,		// ˫�������¼�
	LONG_PRESS_START,	// �ﵽ����ʱ����ֵʱ����һ��
	LONG_PRESS_HOLD,	// �����ڼ�һֱ����
	number_of_event,	//�¼�������
	NONE_PRESS
}PressEvent;

typedef struct Button {
	uint16_t ticks;
	uint8_t  repeat : 4; 					  // ��¼��������
	uint8_t  event : 4;	  					  // ��¼�����¼�
	uint8_t  state : 3;	 					  // ��һ��Ҫ��ת��״̬������״̬���л�
	uint8_t  debounce_cnt : 3;  			  // ��¼����������ÿ�ι̶�ʱ�䣬����ȥ����
	uint8_t  active_level : 1; 				  // ��Ч��ƽ����������ʱ�ĵ�ƽ��
	uint8_t  button_level : 1;  			  // ��¼��ǰ�ĵ�ƽ
	uint8_t  (*hal_button_Level)(void);		  // ����ָ�루ָ���ȡ��ǰ������ƽ�ĺ�����
	BtnCallback  cb[number_of_event];   	  // ����ָ�����飺�ֱ�ָ������¼��Ļص�����
	struct Button* next;

}Button;

#ifdef __cplusplus
extern "C" {
#endif

void button_init(struct Button* handle, uint8_t(*pin_level)(), uint8_t active_level);
void button_attach(struct Button* handle, PressEvent event, BtnCallback cb);
PressEvent get_button_event(struct Button* handle);
int  button_start(struct Button* handle);
void button_stop(struct Button* handle);
void button_ticks(void);

#ifdef __cplusplus
}
#endif

#endif
