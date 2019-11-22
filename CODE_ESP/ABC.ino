//////////////////////////////////////////
/////////////      ABC     ///////////////
//////////////////////////////////////////

int ABC_Actions[ 6 ] = { 0, 5000, 10000, 15000, 20000, 100000};



class ABC
{
	unsigned long TlastStep;
	bool is_on = false;
  int step = 0;
	int actionIndex = 0;
	// Timing
	long stepLength = 500;
	// luminosity
	int masterABC = 30;

  // Constructor
  public:
  ABC(){

  }

  void restart(){
		actionIndex = 0;
		step = 0;
  }

  void update(){

		// ON
		if(Tnow-TstartTimeline>ABC_Actions[actionIndex]){
			// ONCE
			if(is_on==false){
				for (size_t i = 0; i < sizeof(ABC_Adresses)/sizeof(int); i++) {
					dmx.write(ABC_Adresses[i], masterABC);
				}
				if(actionIndex!=0){
					musicPlayer.startPlayingFile("/RESET_PASTILLES.mp3");
					dontPlay=true;
				}
				step = 0;
				is_on = true;
			}
			// END of audio file priority
			if((Tnow-TstartTimeline>ABC_Actions[actionIndex]+2000)&&(dontPlay==true)){
				dontPlay=false;
			}
			// ACTION steps
			if(Tnow-TlastStep>stepLength){
				dmx.write(ABC_Adresses[step], 0);
				step++;
				TlastStep = Tnow;
				// END OF ACTION
				if(step==sizeof(ABC_Adresses)/sizeof(int)){is_on = false; actionIndex++;}
			}
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
