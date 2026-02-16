#ifndef MSL50228_H
#define MSL50228_H

#include "Arduino.h"

// Push buttons front
#define BUTT_UP	     10 // D,2
#define BUTT_DOWN    11 // D,3

/* PD4435 display */

#define PD44_CE1     22 // C,6
#define PD44_RST     34 // E,2
/* Note: reset is u sed to synchronize blinking. Will not
clear the display. The reset pulse should be
less than 1 ms*/

#define PD44_WR      14 // D,6
#define PD44_RD      15 // D,7

#define PD44_A0      16 // C,0
#define PD44_A1      17 // C,1
#define PD44_A2      18 // C,2

#define PD44_DATA PORTA

#define PD44_D0	     24 // A,0
#define PD44_D1      25 // A,1
#define PD44_D2      26 // A,2
#define PD44_D3      27 // A,3
#define PD44_D4      28 // A,4
#define PD44_D5      29 // A,5
#define PD44_D6      30 // A,6
#define PD44_D7      31 // A,7

/* Multiplexer address lines (SNx4HC138) -- see PD datasheet for
 * how this is used to break out to (here 6) displays.
 */
#define MPLEX_A      19 // C,3
#define MPLEX_B      20 // C,4
#define MPLEX_C      21 // C,5

#define NUMDISP 6*4		// there are 6 displays of 4 characters each, on 50228

class MSL50228
{
	public:
		MSL50228();
		void clear(void); 					/* clear full display */
		void setBrightness(char br); 		/* set brightness for full display, 0-3 with 3 brightest and 0 off. */
		void write(const char text[]); 		/* Write from start of display */
		void writeAt(unsigned char disp, const char text[]); /* write at display 0-5, max 4 chars*/
	private:
		unsigned char brightness;
		void sendCtrl(unsigned char cword);
		void _sendByte(unsigned char addr, unsigned char val);
		void sendChar(unsigned char addr, unsigned char val);
		void select(unsigned char n);		/* switch multiplexor to the display that is to be written*/
	};

#endif
