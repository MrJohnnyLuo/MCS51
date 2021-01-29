/*
*******************************************************************************
*                     ���ְ��ֽ���ѧ51��Ƭ��(C���԰�)��
*                    ���� KST-51 ��Ƭ�������� ʾ��Դ����
*
*         (c) ��Ȩ���� 2014 ��ɳ̲������/�廪��ѧ������ ��������Ȩ��
*                 ��ȡ������������ʣ�http://www.kingst.org
*
* �ļ�����main.c
* ��  ������7�� ��������ܼ�ʱ����ľ�̬������ʾ
* �汾�ţ�v1.0.0
* ��  ע���������7��7.2��
*******************************************************************************
*/

#include <reg52.h>
#include <model.h>

#if LessonNumber == Lesson_7_1 //��������ܼ�ʱ����ľ�̬������ʾ
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code LedChar[] = {	//�������ʾ�ַ�ת����
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};
unsigned char LedBuff[6] = {	//�������ʾ����������ֵ0xFFȷ������ʱ������
  	0xFF, 0xFF,	0xFF, 0xFF,	0xFF, 0xFF,
};
unsigned char flag1s = 0;	//1�붨ʱ��־

void main()
{
	unsigned long sec = 0;	//��¼����������
	
	EA = 1;			//ʹ�����ж�
	ENLED = 0;	   	//ʹ��U3��ѡ����������
	ADDR3 = 1;	   	//��Ϊ��Ҫ��̬�ı�ADDR0-2��ֵ�����Բ���Ҫ�ٳ�ʼ����
	TMOD = 0x01;   	//����T0Ϊģʽ1
	TH0 = 0xFC;	   	//ΪT0����ֵ0xFC67����ʱ1ms
	TL0 = 0x67;
	TR0 = 1;	   	//ʹ��T0�ж�
	ET0 = 1;	   	//����T0

	while(1)
	{
		if (flag1s == 1)	//�ж�1�붨ʱ��־
		{
			flag1s = 0;		//1�붨ʱ��־����
			sec++;		 	//������Լ�1
			//���´��뽫sec��ʮ����λ�ӵ͵���������ȡ��תΪ�������ʾ�ַ�
			LedBuff[0] = LedChar[sec%10];
			LedBuff[1] = LedChar[sec/10%10];
			LedBuff[2] = LedChar[sec/100%10];
			LedBuff[3] = LedChar[sec/1000%10];
			LedBuff[4] = LedChar[sec/10000%10];
			LedBuff[5] = LedChar[sec/100000%10];
		}
	}
}

