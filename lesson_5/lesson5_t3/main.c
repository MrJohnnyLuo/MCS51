/*	定时器查询模式实现左右移动的流水灯	*/
#include<reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void main()
{
	unsigned char cnt = 0;		//定义计数变量cnt，记录T0溢出次数
	unsigned char dir = 0; 		//定义移位方向变量dir，用于控制移位的方向
	unsigned char shift = 0x01;	//定义循环移位变量shift，并赋初值0x01

	ENLED = 0;		//使能U3，选择独立LED
	ADDR3 = 1;
	ADDR2 = 1;
	ADDR1 = 1;
	ADDR0 = 0;

	TMOD = 0x01;	//设置T0为模式1
	TH0 = 0xB0;	  	//为T0赋初值0xB800
	TL0 = 0x00;
	TR0 = 1;  		//启动T0

	while(1)  		//主循环，程序无限循环执行该循环体语句
	{
		P0 = ~shift; 		//P0等于循环移位变量取反，控制8个LED
		while( TF0 == 0 );	//当TF0等于0时一直执行空循环，即停在这里直到T0溢出
		TF0 = 0;			//T0溢出后，清零中断标志
		TH0 = 0xB0;	  		//并重新赋初值
		TL0 = 0x00;
		cnt++;	   			//计数值自加1
		if( cnt >= 10)		//T0溢出达到10次后，控制移位
		{
			cnt = 0;
			if( dir == 0 )				//移位方向变量为0时，左移
			{
				shift = shift << 1;	  	//循环移位变量左移1位
				if( shift == 0x80 )		//左移到最左端后，改变移位方向
				{
					dir = 1;
				}	
			}
			else			  			//移位方向变量不为0时，右移
			{
				shift = shift >> 1;		//循环移位变量右移1位
				if( shift == 0x01 )	 	//右移到最右端时，改变移位方向
				{
					dir = 0;
				}
			}
		}
	}
}