/* extended example for TCC7003 display. Sends text and variables to the display */

#include "MSL50228.h"

MSL50228 leddisplay;                   
 
void setup() {

leddisplay.setBrightness(2);        /* set display brightness, 1 to 3*/
leddisplay.write("Hello");          /* Write from start of display */
leddisplay.writeAt(2, "Worl");
leddisplay.writeAt(3, "d!");   		/* Write display 3*/
delay(2000);
leddisplay.clear();                 /* clear the entire display. */

/* if you want to clear only part of the display, you can use writeAt to write spaces. 
 * For example to overwrite a previous reading or other higher number of which no digits should be left. 
 * non-overwritten text stays
 */
 
leddisplay.writeAt(5, "100");
leddisplay.write("bottles of beer:");
delay(1000);
leddisplay.writeAt(5,"99");  /* Oops! 990 bottles!*/
delay(1000);
leddisplay.writeAt(5, "OOPS!");
delay(1000);
leddisplay.writeAt(5,"99 ");  /* That's better!*/
delay(1000);
}

void loop() {
  static char brightness = 3;
  char strbuff[4];
  static unsigned int bottles=99;

  bottles--;
  itoa(bottles,strbuff,10);     /* convert number to string. */
  leddisplay.writeAt(5,"    "); /* clear part of the display */
  leddisplay.writeAt(5, strbuff);

  delay(500); /* setting brightness will be clucky due to this delay but hey it is just an example of how to write text and how to read the buttons...*/

  if (digitalRead(BUTT_DOWN)==0) {
    brightness--;
    delay(100);
  }
  if (digitalRead(BUTT_UP)==0) {
    brightness++;
    delay(100);
  }
  if (brightness > 3) brightness = 3;
  else if (brightness < 0) brightness = 0;
  leddisplay.setBrightness(brightness);

}
