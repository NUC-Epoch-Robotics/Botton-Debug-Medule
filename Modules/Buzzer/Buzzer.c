#include "Buzzer.h"
#include "tim.h"


void Buzzer_init()
{
  HAL_TIM_PWM_Init(&htim3);// ��ʼ����ʱ����PWMģʽ
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);// ������ʱ����PWMģʽ	
}

void Buzzer_off(void)
{	
	HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);// ֹͣ��ʱ����PWM���
}

void Buzzzer_on(uint16_t Pulse)
{
  __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,Pulse);	
}









