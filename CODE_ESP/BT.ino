//////////////////////////////////////////
/////////////      BT      ///////////////
//////////////////////////////////////////

class BT
{
	int randomIndex;
	int randomBT = BT_Adresses[0];
	unsigned long Tlast;
	bool is_on = false;
	// Timing
	int OnTime = 250;
	int OffTime = 1000;
	// int OffTimeMin = 200;
	// int OffTimeMax = 3000;
	// luminosity
	int masterBT = 30;

  // Constructor
  public:
  BT(){
		randomIndex = 0;
		Tlast = 0;
  }

	void restart(){

	}

  void update(int OffTimeMin,int OffTimeMax){

    // ON
    if((Tnow-Tlast>OffTime)&&(is_on==false)){
			is_on=true;
			dmx.write(randomBT,masterBT);
			if((VWX_isPlaying==false)&&(ABC_isPlaying==false)&&(BR_isPlaying==false)){
				String filename = "/BT"+String(randomBT)+".mp3";
				musicPlayer.stopPlaying();
				musicPlayer.startPlayingFile(filename.c_str());
			}
    }
    // OFF
    if((Tnow-Tlast>OffTime+OnTime)&&(is_on==true)){
			is_on=false;
			dmx.write(randomBT,0);
			// NEXT
			Tlast = Tnow;
			OffTime = random(OffTimeMin,OffTimeMax);
			randomIndex = random(sizeof(BT_Adresses) / sizeof(int));
			randomBT = BT_Adresses[randomIndex];
    }

  }

	void forceOff(){
		is_on=false;
		dmx.write(randomBT,0);
	}

};

//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////


BT bumpersT;

void BT_update(int offMin,int offMax){
  bumpersT.update(offMin, offMax);
}
void BT_restart(){
  bumpersT.restart();
}
void BT_forceOff(){
  bumpersT.forceOff();
}
