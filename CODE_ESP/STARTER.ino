// BUG avec le white decoder
// frames stacked

int master = 255;
int stepLength = 200;
unsigned long TlastStep = 0;
int step = 0;
int ABC_step = 0;
int BT_step = 0;
int BR_step = 0;
int VWX_step = 0;

void starter_restart(){
  step = 0;
  ABC_step = 0;
  BT_step = 0;
  BR_step = 0;
  VWX_step = 0;
}

void starter_update(){


  if(Tnow-TlastStep>stepLength){
    // START
    if(step==0){
      starting = true;
      for (size_t i = 0; i < 128; i++) { dmx.write(i,0); }
    }
    // ABC
    if(step==1){
      stepLength = 200;
      musicPlayer.stopPlaying();
      musicPlayer.startPlayingFile("/RESET_PASTILLES.mp3");
    }
    if((step>=1)&&(step<9)){
      dmx.write(ABC_Adresses[ABC_step], master);
      ABC_step++;
    }
    // BT
    if((step>=15)&&(step<22)){
      stepLength = 500;
      dmx.write(BT_Adresses[BT_step], master);
      BT_step++;
      String filename = "/BT"+String(BT_step)+".mp3";
      musicPlayer.stopPlaying();
      musicPlayer.startPlayingFile(filename.c_str());
    }
    // BR
    if((step==25)||(step==26)){
      stepLength = 500;
      dmx.write(BR_Adresses[BR_step], master);
      BR_step++;
      musicPlayer.stopPlaying();
      musicPlayer.startPlayingFile("/BR.mp3");
    }
    // VWX
    if(step==30){
      stepLength = 200;
      musicPlayer.stopPlaying();
      musicPlayer.startPlayingFile("/VWX.mp3");
    }
    if((step>=30)&&(step<36)){
      dmx.write(VWX_Adresses[VWX_step], master);
      VWX_step++;
    }
    // T
    if((step>=36)&&(step<41)){
      if(step%2==0){
        for (size_t i = 0; i < sizeof(T_Adresses)/sizeof(int); i++) { dmx.write(T_Adresses[i], master); }
      }
      if(step%2!=0){
        for (size_t i = 0; i < sizeof(T_Adresses)/sizeof(int); i++) { dmx.write(T_Adresses[i], 0); }
      }
    }

    if(step==42){
      // LOG(Tnow-TstartTimeline);
			for (size_t i = 0; i < sizeof(ABC_Adresses)/sizeof(int); i++) { dmx.write(ABC_Adresses[i], 0); }
			for (size_t i = 0; i < sizeof(BR_Adresses)/sizeof(int); i++) { dmx.write(BR_Adresses[i], 0); }
			for (size_t i = 0; i < sizeof(BT_Adresses)/sizeof(int); i++) { dmx.write(BT_Adresses[i], 0); }
      starting = false;
    }

    TlastStep = Tnow;
    step++;
  }

}

//////////////////////////////////////////
/////////////      OLD     ///////////////
//////////////////////////////////////////

// void testAll(){
//
//   // ALL OFF
//   for (size_t i = 0; i < 128; i++) { dmx.write(i,0); }
//   delay(1000);
//   pushData();
//
//   // ABC
//   musicPlayer.stopPlaying();
//   musicPlayer.startPlayingFile("/RESET_PASTILLES.mp3");
//   for (size_t i = 0; i < sizeof(ABC_Adresses)/sizeof(int); i++) {
//     dmx.write(ABC_Adresses[i], master);
//     dmx.update(); pushData();
//     delay(40);
//   }
//   delay(200);
//
//   // BT
//   for (size_t i = 0; i < sizeof(BT_Adresses)/sizeof(int); i++) {
//     String filename = "/BT"+String(i+1)+".mp3";
//     musicPlayer.stopPlaying();
//     musicPlayer.startPlayingFile(filename.c_str());
//     dmx.write(BT_Adresses[i], master);
//     dmx.update(); pushData();
//     delay(500);
//   }
//   delay(200);
//
//   // BR
//   for (size_t i = 0; i < sizeof(BR_Adresses)/sizeof(int); i++) {
//     musicPlayer.stopPlaying();
//     musicPlayer.startPlayingFile("/BR.mp3");
//     dmx.write(BR_Adresses[i], master);
//     dmx.update(); pushData();
//     delay(1500);
//   }
//   delay(200);
//
//   // VWX
//   musicPlayer.stopPlaying();
//   musicPlayer.startPlayingFile("/VWX.mp3");
//   for (size_t i = 0; i < sizeof(VWX_Adresses)/sizeof(int); i++) {
//     dmx.write(VWX_Adresses[i], master);
//     dmx.update(); pushData();
//     delay(130);
//   }
//   delay(500);
//
//   for (size_t i = 0; i < sizeof(T_Adresses)/sizeof(int); i++) {
//     dmx.write(T_Adresses[i], master);
//     dmx.update(); pushData();
//     delay(50);
//   }
//   delay(200);
//
//   for (pos = 0; pos <= 40; pos += 2) { // goes from 0 degrees to 180 degrees
//     myservo.write(pos);    // tell servo to go to position in variable 'pos'
//     delay(15);             // waits 15ms for the servo to reach the position
//   }
//   for (pos = 40; pos >= 0; pos -= 2) { // goes from 180 degrees to 0 degrees
//     myservo.write(pos);    // tell servo to go to position in variable 'pos'
//     delay(15);             // waits 15ms for the servo to reach the position
//   }
//
// }
//
// void pushData(){
//   for (size_t i = 0; i < 40; i++) {
//     dmx.write(100, 0);
//     dmx.update();
//   }
// }
