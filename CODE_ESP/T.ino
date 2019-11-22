//////////////////////////////////////////
/////////////       T      ///////////////
//////////////////////////////////////////

int T_Actions[ 6 ] = { 5000, 10000, 15000, 20000, 25000};


class T
{
	unsigned long TlastStep;
	bool is_on = false;
  int step = 0;
	int actionIndex = 0;
	// Timing
	long stepLength = 300;
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
		if(Tnow-TstartTimeline>T_Actions[actionIndex]){

			// ACTION steps
			if(Tnow-TlastStep>stepLength){
        if(step%2==0){ // if((step==0)||(step==2)){
          for (size_t i = 0; i < sizeof(T_Adresses)/sizeof(int); i++) { dmx.write(T_Adresses[i], 0); }
        }
        if(step%2!=0){ //if((step==1)||(step==3)){
          for (size_t i = 0; i < sizeof(T_Adresses)/sizeof(int); i++) { dmx.write(T_Adresses[i], masterT); }
        }
				step++;
        if(step>3){ actionIndex++; step = 0; }
    		TlastStep = Tnow;
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
