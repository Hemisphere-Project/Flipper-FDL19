//////////////////////////////////////////
/////////////       T      ///////////////
//////////////////////////////////////////

int T_Actions[ 5 ] = { 1000, 3000, 6000, 9000, 12000};


class T
{
	unsigned long TlastStep;
	bool is_on = false;
  int step = 0;
	int actionIndex = 0;
	// Timing
	long stepLength = 300;
	int actionLength = 4 * stepLength;
	// luminosity
	int masterT = 30;

  // Constructor
  public:
  T(){

  }

  void restart(){
		actionIndex = 0;
		step = 0;
    for (size_t i = 0; i < sizeof(T_Adresses)/sizeof(int); i++) {
      dmx.write(T_Adresses[i], masterT);
    }
  }

  void update(){

		// ON
		if((Tnow-TstartTimeline>T_Actions[actionIndex])&&(Tnow-TstartTimeline<T_Actions[actionIndex]+actionLength)){

			// ACTION steps
			if(Tnow-TlastStep>stepLength){
				// Serial.print("action "); LOG(actionIndex); Serial.print("step "); LOG(step);
        if(step%2==0){ // if((step==0)||(step==2)){
          for (size_t i = 0; i < sizeof(T_Adresses)/sizeof(int); i++) { dmx.write(T_Adresses[i], 0); }
        }
        if(step%2!=0){ //if((step==1)||(step==3)){
          for (size_t i = 0; i < sizeof(T_Adresses)/sizeof(int); i++) { dmx.write(T_Adresses[i], masterT); }
        }
				step++;
    		TlastStep = Tnow;
        if(step>3){ actionIndex++; step=0; }
			}
		}

  }

};

//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////

T tete;

void T_restart(){
	  tete.restart();
}
void T_update(){
	  tete.update();
}
