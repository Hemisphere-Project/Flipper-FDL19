
bool rpi_pin_HIGH=false;

void rpi_Update(){
	if((Tnow-TstartTimeline<500)&&(rpi_pin_HIGH==false)){
		digitalWrite(16,HIGH);
		rpi_pin_HIGH = true;
	}else if((Tnow-TstartTimeline>500)&&(rpi_pin_HIGH==true)){
		digitalWrite(16,LOW);
		rpi_pin_HIGH = false;
	}
}
