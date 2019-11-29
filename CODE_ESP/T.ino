//////////////////////////////////////////
/////////////       T      ///////////////
//////////////////////////////////////////

int T_Actions[ 41 ] = {
												// 20000, 21200, 22400, 23600, 24800, 26000, 27200, 28400,
												60000, 120000, 180000, 240000, 300000,
												320000, 321200, 322400, 323600, 324800, 326000, 327200, 328400, 329600, 330800,
												332000, 333200, 334400, 335600, 336800, 338000, 339200, 340400, 341600, 342800,
												344000, 345200, 346400, 347600, 348800, 350000, 351200, 352400, 353600, 354800,
												356000, 357200, 358400, 359600, 360800, 362000
											 };

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
	int masterT = 255;
	// for fadeout
	float masterValue = masterT;

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
		masterValue = masterT;
  }

  void update(){

		// ON
		if((Tnow-TstartTimeline>T_Actions[actionIndex])&&(Tnow-TstartTimeline<T_Actions[actionIndex]+actionLength)){
			is_on = true;
			// ACTION steps
			if(Tnow-TlastStep>stepLength){
				// LOGINL("action "); LOGINL(actionIndex); LOGINL(" step "); LOG(step);
        if(step%2==0){ // if((step==0)||(step==2)){
          for (size_t i = 0; i < sizeof(T_Adresses)/sizeof(int); i++) { dmx.write(T_Adresses[i], 0); }
        }
        if(step%2!=0){ //if((step==1)||(step==3)){
          for (size_t i = 0; i < sizeof(T_Adresses)/sizeof(int); i++) { dmx.write(T_Adresses[i], masterT); }
        }
				step++;
    		TlastStep = Tnow;
        // if(step>3){ actionIndex++; step=0; LOG("END OF T Action");}
			}
		}
		// END OF ACTION
		if((Tnow-TstartTimeline>T_Actions[actionIndex]+actionLength)&&(is_on==true)){
			actionIndex++; step = 0; is_on = false;
		}

  }

	void fadeout(){
		if(masterValue>=0){
			masterValue = masterValue - 1;
			if(masterValue<0) masterValue = 1;
			for (size_t i = 0; i < sizeof(T_Adresses)/sizeof(int); i++) { dmx.write(T_Adresses[i], int(masterValue)); }
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
void T_fadeout(){
	tete.fadeout();
}
