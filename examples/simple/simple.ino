/* Simple example for 50228 display. Just shows "Hello World!" */

#include "MSL50228.h"

MSL50228 leddisplay; /* make new instance */

void setup() {

  leddisplay.setBrightness(3);      /* set display brightness, 1 to 3 */
  leddisplay.write("Hello World!"); /* Write from start of display */
}

void loop() {
  static char brightness = 3;
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

