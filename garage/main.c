/*
 * counter.c
 *
 * Created: 3/23/2022 8:21:56 PM
 * Author : john
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
volatile int min = 5;
volatile int max = 1;
volatile char num[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0xEF};


int main(void)
{
    //initialization
		DDRC |= 0xFF;
		DDRB |= 0xFF;
		DDRD &= ~(1<<2);
		DDRD &= ~(1<<3);
		DDRD |=  (1<<4);
		DDRD |=  (1<<5);
		EICRA |= (1<<ISC11);
		EICRA |= (1<<ISC01);
		EIMSK |= (1<<INT0);
		EIMSK |= (1<<INT1);
		sei();
		PORTC |= num[min];
		PORTB |= num[max];
		PORTD |= (1<<4);
    while (1) 
    {
		
    }
}

ISR(INT0_vect)
{
	if(min == 10){
		min = 0;
		max++;
	}
	if(min >= 5 && max >= 1){
		min = 5;
		max = 1;
		PORTD |= (1<<4);
	}
	else{
	PORTC &= 0x00;
	min++;
	
	PORTC |= num[min];
	if(min == 5 && max == 1){
		PORTD |= (1<<PIND4);
		PORTD &= ~(1<<PIND5);
	}
	else{
		PORTD &= ~(1<<PIND4);
		PORTD |= (1<<PIND5);
	}
	PORTB &= 0x00;
	PORTB |= num[max];

	}
	sei();
}

ISR(INT1_vect)
{
		if (max == 0 && min ==0)
		{
			min =0;
			PORTC |= num[min];
			max =0;
			PORTB |= num[max];
		}
		else{
	if(min == 0){
		min =10;
		max--;
	}
	
	min--;
	if(min <= 6 && max <= 1){
		PORTD &= ~(1<<PIND4);
		PORTD |= (1<<PIND5);
	}

	PORTC &= 0x00;
	PORTC |= num[min];
	PORTB &= 0x00;
	PORTB |= num[max];
		}
	sei();
}

