#include<reg52.h>

sbit LED = P0^0;
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void main()
{
	unsigned char cnt = 0;	//定义一个计数变量，记录T0溢出次数

	ENLED = 0;		//使能U3，选择独立LED
	ADDR3 = 1;
	ADDR2 = 1;
	ADDR1 = 1;
	ADDR0 = 0;
	
	//x*12/11059200=0.02	x = 18432	65536 - x = 47104 = 0xB800
	TMOD = 0x01;	//设置T0为模式1
	TH0 = 0xB8;		//为T0赋初值0xB800
	TL0 = 0x00;
	TR0 = 1;		//启动T0

	while(1)
	{
		if( TF0 == 1 )			//判断T0是否溢出
		{
			TF0 = 0;			//T0溢出后，清零中断标志
			TH0 = 0xB8;			//并重新赋初值
			TL0 = 0x00;
			cnt++;				//计数值自加1
			if( cnt >= 50 )		//判断T0溢出是否达到50次
			{
				cnt = 0;		//达到50次后计数值清零
				LED = ~LED;		//LED取反：0-->1、1-->0
			}
		}
	}
}