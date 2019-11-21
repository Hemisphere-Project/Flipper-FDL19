//////////////////////////////////////////
/////////////      VWX     ///////////////
//////////////////////////////////////////

int VWX_Actions[ 5 ] = { 2000, 7000, 1000, 15000, 20000};


class VWX
{
	unsigned long Tlast,TlastStep;
	bool is_on = false;
  int step = 0;
	int action = 0;
	// Timing
	long stepTime = 100;
  long actionLength = 1800;

  // Constructor
  public:
  VWX(){
		Tlast = 0;
    TlastStep = 0;
  }

  void Init(){
    for (size_t i = 0; i < sizeof(VWX_Adresses)/sizeof(int); i++) {
      dmx.write(VWX_Adresses[i], 10);
    }
  }


  void Update(){
    // ON
    if((Tnow-TstartTimeline>VWX_Actions[action])&&(Tnow-Tlast<VWX_Actions[action]+actionLength)){
		Serial.println("in");
      if(Tnow-TlastStep>stepTime){
        if(step!=0) dmx.write(VWX_Adresses[step-1], 10);
        dmx.write(VWX_Adresses[step], 0);
        step++;
        TlastStep = Tnow;
        if(step==1+sizeof(VWX_Adresses)/sizeof(int)){step=0;}
      }
    }

		// if((Tnow-TstartTimeline>VWX_Actions[action]+actionLength)&&(false)){
		// 	action++;
		// 	Serial.println(action);
		// }

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
