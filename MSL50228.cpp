/* 
 *	MSL50228 - Library for 50228 display assembly 
 * 	Created by Lucas Volwater, Februari 2026 
 * 
 */


#include "Arduino.h"
#include "MSL50228.h"

/* Pins of displays are always these pins on this board, so no need to pass pins to the constructor. */
MSL50228::MSL50228()
{
	brightness = 3; // default to max brightness

	DDRC |= 0x38; // set multiplexer pins to output 

    pinMode(BUTT_DOWN, INPUT_PULLUP);
	pinMode(BUTT_UP, INPUT_PULLUP);

	/*pd44 init */
	pinMode(PD44_WR, OUTPUT);
	#ifdef PD44_CE1
	pinMode(PD44_CE1, OUTPUT);
	#endif
	
	pinMode(PD44_RD, OUTPUT);
	digitalWrite(PD44_RD, LOW);

	pinMode(PD44_A2, OUTPUT);
	pinMode(PD44_A1, OUTPUT);
	pinMode(PD44_A0, OUTPUT);

	DDRA=0xFF; // porta output, it is the data port

	pinMode(PD44_RST, OUTPUT);
	digitalWrite(PD44_RST, HIGH);

	/*after init, clear and set brightness */
	clear();
  	setBrightness(brightness);	 
}
	
void MSL50228::select(unsigned char c) {
	PORTC = (PORTC & ~((1<<3) + (1<<4) + (1<<5))) | ((c & 0x7) << 3);
  }

void MSL50228::sendCtrl(unsigned char cword){
	_sendByte(0, cword);
}

void MSL50228::sendChar(unsigned char adr, unsigned char cword){
	_sendByte(adr|4, cword);
}

void MSL50228::clear(void){
	for(int d = 0; d < 6; d++) {
		select(d);
		sendCtrl(0x80);
		sendCtrl(brightness); // restore brightness after clear.
	}
}


void MSL50228::_sendByte(unsigned char addr, unsigned char val) {
#ifdef PD44_CE1
	digitalWrite(PD44_CE1,HIGH);
#endif
	digitalWrite(PD44_RD, HIGH);
	digitalWrite(PD44_WR, HIGH);

	digitalWrite(PD44_A0, ((addr >> 0) & 1));
	digitalWrite(PD44_A1, ((addr >> 1) & 1));
	digitalWrite(PD44_A2, ((addr >> 2) & 1));

    PD44_DATA = val;

	digitalWrite(PD44_WR, LOW);
	digitalWrite(PD44_WR, HIGH);

	digitalWrite(PD44_RD, LOW);
#ifdef PD44_CE1
	digitalWrite(PD44_CE1, LOW);
#endif
}

void MSL50228::setBrightness (char br){
brightness = br&0x3;
  for(char i=0;i<6;i++){
		select(i);
    	sendCtrl(brightness);
  }
  }

void MSL50228::writeAt(unsigned char display, const char* tekst) {
	select(display);
    for(int i = 0; i < 4; i++) {
		char c = *tekst;
		if (c) tekst++;
		if (!c) c = ' ';
		sendChar((3-i),c);
	};
}
void MSL50228::write(const char * str) {
	int len = 0;
	for(const char * p = str; *p; len++, p++) {}; // strlen, basicly

	for(int d = 0; d < 6 && d*4 < len; d++) 
		writeAt(d, str + d * 4);
}


  

