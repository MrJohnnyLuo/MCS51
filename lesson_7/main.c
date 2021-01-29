/*
*******************************************************************************
*                     《手把手教你学51单片机(C语言版)》
*                    配套 KST-51 单片机开发板 示例源代码
*
*         (c) 版权所有 2014 金沙滩工作室/清华大学出版社 保留所有权利
*                 获取更多资料请访问：http://www.kingst.org
*
* 文件名：main.c
* 描  述：第7章 基于数码管计时程序的静态变量演示
* 版本号：v1.0.0
* 备  注：详情见第7章7.2节
*******************************************************************************
*/

#include <reg52.h>
#include <model.h>

#if LessonNumber == Lesson_7_1 //基于数码管计时程序的静态变量演示
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code LedChar[] = {	//数码管显示字符转换表
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};
unsigned char LedBuff[6] = {	//数码管显示缓冲区，初值0xFF确保启动时都不亮
  	0xFF, 0xFF,	0xFF, 0xFF,	0xFF, 0xFF,
};
unsigned char flag1s = 0;	//1秒定时标志

void main()
{
	unsigned long sec = 0;	//记录经过的秒数
	
	EA = 1;			//使能总中断
	ENLED = 0;	   	//使能U3，选择控制数码管
	ADDR3 = 1;	   	//因为需要动态改变ADDR0-2的值，所以不需要再初始化了
	TMOD = 0x01;   	//设置T0为模式1
	TH0 = 0xFC;	   	//为T0赋初值0xFC67，定时1ms
	TL0 = 0x67;
	TR0 = 1;	   	//使能T0中断
	ET0 = 1;	   	//启动T0

	while(1)
	{
		if (flag1s == 1)	//判断1秒定时标志
		{
			flag1s = 0;		//1秒定时标志清零
			sec++;		 	//秒计数自加1
			//以下代码将sec按十进制位从低到高依次提取并转为数码管显示字符
			LedBuff[0] = LedChar[sec%10];
			LedBuff[1] = LedChar[sec/10%10];
			LedBuff[2] = LedChar[sec/100%10];
			LedBuff[3] = LedChar[sec/1000%10];
			LedBuff[4] = LedChar[sec/10000%10];
			LedBuff[5] = LedChar[sec/100000%10];
		}
	}
}

/* 定时器0中断服务函数 */
void InterruptTime0() interrupt 1
{
	static unsigned char i = 0;	 //动态扫描的索引，定义为局部静态变量
	static unsigned int cnt = 0; //记录T0中断次数，定义为局部静态变量
	
	TH0 = 0xFC;	//重新加载初值
	TL0 = 0x67;
	cnt++;	   	//中断次数计数值加1

	if (cnt >= 1000)	//中断1000次即1秒
	{
		cnt = 0;	  	//清零计数值以重新开始下1秒计时
		flag1s = 1;	  	//设置1秒定时标志为1
	}

	//以下代码完成数码管动态扫描刷新
	P0 = 0xFF;	//显示消隐
	switch(i)
	{
		case 0: ADDR2=0; ADDR1=0; ADDR0=0; i++; P0=LedBuff[0]; break;
		case 1: ADDR2=0; ADDR1=0; ADDR0=1; i++; P0=LedBuff[1]; break;
		case 2: ADDR2=0; ADDR1=1; ADDR0=0; i++; P0=LedBuff[2]; break;
		case 3: ADDR2=0; ADDR1=1; ADDR0=1; i++; P0=LedBuff[3]; break;
		case 4: ADDR2=1; ADDR1=0; ADDR0=0; i++; P0=LedBuff[4]; break;
		case 5: ADDR2=1; ADDR1=0; ADDR0=1; i=0; P0=LedBuff[5]; break;
		default: break;
	}
}

#elif LessonNumber == Lesson_7_2 //点亮LED点阵上的一个点
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;
sbit LED = P0^0;

