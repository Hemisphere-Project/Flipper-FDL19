//////////////////////////////////////////
/////////////      VWX     ///////////////
//////////////////////////////////////////

int VWX_Actions[ 11 ] = { 30000, 90000, 150000, 210000, 270000, 330000, 342000, 346000, 349000, 352000, 355000 };
// int VWX_Actions[ 5 ] = { 4000, 10000, 18000, 25000, 32000};


class VWX
{
	unsigned long TlastStep;
	bool is_on = false;
  int step = 0;
	int actionIndex = 0;
	// Timing
	long stepLength = 130;
  long actionLength = 2400;
	// luminosity
	int masterVWX = 255;
	// for fadeout
	float masterValue = masterVWX;

  // Constructor
  public:
  VWX(){
    TlastStep = 0;
  }

  void restart(){
		actionIndex = 0;
		step = 0;
    for (size_t i = 0; i < sizeof(VWX_Adresses)/sizeof(int); i++) {
      dmx.write(VWX_Adresses[i], masterVWX);
    }
		masterValue = masterVWX;
  }

  void update(){
    // ON
    if((Tnow-TstartTimeline>VWX_Actions[actionIndex])&&(Tnow-TstartTimeline<VWX_Actions[actionIndex]+actionLength)){
			// ONCE - BEGIN OF ACTION
			if(is_on==false){
				musicPlayer.stopPlaying();
				musicPlayer.startPlayingFile("/VWX.mp3");
				step = 0;
				is_on = true;
				VWX_isPlaying = true; //PREVENT OTHER TRACKS FROM PLAYING WHEN VWXYZ ACTIVE (BT, BR)
			}
			// ACTION steps
      if(Tnow-TlastStep>stepLength){
				// Serial.print("action "); LOG(actionIndex);
        if(step!=0) dmx.write(VWX_Adresses[step-1], masterVWX);
        dmx.write(VWX_Adresses[step], 0);
        step++;
        TlastStep = Tnow;
        if(step==1+sizeof(VWX_Adresses)/sizeof(int)){step=0;}
      }
    }
		// END OF ACTION
		if((Tnow-TstartTimeline>VWX_Actions[actionIndex]+actionLength)&&(is_on==true)){
			actionIndex++;
			is_on = false;
			VWX_isPlaying = false;
		}

  }

	void fadeout(){
		if(masterValue>=0){
			masterValue = masterValue - 1;
			if(masterValue<0) masterValue = 1;
			for (size_t i = 0; i < sizeof(VWX_Adresses)/sizeof(int); i++) { dmx.write(VWX_Adresses[i], int(masterValue)); }
		}
	}

};

//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////

VWX vwxyz;

void VWX_update(){
	  vwxyz.update();
}
void VWX_restart(){
	  vwxyz.restart();
}
void VWX_fadeout(){
	  vwxyz.fadeout();
}
