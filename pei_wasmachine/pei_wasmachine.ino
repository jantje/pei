
#include "pei_wasmachine.h"

#define WASMACHINE_1_PIN 13
#define WASMACHINE_2_PIN 12
#define WASMACHINE_3_PIN 11
#define WASMACHINE_4_PIN 10


#define SECONDS   *1000UL
#define MINUTES  *60000UL


/*Je kan de waarden hieronder aanpassen om een andezre show te krijgen
 * De eerste waarde is de pin die aan de wasmachine is toegewezen
 * De pin is een define en de echte waarden zie je hierboven staan
 * De tweede waarde is de tijd die het duurd voor de wasmachine de eerste maal
 * zal draaien. Dit is omdat ze niet allemaal terzelfder tijd zouden starten.
 * Na deze opstart tijd gaat de machine in een lus aan (gedurende derde waarde tijd) en uit
 * (gedurende vierde waarde tijd).
 *
 * Alle tijden zijn in milli seconden door MINUTES of SECONDS toe te voegen
 * kan je leesbaardere tijden krijgen.
 * Die UL is om te zeggen dat het over grote getallen gaat en moet blijven staan.
 */
WasMachine wasMachine_1(WASMACHINE_1_PIN,0UL MINUTES,20UL MINUTES,40UL MINUTES);
WasMachine wasMachine_2(WASMACHINE_2_PIN,15UL MINUTES,20UL MINUTES,40UL MINUTES);
WasMachine wasMachine_3(WASMACHINE_3_PIN,30UL MINUTES,20UL MINUTES,40UL MINUTES);
WasMachine wasMachine_4(WASMACHINE_4_PIN,40UL MINUTES,20UL MINUTES,40UL MINUTES);
Brains brains(10UL MINUTES,1UL MINUTES);

uint32_t loopMillis=0;

//#define ACCELERATION * 1000UL
//#define HEADSTART  +(0UL-60000UL)
#ifndef ACCELERATION
#define ACCELERATION //this is real time
#endif
#ifndef HEADSTART
#define HEADSTART  //this is real time
#endif


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
	loopMillis=(millis() ACCELERATION) HEADSTART;
	if(loopMillis-lastPlot>1000UL){
		lastPlot=loopMillis;
		plot4(Serial,wasMachine_1.getActualPinValue()*400,
				wasMachine_2.getActualPinValue()*450,
				wasMachine_3.getActualPinValue()*500,
				wasMachine_4.getActualPinValue()*550);
	}
	  wasMachine_1.loop();
	  wasMachine_2.loop();
	  wasMachine_3.loop();
	  wasMachine_4.loop();
	  brains.loop();
}
