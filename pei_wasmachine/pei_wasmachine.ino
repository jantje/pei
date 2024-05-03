
#include "pei_wasmachine.h"

#define WASMACHINE_1_PIN 13
#define WASMACHINE_2_PIN 12
#define WASMACHINE_3_PIN 11
#define WASMACHINE_4_PIN 10


#define SECONDS   1000UL
#define MINUTES  60000UL
//#define ACCELERATION 1000UL
#define ACCELERATION 1UL

WasMachine wasMachine_1(WASMACHINE_1_PIN,0UL *MINUTES,20UL*MINUTES,40UL*MINUTES);
WasMachine wasMachine_2(WASMACHINE_2_PIN,15UL*MINUTES,20UL*MINUTES,40UL*MINUTES);
WasMachine wasMachine_3(WASMACHINE_3_PIN,30UL*MINUTES,20UL*MINUTES,40UL*MINUTES);
WasMachine wasMachine_4(WASMACHINE_4_PIN,40UL*MINUTES,20UL*MINUTES,40UL*MINUTES);
Brains brains(10UL*MINUTES,1UL*MINUTES);

uint32_t loopMillis=0;


void setup() {
	delay(1000);
  Serial.begin(9600);
  Serial.println("Wasmachine start");
  wasMachine_1.setup();
  wasMachine_2.setup();
  wasMachine_3.setup();
  wasMachine_4.setup();
  brains.setup();
  wasMachine_1.start();
  wasMachine_2.start();
  wasMachine_3.start();
  wasMachine_4.start();


}

void loop() {
	static uint32_t lastPlot;
	loopMillis=millis();//*ACCELERATION;
	if(loopMillis-lastPlot>1000UL){
		lastPlot=loopMillis;
		plot4(Serial,wasMachine_1.getActualPinValue()*50,
				wasMachine_2.getActualPinValue()*100,
				wasMachine_3.getActualPinValue()*150,
				wasMachine_4.getActualPinValue()*200);
	}
	  wasMachine_1.loop();
	  wasMachine_2.loop();
	  wasMachine_3.loop();
	  wasMachine_4.loop();
	  brains.loop();
}
