#include "stm32f10x.h"        

extern int sensor[6];//����������main��������飬�����ڱ��ļ���ʹ��sensor[x]�ñ���
int error=0;//С����λ��ƫ���� ���(error),λ��ƫ��Խ�����Խ��ƫ��ԽС�����ԽС


void Sensor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��GPIOB��ʱ��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//IO�ܽ�ģʽ����Ϊ�������룬�������ܻ�ȡ�������������������ź�(�ߵ͵�ƽ)
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);//PB4,5,8,9,10,11�ܽŵĳ�ʼ��
}


/*
��λ�ô�����˳�����ҵĴ��������ص������ź����δ�������sensor[0--6]
���⴫����ʶ�𵽺��߷��������źŵ͵�ƽ1��δʶ�𵽺��߷��ظߵ�ƽ0
*/
void read_sensor(void)
{

	sensor[0]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);//����Ĵ�����
	sensor[1]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5);
	sensor[2]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8);
	sensor[3]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9);
	sensor[4]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10);
	sensor[5]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);//���ҵĴ�����
	
	if(sensor[0]==0&&sensor[1]==0&&sensor[2]==1&&sensor[3]==1&&sensor[4]==0&&sensor[5]==0)//001100
	{
		error=0;
	}
	else if(sensor[0]==1&&sensor[1]==1&&sensor[2]==1&&sensor[3]==1&&sensor[4]==1&&sensor[5]==1)//111111
	{
		error=0;
	}
}
