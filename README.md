
# Twiggs Space Lab Payload Board Driver

TSLPB is a driver class that can be instantiated and used to access the
sensors and devices on the TSLPB V3 for the ThinSat program.

The driver sets up all the input and output pins required for accessing the
analog sensors, and provides methods for reading both the analog and digital
sensors.

## Basic Usage

 You will need to do the following to use this library:
     1. Include tslbp.h in your program.
     2. Instantiate a TSLPB object
     3. Run the TSLPB::begin() method

Once these steps are complete, you may call any of the public methods to
interact with the TSL Payload Board.

## Creating your DataPacket struct

The TSLPB uses a union of a byte array and a struct to allow you to store your 
data in semantically relevant variables. For example, if you want to save
temperature data, instead of storing the bytes directly as follows:

``` c++
long myTemp = getTemp();
byte[1] = highByte(myTemp);
byte[2] = lowByte(myTemp);
```

the user can use:

``` c++
myData.temp = getTemp();
```

If you don't define a custom data packet structure, the library will use the
one defined in ```ThinSat_DataPacket_generic.h```, which does not use 
semantically named fields. They are simply:

``` c++
myData.payloadData.b1;
myData.payloadData.b2;
myData.payloadData.b3;
...
myData.payloadData.b35;
```



### Example

``` c++
 #include "TSLPB.h"

 TSLBP tslpb;
 ThinsatPacket_t missionData;

 void setup() {
     tslpb.begin();
 }

 void loop() {
     uint16_t tslVolts   = tslpb.readAnalogSensor(Voltage);
     uint16_t tslCurrent = tslpb.readAnalogSensor(Current);
     uint16_t tslTempExt = tslpb.readAnalogSensor(TempExt);

     uint16_t tslDT1Raw  = tslpb.readTSLDigitalSensorRaw(DT1);
     double   tslDT1C    = tslpb.readTSLDigitalSensor(DT1);

     missionData.payloadData.solar = tslpb.readAnalogSensor(Solar);

     while (!tslpb.isClearToSend())
     {
         delay(100);
     }

     tslpb.pushDataToNSL(missionData);
 }

```

 You probably noticed the "Voltage", "Current", etc arguments. The TSLPB
 driver has two enums that allow the client to call the read methods with
 human-readable code, and without worrying about keeping I2C addresses or
 managing low-level mux switching.

 - ::TSLPB_AnalogSensor_t
 - ::TSLPB_DigitalSensor_t
 