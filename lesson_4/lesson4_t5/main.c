#include<reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void main()
{
	unsigned int i = 0;		//定义循环变量i，用于软件延时
	unsigned char dir = 0;		//定义移位方向变量dir，用于控制移位的方向
	unsigned char shift = 0x01;		//定义循环移位变量shift，并赋初值0x01

	ENLED = 0;
	ADDR3 = 1;
	ADDR2 = 1;
	ADDR1 = 1;
	ADDR0 = 0;

	while(1)		//主循环，程序无限循环执行该循环体语句
	{
		P0 = ~shift;		  	//P0等于循环移位变量取反，控制8个LED
		for(i=0; i<30000; i++);	//软件延时
		if(dir == 0)		  	//移位方向变量为0时，左移
		{
			shift = shift << 1;	//循环移位变量左移1位
			if(shift == 0x80)	//左移到最左端后，改变移位方向
			{
				dir = 1;
			}
		}
		else				  	//移位方向变量不为0时，右移
		{
			shift = shift >> 1;	//循环移位变量右移1位
			if(shift == 0x01)	//右移到最右端后，改变移位方向
			{
				dir = 0;
			}
		}
	}
}