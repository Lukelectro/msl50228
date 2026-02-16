/* Scrolling text example for 50228 display */

#include "MSL50228.h"

MSL50228 leddisplay;                         /* make new instance */

 
void setup() {

leddisplay.setBrightness(3);        /* set display brightness, 1 to 3 */

}

void loop() {

  const char text[] = "Hello World on \"50228\" board from Arduino with modified MajorCore for Atmega161                 Be excellent to each other & try to not to be on fire.                 This is a library example, the 50228 board can now be used with Arduino like it is an arduino! ";
  static unsigned int i = 0;
  static char brightness = 3;

  leddisplay.write(&text[i%strlen(text)]);
  delay(200);
  i++;

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

