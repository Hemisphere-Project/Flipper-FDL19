
//////////////////////////////////////////
/////////////     LIBS     ///////////////
//////////////////////////////////////////

//MH ET LIVE ESP32 DEVKIT
#define FLIPPER_VERSION  0.1
#define DEBUGFLAG
// #define TESTFLAG

// DEBUG
#include "debug.h"

// MUSIC MAKER
#include <SPI.h>
#include <SD.h>
#include <Adafruit_VS1053.h>
// https://github.com/danclarke/Adafruit_VS1053_Library
// an update of the Adafruit VS1053 Library for ESP32 with Interrupt support
// (The original one crash because Library doesn't support interrupts for ESP32)
// Good LIB de danclarke from github mise à la place de celle d'adafruit dans documents/Arduino/libraries
// DON'T WORK IF PLACED OUTSIDE OF ARDUINO/LIBRARIES Official folder. WHY ?

// DMX
#include "src/ESPDMX/ESPDMX.h"

// SERVO
#include <ESP32Servo.h>
// DON'T WORK IF PLACED OUTSIDE OF ARDUINO/LIBRARIES Official folder. WHY ?

//////////////////////////////////////////
/////////////    GLOBAL    ///////////////
//////////////////////////////////////////

// PINS - Servo
#define SERVOPIN			12
// PINS - MUSIC MAKER
#define VS1053_RESET   -1     // VS1053 reset pin (not used!)
#define VS1053_CS      32     // VS1053 chip select pin (output)
#define VS1053_DCS     33     // VS1053 Data/command select pin (output)
#define CARDCS         14     // Card chip select pin
#define VS1053_DREQ    15     // VS1053 Data request, ideally an Interrupt pin
// TO USE WITH ESP32 DEVKIT, CONNECT THE SCK, MOSI & MISO PINS TO THE ESP TOO

// PINS - DMX
// TXD1 ESP PIN D3 <---> RXD SHIELD


// DMX
DMXESPSerial dmx;
// SERVO
Servo myservo;
// MUSIC MAKER
Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS);

// UTILS
int pos = 0;

// DMX Adresses
int BT_Adresses[ 7 ] = { 1, 2, 3, 4, 5, 6, 7 };
int BR_Adresses[ 2 ] = { 8, 9 };
int VWX_Adresses[ 5 ] = { 10, 11, 12, 13, 14};
int ABC_Adresses[ 8 ] = { 16, 17, 18, 19, 20, 21, 22, 23 };
int T_Adresses[ 8 ] = { 32, 35, 38, 41, 44, 47, 50, 53 };

// SOUND
int masterVol = 5;

unsigned long Tnow = 0;
unsigned long TstartTimeline = 0;
unsigned long timelineDuration = 370000;  // 6'10" = 370000

bool starting = true;
bool ABC_isPlaying, VWX_isPlaying, BR_isPlaying, BT_isPlaying, No_One_Plays, = false;

//////////////////////////////////////////
/////////////     SETUP    ///////////////
//////////////////////////////////////////


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
  musicPlayer.setVolume(masterVol,masterVol);
  // If DREQ is on an interrupt pin we can do background audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int


	// DMX
	dmx.init(128);

	//SERVO
	myservo.setPeriodHertz(50);
	myservo.attach(SERVOPIN, 1000, 2500); // REGLER MIN MAX

	// COM RPI
	pinMode(16, OUTPUT);
	digitalWrite(16,LOW);

}

//////////////////////////////////////////
/////////////     LOOP     ///////////////
//////////////////////////////////////////



void loop() {

	Tnow = millis();

	#ifdef TESTFLAG
		testAll();
		return;
	#endif

	// RELOOP
	if((starting==true)||(Tnow-TstartTimeline>timelineDuration)){
		LOG("RELOOP");
		TstartTimeline = millis();
		starting = false;
		VWX_restart();
		BT_restart();
		BR_restart();
		ABC_restart();
		T_restart();
	}

	// END - FADE OUT
	if(Tnow-TstartTimeline>360000){// 360000
		VWX_fadeout();
		ABC_fadeout();
		T_fadeout();
		BR_forceOff();
		BT_forceOff();
		dmx.update();
		return;
	}

	// NORMAL
	VWX_update();
	BR_update();
	ABC_update();
	T_update();
	MOTOR_update();
	rpi_Update();

	// if((Tnow-TstartTimeline>100)&&(Tnow-TstartTimeline<10000)){
	// 	BT_update(300,4000);
	// }
	if((Tnow-TstartTimeline>15000)&&(Tnow-TstartTimeline<249000)){
		BT_update(300,4000);
	}
	else if((Tnow-TstartTimeline>267000)&&(Tnow-TstartTimeline<342000)){
		BT_update(300,4000);
	}
	else if((Tnow-TstartTimeline>342000)&&(Tnow-TstartTimeline<360000)){
		BT_update(200,1000);
	}else{
		BT_forceOff();
	}


	dmx.update();


}
