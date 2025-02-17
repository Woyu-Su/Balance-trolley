#include "stm32f10x.h"        

extern int sensor[6];//引用主函数main定义的数组，才能在本文件内使用sensor[x]该变量
int error=0;//小车的位置偏移量 误差(error),位置偏移越大，误差越大，偏移越小，误差越小


void Sensor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能GPIOB的时钟
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//IO管脚模式配置为浮空输入，这样就能获取传感器传回来的数字信号(高低电平)
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);//PB4,5,8,9,10,11管脚的初始化
}


/*
将位置从最左按顺序到最右的传感器返回的数字信号依次存入数组sensor[0--6]
红外传感器识别到黑线返回数字信号低电平1，未识别到黑线返回高电平0
*/
void read_sensor(void)
{

	sensor[0]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);//最左的传感器
	sensor[1]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5);
	sensor[2]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8);
	sensor[3]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9);
	sensor[4]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10);
	sensor[5]=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);//最右的传感器
	
	if(sensor[0]==0&&sensor[1]==0&&sensor[2]==1&&sensor[3]==1&&sensor[4]==0&&sensor[5]==0)//001100
	{
		error=0;
	}
	else if(sensor[0]==1&&sensor[1]==1&&sensor[2]==1&&sensor[3]==1&&sensor[4]==1&&sensor[5]==1)//111111
	{
		error=0;
	}
}
