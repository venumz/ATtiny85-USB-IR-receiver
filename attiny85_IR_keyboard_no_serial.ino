/* Attiny85 IR USB receiver by Venum.
*  
* I couldn't make this without the help of:
* David A. Mellis for his attiny core https://github.com/damellis/attiny)
* Rowdy Dog Software for their library TinyTuner https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/arduino-tiny/TinyTuner-0003.zip
* Rowdy Dog Software for their tiny bootloader https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/arduino-tiny/arduino-tiny-0150-0020.zip
* Rancidbacon (http://rancidbacon.com/) for his arduino port of the v-usb library (https://code.google.com/archive/p/vusb-for-arduino/downloads)
* seejaydee for his IR library for tiny cores found on the comments of the instructable https://www.instructables.com/id/Attiny-IR-library/ code on https://drive.google.com/open?id=0B_w9z88wnDtFNHlqYU5sWEZuV0U
*
* To add new key_codes, check out the pdf http://www.usb.org/developers/hidpage/Hut1_12v2.pdf and search for section "Keyboard/Keypad Page" page 53 and use the numbers
* in the column Usage ID (Dec) to associate your remote buttons to keyboard codes.
* Then edit the file UsbKeyboard.h and add new defines to those already existent
*/
#include "UsbKeyboard.h" // http://code.google.com/p/vusb-for-arduino/
#include "tiny_IRremote.h" // by seejaydee on https://www.instructables.com/id/Attiny-IR-library/ code on https://drive.google.com/open?id=0B_w9z88wnDtFNHlqYU5sWEZuV0U

#define RECV_PIN 1
IRrecv irrecv(RECV_PIN);
decode_results results;
int lastStroke=0;

void setup() {
 // uncommment the statement below if you use tinytuner to calibrate the internal clock
 // leave it commented if you use an external 16Mhz crystal
 //OSCCAL = 0x4B; // Oscillator callibration value from Tiny Tuner http://goo.gl/J71XN
 pinMode(RECV_PIN, INPUT);
 digitalWrite(RECV_PIN, HIGH);
 // Disable timer0 as it can interfere with USB timing 
 // millis and delay won't work with this timer down, but delayMicrosencods() will
 TIMSK&=!(1<<TOIE0); // Disabling timer0 
//TIMSK&=!(1<<TOIE1);   // Disable timer1

 // Clear interrupts while performing time-critical operations
cli(); 

// Force re-enumeration so the host will detect us
usbDeviceDisconnect();
delayMs(250);
usbDeviceConnect();
usbInit();
// Set interrupts again
sei();

 irrecv.enableIRIn(); // Start the receiver
}

void loop() {

UsbKeyboard.update(); // needs to be called at least once every 10 ms
// or the computer may think that the device
// has stopped working, and give driver errors 

   if (irrecv.decode(&results)) {
    irrecv.resume(); // Receive the next value

    // WARNING: THIS CODES ARE JUST EXAMPLES THAT WORK WITH MY REMOTE, YOU MAY NEED TO CHANGE THEM FOR YOURS.
   
    if(results.value==3429 || results.value==1381) { // Volume up -
    UsbKeyboard.sendKeyStroke(KEY_VOL_UP);
    } else if(results.value==3427 || results.value==1379) { // Volume down -
    UsbKeyboard.sendKeyStroke(KEY_VOL_DOWN);
    } else if(results.value==3406 || results.value==1358) { // arrow left
    if(lastStroke!=results.value) // we don't want for this button to hit twice
    UsbKeyboard.sendKeyStroke(KEY_ARROW_LEFT);
    } else if(results.value==3408 || results.value==1360) { // arrow right
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_ARROW_RIGHT);
    } else if(results.value==3405 || results.value==1357) { // arrow up
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_ARROW_UP);
    } else if(results.value==3409 || results.value==1361) { // arrow down
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_ARROW_DOWN);
    } else if(results.value==3416 || results.value==1368) { // mute
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_MUTE);
    } else if(results.value==3407 || results.value==1359) { // space
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_SPACE);
    } else if(results.value==3394 || results.value==1346) { // Full screen (f)
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_F);
    } else if(results.value==3451 || results.value==1403) { // Play
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_SPACE);
    } else if(results.value==3452 || results.value==1404) { // Stop
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_STOP);
    } else if(results.value==3455 || results.value==1407 || results.value==3430 || results.value==1382) { // Next
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_STOP);
    } else if(results.value==3453 || results.value==1405 || results.value==3428 || results.value==1380) { // Prev
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_NEXT);
    } else if(results.value==3404 || results.value==1356) { // 0
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_0);
    } else if(results.value==3395 || results.value==1347) { // 1
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_1);
    } else if(results.value==3396 || results.value==1348) { // 2
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_2);
    } else if(results.value==3397 || results.value==1349) { // 3
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_3);
    } else if(results.value==3398 || results.value==1350) { // 4
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_4);
    } else if(results.value==3399 || results.value==1351) { // 5
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_5);
    } else if(results.value==3400 || results.value==1352) { // 6
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_6);
    } else if(results.value==3401 || results.value==1353) { // 7
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_7);
    } else if(results.value==3402 || results.value==1354) { // 8
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_8);
    } else if(results.value==3403 || results.value==1355) { // 9
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_9);
    }
    lastStroke=results.value;
   }
}

void delayMs(unsigned int ms) {
  for( int i=0; i<ms; i++ ) {
    delayMicroseconds(1000);
}
}
