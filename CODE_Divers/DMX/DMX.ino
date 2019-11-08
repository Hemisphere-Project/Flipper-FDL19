
// #include <ESPDMX.h> // https://github.com/Rickgg/ESP-Dmx
#include "src/ESPDMX.h" // To use the lib files located inside the sketch folder, not in the arduino default folder

//MH ET LIVE ESP32 DEVKIT

// DMX
DMXESPSerial dmx;

// TXD1 ESP ( = pin 29 (D3) ) <---connected--->  RXD SHIELD


void spot_ON(){
  for (size_t i = 1; i < 6; i++) {
    dmx.write(i, 1);
  }
  // dmx.write(1, 15);
  dmx.update();
}
void spot_OFF(){
  for (size_t i = 1; i < 6; i++) {
    dmx.write(i, 0);
  }
  // dmx.write(1, 0);
  dmx.update();
}


void setup() {

  //Serial.begin(115200);

  // DMX
  dmx.init(32); // initialization for first 32 addresses by default

}


void loop() {

  spot_ON();
  delay(500);
  spot_OFF();
  delay(500);

}
