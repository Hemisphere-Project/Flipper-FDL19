// BUG avec le white decoder
// frames stacked

int master = 255;

void testAll(){

  // ALL OFF
  for (size_t i = 0; i < 128; i++) { dmx.write(i,0); }
  delay(1000);
  pushData();

  // ABC
  musicPlayer.stopPlaying();
  musicPlayer.startPlayingFile("/RESET_PASTILLES.mp3");
  for (size_t i = 0; i < sizeof(ABC_Adresses)/sizeof(int); i++) {
    dmx.write(ABC_Adresses[i], master);
    dmx.update(); pushData();
    delay(40);
  }
  delay(200);

  // BT
  for (size_t i = 0; i < sizeof(BT_Adresses)/sizeof(int); i++) {
    String filename = "/BT"+String(i+1)+".mp3";
    musicPlayer.stopPlaying();
    musicPlayer.startPlayingFile(filename.c_str());
    dmx.write(BT_Adresses[i], master);
    dmx.update(); pushData();
    delay(1000);
  }
  delay(200);

  // BR
  for (size_t i = 0; i < sizeof(BR_Adresses)/sizeof(int); i++) {
    musicPlayer.stopPlaying();
    musicPlayer.startPlayingFile("/BR.mp3");
    dmx.write(BR_Adresses[i], master);
    dmx.update(); pushData();
    delay(1500);
  }
  delay(200);

  // VWX
  musicPlayer.stopPlaying();
  musicPlayer.startPlayingFile("/VWX.mp3");
  for (size_t i = 0; i < sizeof(VWX_Adresses)/sizeof(int); i++) {
    dmx.write(VWX_Adresses[i], master);
    dmx.update(); pushData();
    delay(130);
  }
  delay(500);

  for (size_t i = 0; i < sizeof(T_Adresses)/sizeof(int); i++) {
    dmx.write(T_Adresses[i], master);
    dmx.update(); pushData();
    delay(50);
  }
  delay(200);

  // for (pos = 0; pos <= 40; pos += 2) { // goes from 0 degrees to 180 degrees
  //   myservo.write(pos);    // tell servo to go to position in variable 'pos'
  //   delay(15);             // waits 15ms for the servo to reach the position
  // }
  // for (pos = 40; pos >= 0; pos -= 2) { // goes from 180 degrees to 0 degrees
  //   myservo.write(pos);    // tell servo to go to position in variable 'pos'
  //   delay(15);             // waits 15ms for the servo to reach the position
  // }

}

void pushData(){
  // for (size_t i = 0; i < 40; i++) {
  //   dmx.write(100, 0);
  //   dmx.update();
  // }
}
