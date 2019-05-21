// #include "myDataPacketStructure.h"

/*  ┌──────────────────────────────────────────────────┐
 *  │  Include Twiggs Space Lab Payload Board Library  │
 *  └──────────────────────────────────────────────────┘ */

#include "TSLPB.h"

/*  ┌──────────────────────────────────────────────────┐
 *  │   Instantiate Controller Classes and Variables   │
 *  └──────────────────────────────────────────────────┘ */

TSLPB pb;
ThinsatPacket_t data;

void setup()
{
    pb.begin();
}

void loop()
{
	/*  ┌──────────────────────────────────────────────┐
	 *  │    Alternate Red and Green LEDs on TSLPB     │
	 *  └──────────────────────────────────────────────┘ */
    
    pb.setLED(Green, ON);
    pb.setLED(Red, OFF);

    delay(1000);

    pb.setLED(Green, OFF);
    pb.setLED(Red, ON);
    
    delay(1000);
}