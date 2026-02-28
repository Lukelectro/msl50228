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

	DDRD &=~((1<<2)|(1<<3));// BUTT_UP and BUTT_DOWN inputs
	PORTD|=((1<<2)|(1<<3)); // BUTT_UP and BUTT_DOWN pull-ups
	DDRC |= 0x7F;			// set A0,A1,A2, multiplexer and CE1 pins to output 

	MAKE_OUTPUT(PD44_WR);
	MAKE_OUTPUT(PD44_RD);
	MAKE_LOW(PD44_RD);

	DDRA=0xFF; 				// porta output, it is the data port

	MAKE_OUTPUT(PD44_RST);
	MAKE_HIGH(PD44_RST);	

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
	MAKE_HIGH(PD44_CE1);
#endif
	MAKE_HIGH(PD44_RD);
	MAKE_HIGH(PD44_WR);

	//SET(PORTC,0,((addr >> 0) & 1)); // digitalWrite(PD44_A0, ((addr >> 0) & 1));
	//SET(PORTC,1,((addr >> 1) & 1)); // digitalWrite(PD44_A1, ((addr >> 1) & 1));
	//SET(PORTC,2,((addr >> 2) & 1)); // digitalWrite(PD44_A2, ((addr >> 2) & 1));
	PORTC = (PORTC & (~0x07)) | (addr&0x07); // set adress pins to adres value, same as above comments


    PD44_DATA = val;	//send data

	MAKE_LOW(PD44_WR);
	MAKE_HIGH(PD44_WR);

	MAKE_LOW(PD44_RD);
#ifdef PD44_CE1
	MAKE_LOW(PD44_CE1);
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
	writeFrom(0, str);
}

void MSL50228::writeFrom(unsigned char disp, const char * str) {
	int len = 0;
	for(const char * p = str; *p; len++, p++) {}; // strlen, basicly

	for(int d = disp; d < 6 && d*4 < len; d++) 
		writeAt(d, str + d * 4);
}
  
void MSL50228::option(unsigned char disp, options whichoption){
// OR the option with the brightness and write to the selected DISP. Options that apply to characters should have the character pre-marked by |0x80 before writing that char
	select(disp);
   	sendCtrl(whichoption|(brightness&3));
}

