//////////////////////////////////////////
/////////////      ABC     ///////////////
//////////////////////////////////////////

int ABC_Actions[ 6 ] = { 0, 5000, 10000, 15000, 20000, 100000};



class ABC
{
	unsigned long TlastStep;
	bool is_on = false;
	bool audio_is_on = false;
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

  void Init(){

  }

  void Update(){

		// ON
		if(Tnow-TstartTimeline>ABC_Actions[actionIndex]){
			// ONCE
			if(is_on==false){
				LOG("init ABCs");
				for (size_t i = 0; i < sizeof(ABC_Adresses)/sizeof(int); i++) {
					dmx.write(ABC_Adresses[i], masterABC);
				}
				if(actionIndex!=0){
					musicPlayer.startPlayingFile("/RESET_PASTILLES.mp3");
					LOG("PLAY RESET");
					dontPlay=true;
				}
				step = 0;
				is_on = true;
			}
			if((Tnow-TstartTimeline>ABC_Actions[actionIndex]+2000)&&(dontPlay==true)){
				LOG("END RESET");
				dontPlay=false;
			}
			// ACT
			if(Tnow-TlastStep>stepLength){
				LOG("éteint un des ABCs");
				dmx.write(ABC_Adresses[step], 0);
				step++;
				TlastStep = Tnow;
				if(step==sizeof(ABC_Adresses)/sizeof(int)){is_on = false; actionIndex++;}
			}
		}


  }

};

//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////

ABC abcdefgh;

void ABC_Update(){
	  abcdefgh.Update();
}
void ABC_Init(){
	  abcdefgh.Init();
}
