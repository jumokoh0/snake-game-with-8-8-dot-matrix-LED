/*
 * example1.c
 *
 * Created: 2018-11-11 오후 3:57:44
 *  Author: kimjaemin
 */ 
//먹이 만들기 성공
//단독이동 성공
//몸통저장 및 출력



#include <avr/io.h>
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>

char LED[10][10]={{0,0,0,0,0,0,0,0,0,0},{0,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00,0}, {0,0x27,0x26,0x25,0x24,0x23,0x22,0x21,0x20,0},{0,0x47,0x46,0x45,0x44,0x43,0x42,0x41,0x40,0}, {0,0x67,0x66,0x65,0x64,0x63,0x62,0x61,0x60,0},{0,0x87,0x86,0x85,0x84,0x83,0x82,0x81,0x80,0}, {0,0xA7,0xA6,0xA5,0xA4,0xA3,0xA2,0xA1,0xA0,0},{0,0xC7,0xC6,0xC5,0xC4,0xC3,0xC2,0xC1,0xC0,0}, {0,0xE7,0xE6,0xE5,0xE4,0xE3,0xE2,0xE1,0xE0,0},{0,0,0,0,0,0,0,0,0,0}};
char Bulb[8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
char body[64]={0,};
	
char t1o0[16] = {6,5,14.24,34,44,54,64,75,76,67,57,47,37,27,17};
char t1o1[8] = {6,16,26,36,46,56,66,76};
char t1o2[14] =	{24,14,5,6,17,27,37,46,55,64,74,75,76,77};
char t1o3[14] =	{14,5,6,17,27,36,35,45,46,57,67,76,75,64};
char t1o4[15] = {57,56,55,54,44,34,25,15,6,16,26,36,46,66,76};
char t1o5[15] = {7,6,5,4,14,24,34,35,36,47,57,67,76,75,64};
char t1o6[20] = {17,7,6,5,4,14,24,34,44,54,64,74,75,76,77,67,57,47,46,45};
char t1o7[14] = {34,24,14,4,5,6,7,17,27,37,47,57,67,77};
char t1o8[24] =	{4,14,24,34,44,54,64,74,75,76,77,67,57,47,46,45,35,36,37,27,17,7,6,5};
char t1o9[19] =	{74,75,76,77,67,57,47,37,27,17,7,6,5,4,14,24,34,35,36};	
char t2o0[16] = {2,1,10.20,30,40,50,60,71,72,63,53,43,33,23,13};
char t2o1[8] = {2,12,22,32,42,52,62,72};
char t2o2[14] =	{20,10,1,2,13,23,33,42,51,60,70,71,72,73};
char t2o3[14] =	{10,1,2,13,23,32,31,41,42,53,63,72,71,60};
char t2o4[15] = {53,52,51,50,40,30,21,11,2,12,22,32,42,62,72};
char t2o5[15] = {3,2,1,0,10,20,30,31,32,43,53,63,72,71,60};
char t2o6[20] = {13,3,2,1,0,10,20,30,40,50,60,70,71,72,73,63,53,43,42,41};
char t2o7[14] = {30,20,10,0,1,2,3,13,23,33,43,53,63,73};
char t2o8[24] =	{0,10,20,30,40,50,60,70,71,72,73,63,53,43,42,41,31,32,33,23,13,3,2,1};
char t2o9[19] =	{70,71,72,73,63,53,43,33,23,13,3,2,1,0,10,20,30,31,32};
char s_smile[12] = {30,21,32,35,26,37,61,72,73.74,75,66};
char s_oh[15] = {0,7,11,16,22,25,31,36,40,47,61,72,63,74,65};
char s_haha[31] = {1,2,3,4,5,6,12,15,21,22,23,24,25,26,30,31,32,33,34,35,36,37,43,52,54,62,63,64,72,73,74};

volatile int Bulbcounter=0;
volatile int w=3;
volatile int h=3;
volatile int dh=0;
volatile int dw=0;
volatile int ready=0;
volatile int move_counter=0;
volatile int fh,fw;
volatile int direction=-1;
volatile int pressnum=0;
volatile int length=1;
volatile int eat=0;
volatile int gameover=0;
volatile int speed=4000;
volatile int nowscore=0;
volatile int bestscore=0;

void move(void);
void makefood(void);
void eatcheck(void);
void gameovercheck(void);
void set(void);
void stay(void);
void score(void);
void clean(void);
void led_num(int t, int o);
void result(void);
void smile(void);
void haha(void);
void oh(void);


ISR(TIMER0_OVF_vect)
{
	int a=Bulbcounter/8;
	int b=Bulbcounter-a*8;
	if(PIND==0b00000001)
	{
		dw=0;
		dh=-1;
		ready = 1;
		pressnum++;
	}
	else{}
	if(PIND==0b00000010)
	{
		dw=-1;
		dh=0;
		ready = 1;
		pressnum++;
	}
	else{}
	if(PIND==0b00000100)
	{
		dw=1;
		dh=0;
		ready = 1;
		pressnum++;
	}
	else{}
	if(PIND==0b00001000)
	{
		dw=0;
		dh=1;
		ready = 1;
		pressnum++;
	}
	else{}
	if(Bulb[a][b] == 0)
	{}
	else
	{
		PORTF=LED[a+1][b+1];
	}	
	if(Bulbcounter<64)
	{
		Bulbcounter++;
	}
	else
	{
		Bulbcounter = 0;
	}
	if(!gameover)
	{
		if(move_counter<speed)
		{
			move_counter++;
		}
		else
		{
			move();
			eatcheck();
			move_counter=0;
		}
	}
	else{}
	
}

/*
ISR(INT0_vect) //UP
{
	dw=0;
	dh=-1;
	ready = 1;
	pressnum++;
	era0++;
}

ISR(INT1_vect) //LEFT
{
	dw=-1;
	dh=0;
	ready = 1;
	pressnum++;
}

ISR(INT2_vect) //RIGHT
{
	dw=1;
	dh=0;
	ready = 1;
	pressnum++;
}


ISR(INT3_vect) //DOWN
{
	dw=0;
	dh=1;
	ready = 1;
	pressnum++;
}

*/


int main(void)
{
	cli();
	DDRF =0xFF; 
	DDRD =0x00;
	TCCR0 = 0x02;
	TIMSK = 0x01;
	//EICRA = 0b10101010; //상승에지 트리거
	//EIMSK = 0x0F; //외부 인터럽트 요청 INT0~INT3
	sei();
	while(1)
	{
		set();
		makefood();
		stay();
		while(!gameover)
		{}
		clean();
		score();
		ready=0;
		stay();
		clean();
		result();
		ready=0;
		stay();
		clean();
	}
}


void move(void)
{
	int i;
	if(length==1)
	{
		Bulb[h-1][w-1]=0;
	}
	else
	{
		if(eat==1)
		{
			eat=0;
		}	
		else
		{	
			int a=body[length-1]/10;
			int b=body[length-1]-a*10;
			Bulb[a-1][b-1]=0;
		}
	}
	h=h+dh;
	w=w+dw;
	if(h == 0)	//위쪽 벽을 넘을 시 반대편에서 나옴
		h=8;
	else{}
	if(w == 0)	//왼쪽 벽을 넘을 시 반대편에서 나옴
		w=8;
	else{}
	if(w == 9)	//오른쪽 벽을 넘을 시 반대편에서 나옴
		w=1;
	else{}
	if(h == 9)	//아래쪽 벽을 넘을 시 반대편에서 나옴
		h=1;
	else{}
	if(eat==1)
	{}
	else	
		Bulb[h-1][w-1]=1;
	gameovercheck();
	for(i=length-1;i>0;i--)
	{
		body[i]=body[i-1];
	}
	body[0]=h*10+w;
}


void makefood(void)
{
	int same=0;
	while(!same)
	{
		srand(move_counter+pressnum+1);       //나중에 카운터로 변경
		fh=rand()%8+1;
		fw=rand()%8+1;
		if(Bulb[fh-1][fw-1]==1 || (fh-1==0 && fw-1==7) || (fh-1==2 && fw-1==4))
		{
			srand(move_counter*pressnum-1+fh);       //나중에 카운터로 변경
			fh=rand()%8+1;
			fw=rand()%8+1;
			same=0;
		}
		else
		{
			same=1;
			Bulb[fh-1][fw-1]=1;
		}
	}
}

void eatcheck(void)
{
	if(h==fh && w==fw)
	{
		length++;
		eat=1;
		speed=speed-45;
		makefood();
	}
	else
	{}
}

void gameovercheck(void)
{
	int i;
	if((h-1==0 && w-1==7) || (h-1==2 && w-1==4))
	{
		gameover=1;
	}
	for(i=1;i<length;i++)
	{
		if(body[0]==body[i])
		{
			gameover=1;
		}
		else
		{}
	}
}

void set(void)
{
	cli();
	Bulbcounter=0;
	w=3;
	h=3;
	dh=0;
	dw=0;
	ready=0;
	move_counter=0;
	pressnum=0;
	length=1;
	eat=0;
	gameover=0;
	speed=4000;
	sei();
}

void stay(void)
{
	while(!ready)
	{}
	ready=0;
}

void clean(void)
{
	int clean_end=0;
	int i=0;
	while(!clean_end)
	{
		int a=i/8;
		int b=i-a*8;
		if(Bulb[a][b] == 0)
		{}
		else
			Bulb[a][b]=0;
		if(i<64)
			i++;
		else
		{
			clean_end=1;
			i=0;
		}
	}
}

void score(void)
{
	cli();
	int two_num=(length-1)/10;
	int one_num=(length-1)-two_num*10;
	led_num(2,two_num);
	led_num(1,one_num);
	sei();
}

void led_num(int t, int o)
{
	cli();
	int a=0;
	int b=0;
	int i;
	if(t==1 && o==0)   //일의 자리 0
	{
		for(i=0;i<16;i++)
		{
			a=t1o0[i]/10;
			b=t1o0[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==1 && o==1)   
	{
		for(i=0;i<8;i++)
		{
			a=t1o1[i]/10;
			b=t1o1[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==1 && o==2)   
	{
		for(i=0;i<14;i++)
		{
			a=t1o2[i]/10;
			b=t1o2[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==1 && o==3)  
	{
		for(i=0;i<14;i++)
		{
			a=t1o3[i]/10;
			b=t1o3[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==1 && o==4) 
	{
		for(i=0;i<15;i++)
		{
			a=t1o4[i]/10;
			b=t1o4[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==1 && o==5)  
	{
		for(i=0;i<15;i++)
		{
			a=t1o5[i]/10;
			b=t1o5[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==1 && o==6)  
	{
		for(i=0;i<20;i++)
		{
			a=t1o6[i]/10;
			b=t1o6[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==1 && o==7)   
	{
		for(i=0;i<14;i++)
		{
			a=t1o7[i]/10;
			b=t1o7[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==1 && o==8)  
	{
		for(i=0;i<24;i++)
		{
			a=t1o8[i]/10;
			b=t1o8[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==1 && o==9)   
	{
		for(i=0;i<19;i++)
		{
			a=t1o9[i]/10;
			b=t1o9[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==2 && o==0)   //이의 자리 0
	{
		for(i=0;i<16;i++)
		{
			a=t2o0[i]/10;
			b=t2o0[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==2 && o==1)
	{
		for(i=0;i<8;i++)
		{
			a=t2o1[i]/10;
			b=t2o1[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==2 && o==2)
	{
		for(i=0;i<14;i++)
		{
			a=t2o2[i]/10;
			b=t2o2[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==2 && o==3)
	{
		for(i=0;i<14;i++)
		{
			a=t2o3[i]/10;
			b=t2o3[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==2 && o==4)
	{
		for(i=0;i<15;i++)
		{
			a=t2o4[i]/10;
			b=t2o4[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==2 && o==5)
	{
		for(i=0;i<15;i++)
		{
			a=t2o5[i]/10;
			b=t2o5[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==2 && o==6)
	{
		for(i=0;i<20;i++)
		{
			a=t2o6[i]/10;
			b=t2o6[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==2 && o==7)
	{
		for(i=0;i<14;i++)
		{
			a=t2o7[i]/10;
			b=t2o7[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==2 && o==8)
	{
		for(i=0;i<24;i++)
		{
			a=t2o8[i]/10;
			b=t2o8[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	if(t==2 && o==9)
	{
		for(i=0;i<19;i++)
		{
			a=t2o9[i]/10;
			b=t2o9[i]-a*10;
			Bulb[a][b]=1;
		}
	}
	else{}
	sei();
}

void result(void)
{
	cli();
	nowscore=length-1;
	if(nowscore>bestscore)
	{
		smile();
	}
	else{}
	if(nowscore==61)
	{
		oh();
	}
	else{}
	if(nowscore<=bestscore)
	{
		haha();
	}
	sei();
}

void smile(void)
{
	cli();
	int i;
	int a=0;
	int b=0;
	for(i=0;i<12;i++)
	{
		a=s_smile[i]/10;
		b=s_smile[i]-a*10;
		Bulb[a][b]=1;
	}
	sei();
}

void oh(void)
{
	cli();
	int i;
	int a=0;
	int b=0;
	for(i=0;i<15;i++)
	{
		a=s_oh[i]/10;
		b=s_oh[i]-a*10;
		Bulb[a][b]=1;
	}
	sei();
}

void haha(void)
{
	cli();
	int i;
	int a=0;
	int b=0;
	for(i=0;i<31;i++)
	{
		a=s_haha[i]/10;
		b=s_haha[i]-a*10;
		Bulb[a][b]=1;
	}
	sei();
}