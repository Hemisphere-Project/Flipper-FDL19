//////////////////////////////////////////
/////////////      ABC     ///////////////
//////////////////////////////////////////

int ABC_Actions[ 6 ] = { 0, 60000, 120000, 180000, 240000, 300000};
// int ABC_Actions[ 6 ] = { 0, 4000, 8000, 12000, 16000, 20000};



class ABC
{
	unsigned long TlastStep;
	bool is_on = false;
  int step = 0;
	int actionIndex = 0;
	// bool allActionsDone = false;
	// Timing
	long stepLength = 7000;
	// long stepLength = 300;
	long actionLength = stepLength * (sizeof(ABC_Adresses)/sizeof(int) + 1 ) ;
	// luminosity
	int masterABC = 255;
	// for fadeout
	float masterValue = masterABC;

  // Constructor
  public:
  ABC(){

  }

  void restart(){
		actionIndex = 0;
		step = 0;
		// allActionsDone = false;
		masterValue = masterABC;
  }

  void update(){

		// ON
		// if((Tnow-TstartTimeline>ABC_Actions[actionIndex])&&(allActionsDone==false)){
		if((Tnow-TstartTimeline>ABC_Actions[actionIndex])&&(Tnow-TstartTimeline<ABC_Actions[actionIndex]+actionLength)){
			// ONCE
			if(is_on==false){
				for (size_t i = 0; i < sizeof(ABC_Adresses)/sizeof(int); i++) { dmx.write(ABC_Adresses[i], masterABC); }
				if(actionIndex!=0){
					musicPlayer.stopPlaying();
					musicPlayer.startPlayingFile("/RESET_PASTILLES.mp3");
					ABC_isPlaying=true;
				}
				step = 0;
				is_on = true;
			}
			// END of audio file priority
			if((Tnow-TstartTimeline>ABC_Actions[actionIndex]+2000)&&(ABC_isPlaying==true)){
				ABC_isPlaying=false;
			}
			// ACTION steps
			if(Tnow-TlastStep>stepLength){
				// Serial.print("action "); LOG(actionIndex); Serial.print("step "); LOG(step);
				step++;
				dmx.write(ABC_Adresses[step], 0);
				TlastStep = Tnow;
				// END OF ACTION
				if(step==sizeof(ABC_Adresses)/sizeof(int)){
					is_on = false;
					actionIndex++;
					// if(actionIndex<(sizeof(ABC_Actions)/sizeof(int) - 1)){ actionIndex++;} else allActionsDone = true;
				}
			}
		}

  }

	void fadeout(){
		if(masterValue>=0){
			masterValue = masterValue - 1;
			if(masterValue<0) masterValue = 1;
			for (size_t i = 0; i < sizeof(ABC_Adresses)/sizeof(int); i++) { dmx.write(ABC_Adresses[i], int(masterValue)); }
		}
	}

};

//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////

ABC abcdefgh;

void ABC_restart(){
	abcdefgh.restart();
}
void ABC_update(){
	abcdefgh.update();
}
void ABC_fadeout(){
	abcdefgh.fadeout();
}
