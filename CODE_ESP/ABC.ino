//////////////////////////////////////////
/////////////      ABC     ///////////////
//////////////////////////////////////////

// int ABC_Actions[ 6 ] = { 0, 60000, 120000, 180000, 240000, 300000};
int ABC_Actions[ 6 ] = { 0, 3000, 6000, 9000, 12000, 15000};



class ABC
{
	unsigned long TlastStep;
	bool is_on = false;
  int step = 0;
	int actionIndex = 0;
	// Timing
	long stepLength = 100; // 7000
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

				// Serial.print("ABC_Actions ");	LOG(ABC_Actions[actionIndex]);
				// Serial.print("ABC_Actions SIZE "); LOG(sizeof(ABC_Actions)/sizeof(int));
				// Serial.print("action "); LOG(actionIndex);

				dmx.write(ABC_Adresses[step], 0);
				step++;
				TlastStep = Tnow;
				// END OF ACTION
				if(step==sizeof(ABC_Adresses)/sizeof(int)){
					is_on = false;
					actionIndex++;
					// if(actionIndex<(sizeof(ABC_Actions)/sizeof(int))) actionIndex++; // MARCHE PAS
				}
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
