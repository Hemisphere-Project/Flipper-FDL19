
// #include <ESPDMX.h> // https://github.com/Rickgg/ESP-Dmx
#include "src/ESPDMX.h" // To use the lib files located inside the sketch folder, not in the arduino default folder


// DMX
DMXESPSerial dmx;

// TXD1 ESP ( = pin 29 (D3) ) <---connected--->  RXD SHIELD


void spot_ON(){
  dmx.write(1, 55);
  dmx.update();
  //Serial.printf("DMX ON: 1 \n");
}
void spot_OFF(){
  dmx.write(1, 0);
  dmx.update();
  //Serial.printf("DMX OFF: 1 \n");
}


void setup() {

  //Serial.begin(115200);

  // DMX
  dmx.init(32); // initialization for first 32 addresses by default

}


void loop() {

  spot_ON();
  delay(1000);
  spot_OFF();
  delay(1000);

}
