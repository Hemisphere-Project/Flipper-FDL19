
// Backtrace: 0x400f3472:0x3ffbc040 0x400de9d3:0x3ffbc060 0x40087136:0x3ffbc080 0x40085289:0x3ffbc0a0



//////////////////////////////////////////
////////////      MOTOR      /////////////
//////////////////////////////////////////

class MOTOR
{
	int re;
  String sens = "up";
  int period = 6000;
  bool is_on = false;
  unsigned long TlastAction, TlastStep;
  //Movement
  int posIncrement = 4;
  int stepLength = 10;
  int posDestination = 6;


  // Constructor
  public:
  MOTOR(){
		TlastAction = 0;
    TlastStep = 0;
  }


  void update(){

    if(Tnow-TlastAction>period){

      if(is_on==false){
        musicPlayer.startPlayingFile("/MOTOR.mp3");
        is_on=true;
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
        if(pos<0) {sens="up"; TlastAction=Tnow; is_on=false;}
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