void main()
{
	ENLED = 0;	//U3、U4两片74HC138总使能
	ADDR3 = 0;	//使能U4使之正常输出
	ADDR2 = 0;	//经U4的Y1输出开启三极管Q11
	ADDR1 = 0;
	ADDR0 = 0;

	LED = 0;	//向P0.0写入0来点亮左上角的一个点
	while(1);	//程序停止在这里
}

#elif LessonNumber == Lesson_7_3 //点亮LED点阵上一行
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void main()
{
	ENLED = 0;	//U3、U4两片74HC138总使能
	ADDR3 = 0;	//使能U4使之正常输出
	ADDR2 = 0;	//经U4的Y1输出开启三极管Q11
	ADDR1 = 0;
	ADDR0 = 0;

	P0 = 0x00;	//向P0写入0来点亮一行
	while(1);	//程序停止在这里
}

#elif LessonNumber == Lesson_7_4 //点亮LED点阵上的全部点
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void main()
{
	EA = 1;			//使能总中断
	ENLED = 0;		//使能U4，选择LED点阵
	ADDR3 = 0;		//因为需要动态改变ADDR0-2的值，所以不需要再初始化了
	TMOD = 0x01;	//设置T0为模式1
	TH0 = 0xFC;		//为T0赋初值0xFC67，定时1ms
	TL0 = 0x67;
	TR0 = 1;		//启动T0
	ET0 = 1;		//使能T0中断

	while(1);		//程序停在这里，等待定时器中断
}
/* 定时器0中断服务函数 */
void InterruptTime0() interrupt 1
{
	static unsigned char i = 0;	//动态扫描的索引

	TH0 = 0xFC;	//重新加载初值
	TL0 = 0x67;
    //以下代码完成LED点阵动态扫描刷新
	P0 = 0xFF;	//显示消隐
	switch(i)
	{
		case 0: ADDR2=0; ADDR1=0; ADDR0=0; i++; P0=0x00; break;
		case 1: ADDR2=0; ADDR1=0; ADDR0=1; i++; P0=0x00; break;
		case 2: ADDR2=0; ADDR1=1; ADDR0=0; i++; P0=0x00; break;
		case 3: ADDR2=0; ADDR1=1; ADDR0=1; i++; P0=0x00; break;
		case 4: ADDR2=1; ADDR1=0; ADDR0=0; i++; P0=0x00; break;
		case 5: ADDR2=1; ADDR1=0; ADDR0=1; i++; P0=0x00; break;
		case 6: ADDR2=1; ADDR1=1; ADDR0=0; i++; P0=0x00; break;
		case 7: ADDR2=1; ADDR1=1; ADDR0=1; i=0; P0=0x00; break;
		default: break;
	}
}

#elif LessonNumber == Lesson_7_5 //LED点阵显示静态图形
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code Heart[] = {	//"心"型图片的字模表
	0xFF,0x99,0x00,0x00,0x00,0x81,0xC3,0xE7,
};

void main()
{
	EA = 1;			//使能总中断
	ENLED = 0;		//使能U4，选择LED点阵
	ADDR3 = 0;
	TMOD = 0x01;	//设置T0为模式1
	TH0 = 0xFC;		//为T0赋初值0xFC67，定时1ms
	TL0 = 0x67;
	TR0 = 1;		//启动T0
	ET0 = 1;		//使能T0中断

	while(1);
}
/* 定时器0中断服务函数 */
void InterruptTime0() interrupt 1
{
	static unsigned char i = 0;	//动态扫描的索引

	TH0 = 0xFC;	//重新加载初值
	TL0 = 0x67;
	//以下代码完成LED点阵动态扫描刷新
	P0 = 0xFF;	//显示消隐
	switch(i)
	{
		case 0: ADDR2=0; ADDR1=0; ADDR0=0; i++; P0=Heart[0]; break;
		case 1: ADDR2=0; ADDR1=0; ADDR0=1; i++; P0=Heart[1]; break;
		case 2: ADDR2=0; ADDR1=1; ADDR0=0; i++; P0=Heart[2]; break;
		case 3: ADDR2=0; ADDR1=1; ADDR0=1; i++; P0=Heart[3]; break;
		case 4: ADDR2=1; ADDR1=0; ADDR0=0; i++; P0=Heart[4]; break;
		case 5: ADDR2=1; ADDR1=0; ADDR0=1; i++; P0=Heart[5]; break;
		case 6: ADDR2=1; ADDR1=1; ADDR0=0; i++; P0=Heart[6]; break;
		case 7: ADDR2=1; ADDR1=1; ADDR0=1; i=0; P0=Heart[7]; break;
		default: break;
	}
}

