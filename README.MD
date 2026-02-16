### How to get this into arduino? ###
Download as .zip, then import zip library

### How to use? ###
Get the modified 'Majorcore' that supports the Atmega161. https://github.com/Lukelectro/MajorCore/tree/luke

Burn bootloader to 50228 board. Add 100nf between reset and the free pin above it on the boxheader. Connect USB-serial to RX,TX, GND. Connect DTR to the 100nF that is connected to reset.

Then with this library the 50228 board can be used as if it is an arduino.

### pinout and other details ###
See MakerSpace Wiki: https://wiki.makerspaceleiden.nl/mediawiki/index.php/Project_Radar_Boards_Schiphol_Control

