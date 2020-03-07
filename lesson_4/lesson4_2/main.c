#include<reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void main()
{
	unsigned int i = 0;		//定义循环变量i，用于软件延时
	unsigned char cnt = 0;	//定义计数变量cnt，用于移位控制

	ENLED = 0;
	ADDR3 = 1;
	ADDR2 = 1;
	ADDR1 = 1;
	ADDR0 = 0;

	while(1)	//主循环，程序无限循环执行该循环体语句
	{
		P0 = ~(0x01 << cnt);	//P0等于1左移cnt位，控制8个LED
		for(i=0; i<30000; i++);	//软件延时
		cnt++;				  	//移位计数变量自加1
		if(cnt >= 8)		  	//移位计数超过7后，再重新从0开始
		{
			cnt = 0;			
		}
	}
}