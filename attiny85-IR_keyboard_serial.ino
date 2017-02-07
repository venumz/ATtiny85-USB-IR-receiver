/* Attiny IR decoder by Venum.
 *  
* I couldn't make this without the help of:
* David A. Mellis for his attiny core https://github.com/damellis/attiny)
* Rowdy Dog Software for their library TinyTuner https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/arduino-tiny/TinyTuner-0003.zip
* Rowdy Dog Software for their tiny bootloader https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/arduino-tiny/arduino-tiny-0150-0020.zip
* Rancidbacon (http://rancidbacon.com/) for his arduino port of the v-usb library (https://code.google.com/archive/p/vusb-for-arduino/downloads)
* seejaydee for his IR library for tiny cores found on the comments of the instructable https://www.instructables.com/id/Attiny-IR-library/ code on https://drive.google.com/open?id=0B_w9z88wnDtFNHlqYU5sWEZuV0U

 * Use this sketck only for testing the keycodes with the cores from 
 * https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/arduino-tiny/arduino-tiny-0150-0020.zip
*/
#include "tiny_IRremote.h" // by seejaydee on https://www.instructables.com/id/Attiny-IR-library/ code on https://drive.google.com/open?id=0B_w9z88wnDtFNHlqYU5sWEZuV0U

#define RECV_PIN 1
IRrecv irrecv(RECV_PIN);
decode_results results;

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

 irrecv.enableIRIn(); // Start the receiver
 Serial.begin(9600);
 Serial.println("\nStarting IR receiver");
}

void loop() {

   if (irrecv.decode(&results)) {
    irrecv.resume(); // Receive the next value
   
   Serial.print("RECEIVED ");
   Serial.print(results.decode_name);
   Serial.print(" ");
   Serial.print(results.value, HEX);
   Serial.print(" ");
   Serial.println(results.value);
   }
}

void delayMs(unsigned int ms) {
  for( int i=0; i<ms; i++ ) {
    delayMicroseconds(1000);
    }
}