#elif LessonNumber == Lesson_7_6 //LED点阵显示纵向移动的动画
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code I_Love_You[] = {	//"I Love You"图片的字模表
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xC3,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xC3,
	0xFF,0x99,0x00,0x00,0x00,0x81,0xC3,0xE7,
	0xFF,0x99,0x99,0x99,0x99,0x99,0x81,0xC3,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};

void main()
{
	EA = 1;			//使能总中断
	ENLED = 0;		//使能U4，选择LED点阵
	ADDR3 = 0;
	TMOD = 0x01;	//设置T0为模式1
	TH0 = 0xFC;		//为T0赋初值0xFC67，定时1ms
	TL0 = 0x67;
	TR0 = 1;		//启动T0
	ET0 = 1;		//使能T0中断

	while(1);
}
/* 定时器0中断服务函数 */
void InterruptTime0() interrupt 1
{
	static unsigned char i = 0;		//动态扫描的索引
	static unsigned char tmr = 0;	//250ms软件定时器
	static unsigned char index = 0;	//图片刷新索引

	TH0 = 0xFC;	//重新加载初值
	TL0 = 0x67;
	tmr++;
	//以下代码完成LED点阵动态扫描刷新
	P0 = 0xFF;	//显示消隐
	switch(i)
	{
		case 0: ADDR2=0; ADDR1=0; ADDR0=0; i++; P0=I_Love_You[index+0]; break;
		case 1: ADDR2=0; ADDR1=0; ADDR0=1; i++; P0=I_Love_You[index+1]; break;
		case 2: ADDR2=0; ADDR1=1; ADDR0=0; i++; P0=I_Love_You[index+2]; break;
		case 3: ADDR2=0; ADDR1=1; ADDR0=1; i++; P0=I_Love_You[index+3]; break;
		case 4: ADDR2=1; ADDR1=0; ADDR0=0; i++; P0=I_Love_You[index+4]; break;
		case 5: ADDR2=1; ADDR1=0; ADDR0=1; i++; P0=I_Love_You[index+5]; break;
		case 6: ADDR2=1; ADDR1=1; ADDR0=0; i++; P0=I_Love_You[index+6]; break;
		case 7: ADDR2=1; ADDR1=1; ADDR0=1; i=0; P0=I_Love_You[index+7]; break;
		default: break;
	}
    //以下代码完成每250ms改变一帧图像
	if (tmr >= 250)	//达到250ms时改变一次图片索引
	{
		tmr = 0;
		index++;
		if (index >= 32)	//图片索引达到32后归零
		{
			index = 0;
		}
	}
}

#elif LessonNumber == Lesson_7_6_h //LED点阵显示横向移动的动画(掉转板子方向的取巧方式)
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code I_Love_You_hengxiang[] = {	//"I Love You"横向图片的字模表
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0x7D,0x01,0x01,0x7D,0xFF,0xFF,0xE3,0xC1,
	0x81,0x03,0x03,0x81,0xC1,0xE3,0xFF,0xFF,
	0x81,0x01,0x7F,0x7F,0x7F,0x01,0x81,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};

