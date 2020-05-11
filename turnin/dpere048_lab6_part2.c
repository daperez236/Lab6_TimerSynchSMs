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
unsigned char tmpC = 0x00;
unsigned char tmpA = 0x00;
enum States{begin, light1, pause, light2, pause2, light3, pause3}state;
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
			if(tmpA){
			state = pause;
			}
			else{
			state = light2;
			}
			break;
		case pause:
			if(tmpA){
			state = light1;
			}
			else{
			state = pause2;
			}
			break;
		case light2:
			if(tmpA){
			state = pause2;
			}
			else{
			state = light3;
			}
			break;
		case pause2:
			if(tmpA){
			state = light2
			}
			else{
			state pause2;
			}
		case light3:
			if(tmpA){
			state = pause3;
			}
			else{
			state = light1;
			}
			break;
		case pause3:
			if(tmpA){
			state = light3;
			}
			else{
			state = pause3;
			}
			break;
	}
	switch(state)
	{
		case light1:
			tmpC= 0x01;
			break;
		case pause:
			tmpC = 0X01;
			break;
		case light2:
			tmpC = 0x02;
			break;
		case pause2:
			tmpC = 0x02;
			break;
		case light3:
			tmpC = 0x04;
			break;	
		case pause3:
			tmpC = 0x04;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRC = 0xFF;
	PORTC = 0x00;
	
	TimerSet(300);
	TimerOn();
	unsigned char tmpB = 0x00;
	state = begin;
    /* Insert your solution below */

    while (1) {	
	tmpA = ~PINA&0x08;
	LightTick();
	while (!TimerFlag);
	TimerFlag = 0;
	PORTC = tmpC;
		
    }
    return 1;
}
