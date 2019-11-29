
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
  int posIncrement = 4; // 4
  int stepLength = 12;  // 10
  int posDestination = 40; //40
	//Timing
  // int period = 7000;

  // Constructor
  public:
  MOTOR(){
		TlastAction = 0;
    TlastStep = 0;
  }


  void update(int period){

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
        if((VWX_isPlaying==false)&&(ABC_isPlaying==false)&&(BR_isPlaying==false)&&(BT_isPlaying==false)&&(No_One_Plays==false)){
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

void MOTOR_update(int period){
	  mymotor.update(period);
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
