/* example for 50228 display that shows cursor and blink options. A blinking cursor could for example be used when entering text */

#include "MSL50228.h"

MSL50228 leddisplay; /* make new instance */

char text[] = {"ThisCan alsobe  doneh   "};  /* Write from start of display. Layout of displays on PCB adds spaces where there are none in the text*/

void setup() {
  
  /* for characters that need options, set bit 7 (done by or-ing them with 0x80), to mark that character as the one that te option needs to be applied to. Multiple characters on a display can be marked, they then get the same option applied */
  text[1] |= 0x80; //the h in "this"
  text[2] |= 0x80; //the i in "this"
  text[20]|= 0x80; // the h in "here"
  text[15]|= 0x80; // the 2nd space after "be #"

  leddisplay.setBrightness(3);      /* set display brightness, 1 to 3 . NOTE: setting brightness also changes options to default nonblinking etc!*/
  
  leddisplay.write(text);

  leddisplay.option(2,BLINKDISP); // blink display 3 (also)
  
  //todo: for those also bit 7 on the char needs to be set, to select which char to blink
  leddisplay.option(0,BLINKCHAR); // blink char 3 on display 0 (the i in this)
  leddisplay.option(5,ALTERNATECHAR); // alternate between character and cusor on disp 4, char 0 (d in done)
  //leddisplay.option(3,CURSORCHAR); 	// cusor on display 3 char 3 (right after be)

}

void loop() {
 /* Note the display does the blinking etc. by itself. The CPU can do something usefull instead. Or in this example, just spin in a delay*/

  delay(5000);
  text[20]&=~0x80; 			// disable option on the h in "here"
  text[21] = 'e' | 0x80; 	// apply option to the fist e in "here"
  leddisplay.write(text); /* rewrite text with modified option markers */
  delay(600);
  text[21]&=~0x80; 
  text[22] = 'r' | 0x80; 
  leddisplay.write(text); /* rewrite text */
  delay(450);
  text[22]&=~0x80; 
  text[23] = 'e'| 0x80; 
  leddisplay.write(text); /* rewrite text */
  delay(500);
  text[23]&=~0x80; 
  leddisplay.write(text); /* rewrite text */
  delay(5000);
  /* erase the last bit of text again. So it restarts. Looks like someone is typing */
  text[21] = ' ';
  text[22] = ' ';
  text[23] = ' ';
  text[20]|=0x80; // option back to the first letter
}



