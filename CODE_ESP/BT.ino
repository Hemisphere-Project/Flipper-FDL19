//////////////////////////////////////////
/////////////      BT      ///////////////
//////////////////////////////////////////

class BT
{
	int randomIndex;
	int randomBT;
	unsigned long Tlast;
	bool is_on = false;
	// Timing
	long OnTime = 300;
	long OffTime;
	long OffTimeMin = 200;
	long OffTimeMax = 3000;

  // Constructor
  public:
  BT(){
		randomIndex = 0;
		Tlast = 0;
	  OffTime = random(OffTimeMin,OffTimeMax);
  }

  void Update(){

    // ON
    if((Tnow-Tlast>OffTime)&&(is_on==false)){
			is_on=true;
			digitalWrite(16,HIGH);
			dmx.write(randomBT,30);
			if(dontPlay==false){
				String filename = "/BT"+String(randomBT)+".mp3";
				musicPlayer.startPlayingFile(filename.c_str());
			}
    }
    // OFF
    if((Tnow-Tlast>OffTime+OnTime)&&(is_on==true)){
			is_on=false;
			digitalWrite(16,LOW);
			dmx.write(randomBT,0);
			// NEXT
			Tlast = Tnow;
			OffTime = random(OffTimeMin,OffTimeMax);
			randomIndex = random(sizeof(BT_Adresses) / sizeof(int));
			randomBT = BT_Adresses[randomIndex];
    }

  }

};

//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////


BT bumpersT;


void BT_Update(){

	  bumpersT.Update();

}
