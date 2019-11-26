
// Backtrace: 0x400f3472:0x3ffbc040 0x400de9d3:0x3ffbc060 0x40087136:0x3ffbc080 0x40085289:0x3ffbc0a0
// Backtrace: 0x400f34b2:0x3ffbc040 0x400dea13:0x3ffbc060 0x40087136:0x3ffbc080 0x40085289:0x3ffbc0a0

// Backtrace: 0x40089020:0x3ffb1e40 0x4008924d:0x3ffb1e60 0x4008169f:0x3ffb1e80 0x4000be0d:0x3ffb1ea0 0x4000209c:0x3ffb1ec0 0x400020b5:0x3ffb1ee0 0x400d2c15:0x3ffb1f00 0x400d2b85:0x3ffb1f20 0x400d3872:0x3ffb1f50 0x400d1231:0x3ffb1f70 0x400d17bb:0x3ffb1f90 0x400d6745:0x3ffb1fb0 0x40085289:0x3ffb1fd0
// Backtrace: 0x40089020:0x3ffb1e20 0x4008924d:0x3ffb1e40 0x4008169f:0x3ffb1e60 0x4000be0d:0x3ffb1e80 0x4000209c:0x3ffb1ea0 0x400020b5:0x3ffb1ec0 0x400d2c15:0x3ffb1ee0 0x400d2b85:0x3ffb1f00 0x400d3872:0x3ffb1f30 0x400d149c:0x3ffb1f50 0x400d156a:0x3ffb1f70 0x400d17c4:0x3ffb1f90 0x400d6745:0x3ffb1fb0 0x40085289:0x3ffb1fd0



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
        myservo.write(pos);
        TlastStep = Tnow;
        if(pos>posDestination) sens="down";
      }
      if((sens=="down")&&(Tnow-TlastStep>stepLength)){
        pos -= posIncrement;
        myservo.write(pos);
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


void MOTOR_update(){

	  mymotor.update();

}
