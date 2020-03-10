#include<reg52.h>

sbit LED = P0^0;
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void main()
{
	unsigned char cnt = 0;	//����һ��������������¼T0�������

	ENLED = 0;		//ʹ��U3��ѡ�����LED
	ADDR3 = 1;
	ADDR2 = 1;
	ADDR1 = 1;
	ADDR0 = 0;
	
	//x*12/11059200=0.02	x = 18432	65536 - x = 47104 = 0xB800
	TMOD = 0x01;	//����T0Ϊģʽ1
	TH0 = 0xB8;		//ΪT0����ֵ0xB800
	TL0 = 0x00;
	TR0 = 1;		//����T0

	while(1)
	{
		if( TF0 == 1 )			//�ж�T0�Ƿ����
		{
			TF0 = 0;			//T0����������жϱ�־
			TH0 = 0xB8;			//�����¸���ֵ
			TL0 = 0x00;
			cnt++;				//����ֵ�Լ�1
			if( cnt >= 50 )		//�ж�T0����Ƿ�ﵽ50��
			{
				cnt = 0;		//�ﵽ50�κ����ֵ����
				LED = ~LED;		//LEDȡ����0-->1��1-->0
			}
		}
	}
}