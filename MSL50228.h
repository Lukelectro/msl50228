#ifndef MSL50228_H
#define MSL50228_H

#include "Arduino.h"

#define _SET(type,name,bit)          type ## name  |= _BV(bit)    
#define _CLEAR(type,name,bit)        type ## name  &= ~ _BV(bit)        
#define _TOGGLE(type,name,bit)       type ## name  ^= _BV(bit)    
#define _GET(type,name,bit)          ((type ## name >> bit) &  1)
#define _PUT(type,name,bit,value)    type ## name = ( type ## name & ( ~ _BV(bit)) ) | ( ( 1 & (unsigned char)value ) << bit )

// OUTPUT(pin) collides with arduino's definition, hence the make_ prefix
#define MAKE_OUTPUT(pin)    _SET(DDR,pin)    
#define MAKE_INPUT(pin)     _CLEAR(DDR,pin)    
#define MAKE_HIGH(pin)      _SET(PORT,pin)
#define MAKE_LOW(pin)       _CLEAR(PORT,pin)    
#define SET(pin,value)      _PUT(PORT,pin,value)
#define TOGGLE(pin)         _TOGGLE(PORT,pin)    
#define READ(pin)           _GET(PIN,pin)

/* PD4435 display */

#define PD44_CE1  C,6
#define PD44_RST  E,2

#define PD44_WR   D,6
#define PD44_RD   D,7

#define PD44_A0   C,0
#define PD44_A1   C,1
#define PD44_A2   C,2

#define PD44_DATA PORTA

#define PD44_D0   A,0
#define PD44_D1   A,1
#define PD44_D2   A,2
#define PD44_D3   A,3
#define PD44_D4   A,4
#define PD44_D5   A,5
#define PD44_D6   A,6
#define PD44_D7   A,7

/* Multiplexer address lines (SNx4HC138) -- see PD datasheet for
 * how this is used to break out to (here 6) displays.
 */
#define MPLEX_A      C,3 
#define MPLEX_B      C,4 
#define MPLEX_C      C,5 

// Push buttons front
#define BUTT_UP	     D,2
#define BUTT_DOWN    D,3

//pushbuttons, majorcore compatible arduino pin numbering:
#define B_UP	PIN_PD2 
#define B_DOWN	PIN_PD3


#define NUMDISP 6*4		// there are 6 displays of 4 characters each, on 50228

enum options {BLINKDISP=0x20, LAMPTESTDISP=0x40, CURSORCHAR=0x10, ALTERNATECHAR=0x1C, BLINKCHAR=0x14, BLINKCURSOR=0x18}; /* available options. For the char options, write the char with its 7th bit set for example ('A'|0x80'), so that character gets selected for the extra option */

class MSL50228
{	
	public:
		MSL50228();
		void clear(void); 					/* clear full display */
		void setBrightness(char br); 		/* set brightness for full display, 0-3 with 3 brightest and 0 off. */
		void write(const char text[]); 		/* Write from start of display */
		void writeAt(unsigned char disp, const char text[]); /* write at display 0-5, max 4 chars*/
		void writeFrom(unsigned char disp, const char text[]); /* write from display 0-5, for the remaining characters*/
		void option(unsigned char disp, enum options whichoption); /* apply option to selected display. Options that aply to a character need that character marked first by having its 7th bit set */
	private:
		unsigned char brightness;
		void sendCtrl(unsigned char cword);
		void _sendByte(unsigned char addr, unsigned char val);
		void sendChar(unsigned char addr, unsigned char val);
		void select(unsigned char n);		/* switch multiplexor to the display that is to be written*/
	};

#endif
