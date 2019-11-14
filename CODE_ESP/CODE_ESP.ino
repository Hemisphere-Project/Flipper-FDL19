
//MH ET LIVE ESP32 DEVKIT

// MUSIC MAKER
#include <SPI.h>
#include <SD.h>
// #include "src/Adafruit_VS1053/Adafruit_VS1053.h" // https://github.com/danclarke/Adafruit_VS1053_Library
#include <Adafruit_VS1053.h> // Crash because Library doesn't support interrupts for ESP32
// Good LIB de danclarke sur github mise à la place de celle d'adafruit dans documents/Arduino/libraries car sinon marche Pas... WHAT THE FUCK ?

// DMX
#include "src/ESPDMX/ESPDMX.h"
// SERVO
#include <ESP32Servo.h>


// PINS - Servo
#define SERVOPIN			12
// PINS - DMX
// TXD1 ESP = D3 <---connected--->  RXD SHIELD
// PINS - MUSIC MAKER
#define VS1053_RESET   -1     // VS1053 reset pin (not used!)
#define VS1053_CS      32     // VS1053 chip select pin (output)
#define VS1053_DCS     33     // VS1053 Data/command select pin (output)
#define CARDCS         14     // Card chip select pin
#define VS1053_DREQ    15     // VS1053 Data request, ideally an Interrupt pin
// TO USE WITH ESP32 DEVKIT, CONNECT THE SCK, MOSI & MISO PINS TO THE ESP TOO



// DMX
DMXESPSerial dmx;
// SERVO
Servo myservo;
// MUSIC MAKER
Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS);

// UTILS
int pos = 0;





void setup() {

	Serial.begin(115200);

  // Wait for serial port to be opened, remove this line for 'standalone' operation
  while (!Serial) { delay(1); }
  delay(500);

  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);
  }
  Serial.println("SD OK!");

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20,20);
  musicPlayer.sineTest(0x44, 500);
  // If DREQ is on an interrupt pin we can do background audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int


	// DMX
	dmx.init(32);

	//SERVO
	myservo.setPeriodHertz(50);
	myservo.attach(SERVOPIN, 1000, 2500); // REGLER MIN MAX


}

void loop() {

	// for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
	// 	myservo.write(pos);    // tell servo to go to position in variable 'pos'
	// 	delay(15);             // waits 15ms for the servo to reach the position
	// }
	// for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
	// 	myservo.write(pos);    // tell servo to go to position in variable 'pos'
	// 	delay(15);             // waits 15ms for the servo to reach the position
	// }

	for (pos = 0; pos <= 40; pos += 3) { // goes from 0 degrees to 180 degrees
		myservo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(15);             // waits 15ms for the servo to reach the position
	}
	for (pos = 40; pos >= 0; pos -= 3) { // goes from 180 degrees to 0 degrees
		myservo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(15);             // waits 15ms for the servo to reach the position
	}

	// for (size_t i = 0; i < 100; i++) {
	// 	musicPlayer.startPlayingFile("/track004.mp3");
	// 	delay(100);
	// }

  musicPlayer.stopPlaying();
	delay(1000);
	musicPlayer.startPlayingFile("/track004.mp3");
	all_ON();
	delay(1000);

	musicPlayer.stopPlaying();
	delay(1000);
  musicPlayer.startPlayingFile("/track002.mp3");
	all_OFF();
	delay(1000);

}


void all_ON(){
  for (int adress = 1; adress < 6; adress++) { dmx.write(adress, 10); }
  dmx.update();
}
void all_OFF(){
  for (int adress = 1; adress < 6; adress++) { dmx.write(adress, 0); }
  dmx.update();
}
