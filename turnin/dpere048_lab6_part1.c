/*	Author: dpere048
 *  Partner(s) Name: 
 *	Lab Section: 021
 *	Assignment: Lab #6  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned char tmpA = 0x00;
enum States{begin, light1, light2, light3}state;
void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125; 
	TIMSK1	 = 0x02; 
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}
void TimerOff() {
	TCCR1B = 0x00;
}
void TimerISR(){
	TimerFlag = 1;
}
ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0){
	TimerISR();
	_avr_timer_cntcurr = _avr_timer_M;
	}
}
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}
void LightTick(){
	switch(state)
	{
		case begin:
			state = light1;
			break;
		case light1:
			state = light2;
			break;
		case light2
			state = light3;
			break;
		case light3
			state = light1;
			break;
	}
	switch(state)
	{
		case light1:
			tmpB= 0x01;
			break;
		case light2:
			tmpB = 0x02;
			break;
		case light3:
			tmpB = 0x04;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(1000);
	TimerOn();
	unsigned char tmpB = 0x00;
	state = begin;
    /* Insert your solution below */

    while (1) {
	LightTick();
	while (!TimerFlag);
	TimerFlag = 0;
	PORTB = tmpB;
		
    }
    return 1;
}