void main()
{
	EA = 1;			//使能总中断
	ENLED = 0;		//使能U4，选择LED点阵
	ADDR3 = 0;
	TMOD = 0x01;	//设置T0为模式1
	TH0 = 0xFC;		//为T0赋初值0xFC67，定时1ms
	TL0 = 0x67;
	TR0 = 1;		//启动T0
	ET0 = 1;		//使能T0中断

	while(1);
}
/* 定时器0中断服务函数 */
void InterruptTime0() interrupt 1
{
	static unsigned char i = 0;		//动态扫描的索引
	static unsigned char tmr = 0;	//250ms软件定时器
	static unsigned char index = 0;	//图片刷新索引

	TH0 = 0xFC;	//重新加载初值
	TL0 = 0x67;
	tmr++;
	//以下代码完成LED点阵动态扫描刷新
	P0 = 0xFF;	//显示消隐
	switch(i)
	{
		case 0: ADDR2=0; ADDR1=0; ADDR0=0; i++; P0=I_Love_You_hengxiang[index+0]; break;
		case 1: ADDR2=0; ADDR1=0; ADDR0=1; i++; P0=I_Love_You_hengxiang[index+1]; break;
		case 2: ADDR2=0; ADDR1=1; ADDR0=0; i++; P0=I_Love_You_hengxiang[index+2]; break;
		case 3: ADDR2=0; ADDR1=1; ADDR0=1; i++; P0=I_Love_You_hengxiang[index+3]; break;
		case 4: ADDR2=1; ADDR1=0; ADDR0=0; i++; P0=I_Love_You_hengxiang[index+4]; break;
		case 5: ADDR2=1; ADDR1=0; ADDR0=1; i++; P0=I_Love_You_hengxiang[index+5]; break;
		case 6: ADDR2=1; ADDR1=1; ADDR0=0; i++; P0=I_Love_You_hengxiang[index+6]; break;
		case 7: ADDR2=1; ADDR1=1; ADDR0=1; i=0; P0=I_Love_You_hengxiang[index+7]; break;
		default: break;
	}
    //以下代码完成每250ms改变一帧图像
	if (tmr >= 250)	//达到250ms时改变一次图片索引
	{
		tmr = 0;
		index++;
		if (index >= 32)	//图片索引达到32后归零
		{
			index = 0;
		}
	}
}

#elif LessonNumber == Lesson_7_7 //LED点阵显示横向移动的动画
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code I_Love_You_hengxiang_30[30][8] = {	//"I Love You"横向图片的字模表
	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},	//动画帧1
	{0xFF,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F},	//动画帧2
	{0xFF,0x3F,0x7F,0x7F,0x7F,0x7F,0x7F,0x3F},	//动画帧3
	{0xFF,0x1F,0x3F,0x3F,0x3F,0x3F,0x3F,0x1F},	//动画帧4
	{0xFF,0x0F,0x9F,0x9F,0x9F,0x9F,0x9F,0x0F},	//动画帧5
	{0xFF,0x87,0xCF,0xCF,0xCF,0xCF,0xCF,0x87},	//动画帧6
	{0xFF,0xC3,0xE7,0xE7,0xE7,0xE7,0xE7,0xC3},	//动画帧7
	{0xFF,0xE1,0x73,0x73,0x73,0xF3,0xF3,0xE1},	//动画帧8
	{0xFF,0x70,0x39,0x39,0x39,0x79,0xF9,0xF0},	//动画帧9
	{0xFF,0x38,0x1C,0x1C,0x1C,0x3C,0x7C,0xF8},	//动画帧10
	{0xFF,0x9C,0x0E,0x0E,0x0E,0x1E,0x3E,0x7C},	//动画帧11
	{0xFF,0xCE,0x07,0x07,0x07,0x0F,0x1F,0x3E},	//动画帧12
	{0xFF,0x67,0x03,0x03,0x03,0x07,0x0F,0x9F},	//动画帧13
	{0xFF,0x33,0x01,0x01,0x01,0x03,0x87,0xCF},	//动画帧14
	{0xFF,0x99,0x00,0x00,0x00,0x81,0xC3,0xE7},	//动画帧15
	{0xFF,0xCC,0x80,0x80,0x80,0xC0,0xE1,0xF3},	//动画帧16
	{0xFF,0xE6,0xC0,0xC0,0xC0,0xE0,0xF0,0xF9},	//动画帧17
	{0xFF,0x73,0x60,0x60,0x60,0x70,0x78,0xFC},	//动画帧18
	{0xFF,0x39,0x30,0x30,0x30,0x38,0x3C,0x7E},	//动画帧19
	{0xFF,0x9C,0x98,0x98,0x98,0x9C,0x1E,0x3F},	//动画帧20
	{0xFF,0xCE,0xCC,0xCC,0xCC,0xCE,0x0F,0x1F},	//动画帧21
	{0xFF,0x67,0x66,0x66,0x66,0x67,0x07,0x0F},	//动画帧22
	{0xFF,0x33,0x33,0x33,0x33,0x33,0x03,0x87},	//动画帧23
	{0xFF,0x99,0x99,0x99,0x99,0x99,0x81,0xC3},	//动画帧24
	{0xFF,0xCC,0xCC,0xCC,0xCC,0xCC,0xC0,0xE1},	//动画帧25
	{0xFF,0xE6,0xE6,0xE6,0xE6,0xE6,0xE0,0xF0},	//动画帧26
	{0xFF,0xF3,0xF3,0xF3,0xF3,0xF3,0xF0,0xF8},	//动画帧27
	{0xFF,0xF9,0xF9,0xF9,0xF9,0xF9,0xF8,0xFC},	//动画帧28
	{0xFF,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFE},	//动画帧29
	{0xFF,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFF},	//动画帧30
};

