
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
// #include "src/Adafruit_VS1053/Adafruit_VS1053.h" // https://github.com/danclarke/Adafruit_VS1053_Library
#include <Adafruit_VS1053.h> // Crash because Library doesn't support interrupts for ESP32
// Good LIB de danclarke sur github mise à la place de celle d'adafruit dans documents/Arduino/libraries car sinon marche Pas... WHAT THE FUCK ?

// DMX
#include "src/ESPDMX/ESPDMX.h"
// SERVO
#include <ESP32Servo.h>

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
int ABC_Adresses[ 8 ] = { 13, 14, 15, 16, 17, 18, 19, 20 };
int VWX_Adresses[ 5 ] = { 32, 33, 34, 35, 36};
int T_Adresses[ 12 ] = {44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55};


unsigned long Tnow = 0;
unsigned long TstartTimeline = 0;
unsigned long timelineDuration = 370000;  // 6'10"

bool starting = true;
bool ABC_isPlaying, VWX_isPlaying, BR_isPlaying = false;

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
  musicPlayer.setVolume(30,30);
  // If DREQ is on an interrupt pin we can do background audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int


	// DMX
	dmx.init(128);

	//SERVO
	myservo.setPeriodHertz(50);
	myservo.attach(SERVOPIN, 1000, 2500); // REGLER MIN MAX

	// COM
	pinMode(16, OUTPUT);

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

	VWX_update();
	BR_update();
	ABC_update();
	T_update();
	// MOTOR_update();
	rpi_Update();

	// if((Tnow-TstartTimeline>100)&&(Tnow-TstartTimeline<449000)){
	// 	BT_update(300,400);
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
