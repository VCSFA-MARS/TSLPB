/*  ┌──────────────────────────────────────────────────┐
    │      TSLPB EEPROM Example Code and Tutorial      │
    └──────────────────────────────────────────────────┘

    Description of the project
    Developed with [embedXcode](http://embedXcode.weebly.com)

    Author       Nicholas Counts
                 Counts Engineering

    Date         05/14/18 3:45 PM
    Version      0.5.2

    Copyright    © Nicholas Counts, 2018
    Licence      MIT



    This example works through the TSLPB EEPROM (memory)
    functions:

      putMemByte()  - write a single byte to the EEPROM
      getMemByte()  - read a single byte from the EEPROM

      writeMemVar() - write your entire variable to the EEPROM
      readMemVar()  - read a value from the EEPROM and store it
                      as the correct type.

*/


#include "TSLPB.h"


TSLPB pb;
ThinsatPacket_t missionData;



void setup() {
  // put your setup code here, to run once:
  pb.begin();
}


/*  ┌──────────────────────────────────────────────────┐
 *  │        EEPROM Read and Write Demonstration       │
 *  └──────────────────────────────────────────────────┘ */

void loop() {

  
  /*
   * The first example: We write 4 individual bytes to the EEPROM.
   * Then we read them back. Pretty exciting, right?
   */
  
  word reg = 0;
  float pi = 3.14159;
  
  Serial.println("Trying to read the first 16 registers on the TSLPB EEPROM Chip\n\n");

  Serial.println("Example 1:\n--------------------------------------\n");

    Serial.print("Writing the first 4 EEPROM bytes with the following: 40 49 0f d0 ");
    pb.putMemByte(0x40, 0);
    pb.putMemByte(0x49, 1);
    pb.putMemByte(0x0f, 2);
    pb.putMemByte(0xd0, 3);
    
    Serial.println("\nReading the first 4 EEPROM registers:");
    printRegFromTo(0, 3);


  /*
   * In the last example, we wrote data to the EEPROM. But what did it mean?
   * It turns out, those 1s and 0s could mean all kinds of things, depending
   * on how youinterpret them.
   * 
   * For example:
   * 
   *   The hex value 0x65 has the following bit pattern: 01100101
   *   If we treat it as a character, it would be the letter "A"
   *   If we treat it as an integer, it would be the number 101
   *   The way we treat raw data is referred to as the "type" of
   *   the data. 
   *   
   * In this example, we will read the first 4 bytes of the EEPROM
   * and treat them as a floating point (think decimals). 
   */

  
  Serial.println("\nExample 2:\n--------------------------------------\n");
  
    Serial.println("\n\nReading Variable from EEPROM as a <float> starting at reg 0: ");
    float newFloat;
    pb.readMemVar(reg, newFloat);
    Serial.println(newFloat);
  
  /*
   * That was easy as pi. Using the "readMemVar()" function lets you
   * automatically translate the raw data to the correct type.
   * 
   * Notice how we created a float called "newFloat"?
   * When we used readMemVar(reg, newFloat) we took the
   * data that started at register reg, interpreted it
   * as a float, and stored the value in newFloat.
   * 
   * This works for all data types defined in Arduino.
   * 
   * What if you want to save your variable without having
   * to translate it into individual bytes? Sounds like a
   * hassle. Does the TSLPB library have a simple function
   * to take care of the dirty work for me?
   */

  Serial.println("\n\nExample 3:\n--------------------------------------\n");
    
    Serial.println("\nSaving <float> e to eeprom, starting at reg 4");
    float e = 2.718281828459045235;
    pb.writeMemVar(e, 4);

  /*
   * Using writeMemVar() makes it a breeze. The library handles all
   * the type issues. All you have to do is tell it what register to
   * start saving in.
   * 
   * You're probably wondering what that crazy number looks like
   * in the EEPROM. Let's see:
   */  

    printRegFromTo(4, 7);

  /*
   * So can we read this new value from the EEPROM with readMemVar() ?
   *
   * Naturally!
   */

  Serial.println("\n\nExample 4:\n--------------------------------------\n");
    pb.readMemVar(4, newFloat);
    Serial.print("We read ");
    Serial.print(newFloat);
    Serial.println(" starting at register 4");
  
  
//  pb.writeMemVar(pi, reg);

  Serial.print("Reading hex from EEPROM: ");
  for (int i = 0; i < sizeof(e); i++) {
    Serial.print(pb.getMemByte(reg + i), HEX);
  }

  Serial.println("\n\nReading Variable from EEPROM as a <float>: ");
  newFloat;
  pb.readMemVar(reg, newFloat);
  Serial.println(newFloat);

  printRegFromTo(0, 15);
  
  do {
      delay(10000);
  } while (true);
  
}




/*  ┌──────────────────────────────────────────────────┐
 *  │     Simple function to print EEPROM contents     │
 *  └──────────────────────────────────────────────────┘ */

void printRegFromTo(int from, int to){
  byte contents;
  for (word reg = from; reg <= to; ++reg)
  {
      contents = pb.getMemByte(reg);
      Serial.print("Reg\t");
      Serial.print(reg);
      Serial.print("\t contains: ");
      Serial.println(contents, HEX);
  }
}
