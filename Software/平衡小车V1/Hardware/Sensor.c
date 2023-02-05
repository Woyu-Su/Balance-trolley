#include "stm32f10x.h"                  // Device header

extern int sensor[6];//����������main��������飬�����ڱ��ļ���ʹ��sensor[x]�ñ���
int error=0;//С����λ��ƫ���� ���(error),λ��ƫ��Խ�����Խ��ƫ��ԽС�����ԽС


void Sensor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIOA��ʱ��
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��GPIOB��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//ʹ�ܸ��ù��ܵ�ʱ��
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//IO�ܽ�ģʽ����Ϊ�������룬�������ܻ�ȡ�������������������ź�(�ߵ͵�ƽ)
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//PA4,PA5,PA6,PA7�ܽŵĳ�ʼ��
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//��������ģʽ
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);//PB0,PB1�ܽŵĳ�ʼ��
	  
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//�������ģʽ
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);//PB8�ܽŵĳ�ʼ����TB6612����������ʹ�ܶ�
	

}

void read_sensor(void)//���⴫����ʶ�𵽺��߷��������źŵ͵�ƽ1��δʶ�𵽺��߷��ظߵ�ƽ0
{
	      /*��λ�ô�����˳�����ҵĴ��������ص������ź����δ�������sensor[0��6]��*/
	sensor[0]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2);//����Ĵ�����
	sensor[1]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);
	sensor[2]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
	sensor[3]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5);
	sensor[4]=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);
	sensor[5]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1);
	
	if(sensor[0]==0&&sensor[1]==0&&sensor[2]==1&&sensor[3]==1&&sensor[4]==0&&sensor[5]==0)//001100
	{
		error=0;
	}
	else if(sensor[0]==1&&sensor[1]==1&&sensor[2]==1&&sensor[3]==1&&sensor[4]==1&&sensor[5]==1)//111111
	{
		error=0;
	}
}
