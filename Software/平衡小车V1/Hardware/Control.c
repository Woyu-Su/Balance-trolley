#include "stm32f10x.h"                  	
#include "PWM.h"
#include "Timer.h"


int M1PWM,M2PWM;
int PID_sd=0;																			//С������PID��������PWM���ֵ
extern int error;

int Position_PID (int Encoder,int Target)   											//����PID������//����Encoder=error��Target=0;
{ 	
	 float Position_KP=150,Position_KI=0.2,Position_KD=1000;
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  								//����ƫ��
	 Integral_bias+=Bias;	                                 							//���ƫ��Ļ���
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //λ��ʽPID������
	 Last_Bias=Bias;                                       								//������һ��ƫ�� 
	 return Pwm;                                           								//����PWMֵ
}


void Run_PID(void)																		//��OUTPUT��OUTPUT1��OUTPUT2�����ȥ��ʹ�����С������ܵ���Ӧ����
{
		  
		TIM_SetCompare2(TIM2,M1PWM);													//�������
	    TIM_SetCompare2(TIM2,M2PWM);													//�������
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		PID_sd=Position_PID (error,0);													//������PID�����������PWMֵ��ֵ��PID_sd       
		Run_PID();		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
