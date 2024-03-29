//////////////////////////////////////////
/////////////      BR      ///////////////
//////////////////////////////////////////

int BR_Actions[ 38 ] = { 17000, 27000, 38000, 45000, 67000, 85000, 102000, 119000, 134000, 154000,
												166000, 182000, 204000, 224000, 245000, 278000, 283000, 287000, 291000, 293000,
												297000,  305000, 308000, 311000, 314000, 317000, 323000, 326000, 330000, 338000,
												342000, 344000, 347000, 349000, 351000, 353000, 355000, 357500 };


class bmpR
{
	unsigned long TlastStep;
  bool light_is_on=false;
  bool is_on=false;
	int actionIndex = 0;
  int step = 0;
  int ran;
	// luminosity
	int masterBR = 255;
  // Timing
  long stepLength = 70;
  long actionLength = 1200;


  // Constructor
  public:
  bmpR(){

  }

  void restart(){
		actionIndex = 0;
		step = 0;
  }

  void update(){

    // ON
    if((Tnow-TstartTimeline>BR_Actions[actionIndex])&&(Tnow-TstartTimeline<BR_Actions[actionIndex]+actionLength)){
      // BEGIN
      if(is_on==false){
          step=0;
          ran = random(0,2);
					if(No_One_Plays==false){
						musicPlayer.stopPlaying();
						musicPlayer.startPlayingFile("/BR.mp3");
					}
          is_on=true;
          BR_isPlaying = true;
        }
      // ACTION steps
      if(Tnow-TlastStep>stepLength){
        if(step%2!=0){ dmx.write(BR_Adresses[ran], masterBR); }
        if(step%2==0){ dmx.write(BR_Adresses[ran], 0); }
        step++;
        TlastStep = Tnow;
        //End of action
        if(step>11){
          actionIndex++;
          step=0;
          is_on=false;
          BR_isPlaying = false;
          dmx.write(BR_Adresses[ran], 0);
        }
      }
    }
  }
	void force0ff(){
		is_on=false;
		dmx.write(BR_Adresses[ran],0);
	}

};

//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////

bmpR bumpersR;

void BR_restart(){
	bumpersR.restart();
}
void BR_update(){
	bumpersR.update();
}
void BR_forceOff(){
  bumpersR.force0ff();
}
