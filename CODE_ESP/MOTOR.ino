
// Backtrace: 0x400f3472:0x3ffbc040 0x400de9d3:0x3ffbc060 0x40087136:0x3ffbc080 0x40085289:0x3ffbc0a0
// Backtrace: 0x400f34b2:0x3ffbc040 0x400dea13:0x3ffbc060 0x40087136:0x3ffbc080 0x40085289:0x3ffbc0a0

// /Users/ficeto/Desktop/ESP32/ESP32/esp-idf-public/components/newlib/locks.c:113 (_lock_close)- assert failed!
// abort() was called at PC 0x4008169f on core 1
// Backtrace: 0x40089020:0x3ffb1e40 0x4008924d:0x3ffb1e60 0x4008169f:0x3ffb1e80 0x4000be0d:0x3ffb1ea0 0x4000209c:0x3ffb1ec0 0x400020b5:0x3ffb1ee0 0x400d2bf1:0x3ffb1f00 0x400d2b61:0x3ffb1f20 0x400d384e:0x3ffb1f50 0x400d1695:0x3ffb1f70 0x400d1794:0x3ffb1f90 0x400d66a9:0x3ffb1fb0 0x40085289:0x3ffb1fd0


// AU BOUT DE 5 MINUTES ENVIRON, BLOQUE TOUT


//////////////////////////////////////////
////////////      MOTOR      /////////////
//////////////////////////////////////////

class MOTOR
{
  String sens = "up";
  bool is_on = false;
  bool playSound = false;
  int numberOfMovements = 0;
  int step = 0;
  unsigned long TlastAction, TlastStep;
  //Movement
  int posIncrement = 4;
  int stepLength = 10;
  int posDestination = 40;
	//Timing
  int period = 7000;

  // Constructor
  public:
  MOTOR(){
		TlastAction = 0;
    TlastStep = 0;
  }


  void update(){

    if(Tnow-TlastAction>period){

      if(is_on==false){
        is_on=true;
        playSound = true;
        step = 0;
        sens="up";
        numberOfMovements = random(1,3);
      }
      if(playSound==true){
        playSound = false;
        if((VWX_isPlaying==false)&&(ABC_isPlaying==false)&&(BR_isPlaying==false)){
          musicPlayer.stopPlaying();
          musicPlayer.startPlayingFile("/MOTOR.mp3");
        }
      }
      if((sens=="up")&&(Tnow-TlastStep>stepLength)){
        pos += posIncrement;
        MOTOR_pos(pos, true);
        TlastStep = Tnow;
        if(pos>posDestination) sens="down";
      }
      if((sens=="down")&&(Tnow-TlastStep>stepLength)){
        pos -= posIncrement;
        MOTOR_pos(pos, true);
        TlastStep = Tnow;
        // Reloop
        if((pos<0)&&(step<numberOfMovements)){ sens="up"; step++; playSound = true; }
        // End of action
        if((pos<0)&&(step==numberOfMovements)) { TlastAction=Tnow; is_on=false; }
      }
    }
  }

};

//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////


MOTOR mymotor;
int motorPosition = 0;

void MOTOR_update(){
	  mymotor.update();
}

// called by xTaskCreate (to run on core0)
void MOTOR_asyncPos(void * data) {
  int position = *(int *) data;
  myservo.write(position);
  // Serial.println("motor pos 2");
  vTaskDelete( NULL );
}

// Set Motor position, if newtask is TRUE > use a separate Task on Core0
void MOTOR_pos(int position, bool newtask){
  // Serial.println("motor pos 1");
  motorPosition = position;
  if (!newtask) myservo.write(position);
  else xTaskCreatePinnedToCore(
                  MOTOR_asyncPos,   /* Function to implement the task */
                  "motorTask", /* Name of the task */
                  10000,      /* Stack size in words */
                  &motorPosition,       /* Task input parameter */
                  10,          /* Priority of the task */
                  NULL,       /* Task handle. */
                  0);         /* Core where the task should run */
}

// Set Motor position (do not use separate Task)
void MOTOR_pos(int position){
  MOTOR_pos(position, false);
}
