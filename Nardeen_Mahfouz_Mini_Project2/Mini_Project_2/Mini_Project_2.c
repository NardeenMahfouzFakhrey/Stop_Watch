/*
 * Mini_Project_2.c
 *
 *  Created on: 19 Sept 2022
 *      Author: Nardeen
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


unsigned char seconds=0,sec1=0,sec2=0;
unsigned char minutes=0 ,min1=0,min2=0;;
unsigned char hours=0,hour1=0,hour2=0;


void Numbers (void){
	sec1=seconds%10;
	sec2=(seconds/10 )%10;

	min1=minutes%10;

		min2= (minutes/10)%10;

	hour1=hours%10;

	 hour2=(hours/10)%10;
}

ISR(INT0_vect){
	seconds=0;
    minutes=0;
     hours=0;
}
ISR(INT1_vect){
	TCCR1B &= ~(1<<CS12) &~ (1<<CS10);
}
ISR(INT2_vect){
	TCCR1B |=(1<<CS12) | (1<<CS10);
}

ISR(TIMER1_COMPA_vect){

	seconds++;

	if(seconds==60){

		minutes++;
		seconds=0;

	}
	if (minutes ==60){

		hours++;
		minutes=0;
	}
	if(hours==24){
		hours=0;
	}

}

void Timer1_Init(void){

	TCNT1=0;
	TCCR1A =(1<< FOC1A);
	TCCR1B =(1<<WGM12) | (1<<CS12) | (1<<CS10);
	OCR1A=1000; // count till 1000;
	TIMSK |= (1<<OCIE1A); //Enable interrupt
	//global interrupt

}

void Int0_Init(void){

	MCUCR|=(1<<ISC01);
	GICR|=(1<<INT0);

}
void Int1_Init(void){

	MCUCR|=(1<< ISC11)|(1<<ISC10);
	GICR|=(1<<INT1);

}
void Int2_Init(void){

	GICR|=(1<<INT2);

}
void GPIO_Init(void){
	DDRD  &= (~(1<<PD3)) &(~(1<<PD2)) ;
	DDRB  &= (~(1<<PB2));
	DDRC  |= (1<<PC0)| (1<<PC1) | (1<<PC2) | (1<<PC3);
	DDRA  |= (1<<PA0)| (1<<PA1) | (1<<PA2) | (1<<PA3) | (1<<PA4) | (1<<PA5) ;
}


int main(){
	GPIO_Init();
	Int2_Init();
	Int1_Init();
	Int0_Init();
	Timer1_Init();
	SREG  |= (1<<7);
	while(1){
      Numbers();
      PORTA =  0x01;
      PORTC = (PORTC & 0xF0)| sec1;
       _delay_ms(2);
      PORTA =  0x02;
      PORTC =  (PORTC& 0xF0)| sec2;
      _delay_ms(2);
      PORTA =  0x04;
      PORTC = (PORTC& 0xF0)| min1;
      _delay_ms(2);
      PORTA =  0x08;
      PORTC = (PORTC& 0xF0) | min2;
      _delay_ms(2);
      PORTA =  0x10;
      PORTC = (PORTC& 0xF0)| hour1;
      _delay_ms(2);
      PORTA =  0x20;
      PORTC = (PORTC& 0xF0)| hour2;
      _delay_ms(2);
	}
}
