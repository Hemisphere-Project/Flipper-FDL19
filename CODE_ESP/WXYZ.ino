//////////////////////////////////////////
/////////////      VWX     ///////////////
//////////////////////////////////////////

int VWX_Actions[ 5 ] = { 4000, 10000, 18000, 25000, 32000};


class VWX
{
	unsigned long TlastStep;
	bool is_on = false;
  int step = 0;
	int action = 0;
	// Timing
	long stepTime = 130;
  long actionLength = 2400;

  // Constructor
  public:
  VWX(){
    TlastStep = 0;
  }

  void Init(){
    for (size_t i = 0; i < sizeof(VWX_Adresses)/sizeof(int); i++) {
      dmx.write(VWX_Adresses[i], 10);
    }
  }


  void Update(){
    // ON
    if((Tnow-TstartTimeline>VWX_Actions[action])&&(Tnow-TstartTimeline<VWX_Actions[action]+actionLength)){

			// ONCE
			if(is_on==false){
				musicPlayer.startPlayingFile("/VWX.mp3");
				step = 0;
				is_on = true;
				dontPlay = true; //PREVENT OTHER TRACKS FROM PLAYING WHEN VWXYZ ACTIVE (BT, BR)
			}
			// ACT
      if(Tnow-TlastStep>stepTime){
        if(step!=0) dmx.write(VWX_Adresses[step-1], 10);
        dmx.write(VWX_Adresses[step], 0);
        step++;
        TlastStep = Tnow;
        if(step==1+sizeof(VWX_Adresses)/sizeof(int)){step=0;}
      }
    }

		if((Tnow-TstartTimeline>VWX_Actions[action]+actionLength)&&(true)){
			action++;
			is_on = false;
			dontPlay = false;
		}

  }

};

//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////

VWX vwxyz;

void VWX_Update(){
	  vwxyz.Update();
}
void VWX_Init(){
	  vwxyz.Init();
}