/* ��ʱ��0�жϷ����� */
void InterruptTime0() interrupt 1
{
	static unsigned char i = 0;	 //��̬ɨ�������������Ϊ�ֲ���̬����
	static unsigned int cnt = 0; //��¼T0�жϴ���������Ϊ�ֲ���̬����
	
	TH0 = 0xFC;	//���¼��س�ֵ
	TL0 = 0x67;
	cnt++;	   	//�жϴ�������ֵ��1

	if (cnt >= 1000)	//�ж�1000�μ�1��
	{
		cnt = 0;	  	//�������ֵ�����¿�ʼ��1���ʱ
		flag1s = 1;	  	//����1�붨ʱ��־Ϊ1
	}

	//���´����������ܶ�̬ɨ��ˢ��
	P0 = 0xFF;	//��ʾ����
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

#elif LessonNumber == Lesson_7_2 //����LED�����ϵ�һ����
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;
sbit LED = P0^0;

void main()
{
	ENLED = 0;	//U3��U4��Ƭ74HC138��ʹ��
	ADDR3 = 0;	//ʹ��U4ʹ֮�������
	ADDR2 = 0;	//��U4��Y1�������������Q11
	ADDR1 = 0;
	ADDR0 = 0;

	LED = 0;	//��P0.0д��0���������Ͻǵ�һ����
	while(1);	//����ֹͣ������
}

#elif LessonNumber == Lesson_7_3 //����LED������һ��
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void main()
{
	ENLED = 0;	//U3��U4��Ƭ74HC138��ʹ��
	ADDR3 = 0;	//ʹ��U4ʹ֮�������
	ADDR2 = 0;	//��U4��Y1�������������Q11
	ADDR1 = 0;
	ADDR0 = 0;

	P0 = 0x00;	//��P0д��0������һ��
	while(1);	//����ֹͣ������
}

#elif LessonNumber == Lesson_7_4 //����LED�����ϵ�ȫ����
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void main()
{
	EA = 1;			//ʹ�����ж�
	ENLED = 0;		//ʹ��U4��ѡ��LED����
	ADDR3 = 0;		//��Ϊ��Ҫ��̬�ı�ADDR0-2��ֵ�����Բ���Ҫ�ٳ�ʼ����
	TMOD = 0x01;	//����T0Ϊģʽ1
	TH0 = 0xFC;		//ΪT0����ֵ0xFC67����ʱ1ms
	TL0 = 0x67;
	TR0 = 1;		//����T0
	ET0 = 1;		//ʹ��T0�ж�

	while(1);		//����ͣ������ȴ���ʱ���ж�
}
/* ��ʱ��0�жϷ����� */
void InterruptTime0() interrupt 1
{
	static unsigned char i = 0;	//��̬ɨ�������

	TH0 = 0xFC;	//���¼��س�ֵ
	TL0 = 0x67;
    //���´������LED����̬ɨ��ˢ��
	P0 = 0xFF;	//��ʾ����
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

#elif LessonNumber == Lesson_7_5 //LED������ʾ��̬ͼ��
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code Heart[] = {	//"��"��ͼƬ����ģ��
	0xFF,0x99,0x00,0x00,0x00,0x81,0xC3,0xE7,
};

void main()
{
	EA = 1;			//ʹ�����ж�
	ENLED = 0;		//ʹ��U4��ѡ��LED����
	ADDR3 = 0;
	TMOD = 0x01;	//����T0Ϊģʽ1
	TH0 = 0xFC;		//ΪT0����ֵ0xFC67����ʱ1ms
	TL0 = 0x67;
	TR0 = 1;		//����T0
	ET0 = 1;		//ʹ��T0�ж�

	while(1);
}
/* ��ʱ��0�жϷ����� */
void InterruptTime0() interrupt 1
{
	static unsigned char i = 0;	//��̬ɨ�������

	TH0 = 0xFC;	//���¼��س�ֵ
	TL0 = 0x67;
	//���´������LED����̬ɨ��ˢ��
	P0 = 0xFF;	//��ʾ����
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

#elif LessonNumber == Lesson_7_6 //LED������ʾ�����ƶ��Ķ���
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code I_Love_You[] = {	//"I Love You"ͼƬ����ģ��
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xC3,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xC3,
	0xFF,0x99,0x00,0x00,0x00,0x81,0xC3,0xE7,
	0xFF,0x99,0x99,0x99,0x99,0x99,0x81,0xC3,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};

void main()
{
	EA = 1;			//ʹ�����ж�
	ENLED = 0;		//ʹ��U4��ѡ��LED����
	ADDR3 = 0;
	TMOD = 0x01;	//����T0Ϊģʽ1
	TH0 = 0xFC;		//ΪT0����ֵ0xFC67����ʱ1ms
	TL0 = 0x67;
	TR0 = 1;		//����T0
	ET0 = 1;		//ʹ��T0�ж�

	while(1);
}
/* ��ʱ��0�жϷ����� */
void InterruptTime0() interrupt 1
{
	static unsigned char i = 0;		//��̬ɨ�������
	static unsigned char tmr = 0;	//250ms�����ʱ��
	static unsigned char index = 0;	//ͼƬˢ������

	TH0 = 0xFC;	//���¼��س�ֵ
	TL0 = 0x67;
	tmr++;
	//���´������LED����̬ɨ��ˢ��
	P0 = 0xFF;	//��ʾ����
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
    //���´������ÿ250ms�ı�һ֡ͼ��
	if (tmr >= 250)	//�ﵽ250msʱ�ı�һ��ͼƬ����
	{
		tmr = 0;
		index++;
		if (index >= 32)	//ͼƬ�����ﵽ32�����
		{
			index = 0;
		}
	}
}

#elif LessonNumber == Lesson_7_6_h //LED������ʾ�����ƶ��Ķ���(��ת���ӷ����ȡ�ɷ�ʽ)
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code I_Love_You_hengxiang[] = {	//"I Love You"����ͼƬ����ģ��
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0x7D,0x01,0x01,0x7D,0xFF,0xFF,0xE3,0xC1,
	0x81,0x03,0x03,0x81,0xC1,0xE3,0xFF,0xFF,
	0x81,0x01,0x7F,0x7F,0x7F,0x01,0x81,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};

void main()
{
	EA = 1;			//ʹ�����ж�
	ENLED = 0;		//ʹ��U4��ѡ��LED����
	ADDR3 = 0;
	TMOD = 0x01;	//����T0Ϊģʽ1
	TH0 = 0xFC;		//ΪT0����ֵ0xFC67����ʱ1ms
	TL0 = 0x67;
	TR0 = 1;		//����T0
	ET0 = 1;		//ʹ��T0�ж�

	while(1);
}
/* ��ʱ��0�жϷ����� */
void InterruptTime0() interrupt 1
{
	static unsigned char i = 0;		//��̬ɨ�������
	static unsigned char tmr = 0;	//250ms�����ʱ��
	static unsigned char index = 0;	//ͼƬˢ������

	TH0 = 0xFC;	//���¼��س�ֵ
	TL0 = 0x67;
	tmr++;
	//���´������LED����̬ɨ��ˢ��
	P0 = 0xFF;	//��ʾ����
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
    //���´������ÿ250ms�ı�һ֡ͼ��
	if (tmr >= 250)	//�ﵽ250msʱ�ı�һ��ͼƬ����
	{
		tmr = 0;
		index++;
		if (index >= 32)	//ͼƬ�����ﵽ32�����
		{
			index = 0;
		}
	}
}

#elif LessonNumber == Lesson_7_7 //LED������ʾ�����ƶ��Ķ���
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code I_Love_You_hengxiang_30[30][8] = {	//"I Love You"����ͼƬ����ģ��
	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},	//����֡1
	{0xFF,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F},	//����֡2
	{0xFF,0x3F,0x7F,0x7F,0x7F,0x7F,0x7F,0x3F},	//����֡3
	{0xFF,0x1F,0x3F,0x3F,0x3F,0x3F,0x3F,0x1F},	//����֡4
	{0xFF,0x0F,0x9F,0x9F,0x9F,0x9F,0x9F,0x0F},	//����֡5
	{0xFF,0x87,0xCF,0xCF,0xCF,0xCF,0xCF,0x87},	//����֡6
	{0xFF,0xC3,0xE7,0xE7,0xE7,0xE7,0xE7,0xC3},	//����֡7
	{0xFF,0xE1,0x73,0x73,0x73,0xF3,0xF3,0xE1},	//����֡8
	{0xFF,0x70,0x39,0x39,0x39,0x79,0xF9,0xF0},	//����֡9
	{0xFF,0x38,0x1C,0x1C,0x1C,0x3C,0x7C,0xF8},	//����֡10
	{0xFF,0x9C,0x0E,0x0E,0x0E,0x1E,0x3E,0x7C},	//����֡11
	{0xFF,0xCE,0x07,0x07,0x07,0x0F,0x1F,0x3E},	//����֡12
	{0xFF,0x67,0x03,0x03,0x03,0x07,0x0F,0x9F},	//����֡13
	{0xFF,0x33,0x01,0x01,0x01,0x03,0x87,0xCF},	//����֡14
	{0xFF,0x99,0x00,0x00,0x00,0x81,0xC3,0xE7},	//����֡15
	{0xFF,0xCC,0x80,0x80,0x80,0xC0,0xE1,0xF3},	//����֡16
	{0xFF,0xE6,0xC0,0xC0,0xC0,0xE0,0xF0,0xF9},	//����֡17
	{0xFF,0x73,0x60,0x60,0x60,0x70,0x78,0xFC},	//����֡18
	{0xFF,0x39,0x30,0x30,0x30,0x38,0x3C,0x7E},	//����֡19
	{0xFF,0x9C,0x98,0x98,0x98,0x9C,0x1E,0x3F},	//����֡20
	{0xFF,0xCE,0xCC,0xCC,0xCC,0xCE,0x0F,0x1F},	//����֡21
	{0xFF,0x67,0x66,0x66,0x66,0x67,0x07,0x0F},	//����֡22
	{0xFF,0x33,0x33,0x33,0x33,0x33,0x03,0x87},	//����֡23
	{0xFF,0x99,0x99,0x99,0x99,0x99,0x81,0xC3},	//����֡24
	{0xFF,0xCC,0xCC,0xCC,0xCC,0xCC,0xC0,0xE1},	//����֡25
	{0xFF,0xE6,0xE6,0xE6,0xE6,0xE6,0xE0,0xF0},	//����֡26
	{0xFF,0xF3,0xF3,0xF3,0xF3,0xF3,0xF0,0xF8},	//����֡27
	{0xFF,0xF9,0xF9,0xF9,0xF9,0xF9,0xF8,0xFC},	//����֡28
	{0xFF,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFE},	//����֡29
	{0xFF,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFF},	//����֡30
};

void main()
{
	EA = 1;			//ʹ�����ж�
	ENLED = 0;		//ʹ��U4��ѡ��LED����
	ADDR3 = 0;
	TMOD = 0x01;	//����T0Ϊģʽ1
	TH0 = 0xFC;		//ΪT0����ֵ0xFC67����ʱ1ms
	TL0 = 0x67;
	TR0 = 1;		//����T0
	ET0 = 1;		//ʹ��T0�ж�

	while(1);
}
/* ��ʱ��0�жϷ����� */
void InterruptTime0() interrupt 1
{
	static unsigned char i = 0;		//��̬ɨ�������
	static unsigned char tmr = 0;	//250ms�����ʱ��
	static unsigned char index = 0;	//ͼƬˢ������

	TH0 = 0xFC;	//���¼��س�ֵ
	TL0 = 0x67;
	tmr++;
	//���´������LED����̬ɨ��ˢ��
	P0 = 0xFF;	//��ʾ����
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
    //���´������ÿ250ms�ı�һ֡ͼ��
	if (tmr >= 250)	//�ﵽ250msʱ�ı�һ��ͼƬ����
	{
		tmr = 0;
		index++;
		if (index >= 30)	//ͼƬ�����ﵽ30�����
		{
			index = 0;
		}
	}
}

#endif