void main()
{
	EA = 1;			//使能总中断
	ENLED = 0;		//使能U4，选择LED点阵
	ADDR3 = 0;
	TMOD = 0x01;	//设置T0为模式1
	TH0 = 0xFC;		//为T0赋初值0xFC67，定时1ms
	TL0 = 0x67;
	TR0 = 1;		//启动T0
	ET0 = 1;		//使能T0中断

	while(1);
}
/* 定时器0中断服务函数 */
void InterruptTime0() interrupt 1
{
	static unsigned char i = 0;		//动态扫描的索引
	static unsigned char tmr = 0;	//250ms软件定时器
	static unsigned char index = 0;	//图片刷新索引

	TH0 = 0xFC;	//重新加载初值
	TL0 = 0x67;
	tmr++;
	//以下代码完成LED点阵动态扫描刷新
	P0 = 0xFF;	//显示消隐
	switch(i)
	{
		case 0: ADDR2=0; ADDR1=0; ADDR0=0; i++; P0=I_Love_You_hengxiang_30[index][0]; break;
		case 1: ADDR2=0; ADDR1=0; ADDR0=1; i++; P0=I_Love_You_hengxiang_30[index][1]; break;
		case 2: ADDR2=0; ADDR1=1; ADDR0=0; i++; P0=I_Love_You_hengxiang_30[index][2]; break;
		case 3: ADDR2=0; ADDR1=1; ADDR0=1; i++; P0=I_Love_You_hengxiang_30[index][3]; break;
		case 4: ADDR2=1; ADDR1=0; ADDR0=0; i++; P0=I_Love_You_hengxiang_30[index][4]; break;
		case 5: ADDR2=1; ADDR1=0; ADDR0=1; i++; P0=I_Love_You_hengxiang_30[index][5]; break;
		case 6: ADDR2=1; ADDR1=1; ADDR0=0; i++; P0=I_Love_You_hengxiang_30[index][6]; break;
		case 7: ADDR2=1; ADDR1=1; ADDR0=1; i=0; P0=I_Love_You_hengxiang_30[index][7]; break;
		default: break;
	}
    //以下代码完成每250ms改变一帧图像
	if (tmr >= 250)	//达到250ms时改变一次图片索引
	{
		tmr = 0;
		index++;
		if (index >= 30)	//图片索引达到30后归零
		{
			index = 0;
		}
	}
}

#endif

