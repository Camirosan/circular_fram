#include <Arduino.h>
#include <CircularFRAM.h>

#define fram_add          0x54

CircularFRAM cfram = CircularFRAM();

void setup() {
  Serial.begin(115200);
  //  if (fram.begin(fram_add)) {
  //   Serial.println("Found I2C FRAM");
  // } else {
  //   Serial.println("I2C FRAM not identified");
  // }
  cfram.setup(fram_add);
  // int head_add = readHead();
  int head_add = cfram.readHead();
  // Serial.print("1 - HEAD : ");
  // Serial.println(head_add);
  // head_add = sumAdd(head_add);
  // Serial.print("2 - HEAD : ");
  // Serial.println(head_add);
  // head_add = sumAdd(head_add);
  // Serial.print("3 - HEAD : ");
  // Serial.println(head_add);
  // writeHead(head_add);
  // writeHead(0);
  // writeTail(0);
  // uint8_t able = readFlag(); 
  // Serial.print("ABLE : ");
  // Serial.println(able);
  // writeFlag(1);
  // uint8_t cont = 0;
  // while(!cont){
  //   cont = checkWrite(head_add);
  //   head_add = sumAdd(head_add);
  // }
  // // checkWrite(head_add);
  cfram.writeFlag(0);
  for (int i = 0; i < 10; i++){
    if(cfram.checkWrite(head_add)){
      cfram.writeData(head_add, 0);
      cfram.writeFlag(1);
      head_add = cfram.sumAdd(head_add);
    }else{
      Serial.println("Memory full");
      break;
    }
  }
      cfram.writeHead(head_add);
}

void loop() {
}
