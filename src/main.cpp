#include <Arduino.h>
// #include "Adafruit_FRAM_I2C.h"
#include <CircularFRAM.h>

// Adafruit_FRAM_I2C fram     = Adafruit_FRAM_I2C();

// #define memSize           0x20
#define fram_add          0x54
// #define config_add        0x00
// #define nanoConfig_add    0x40
// #define memConfig_add     0x80
// #define data_add          0x300

CircularFRAM cfram = CircularFRAM();

// put function declarations here:
// int i2cAdd(int);
// int numberNanos();
// int sumAdd(int);
// int readHead();
// void writeHead(int);
// int readTail();
// void writeTail(int);
// uint8_t readFlag();
// void writeFlag(uint8_t);
// uint8_t checkWrite(int);
// template <typename T>
// uint8_t writeData(int, T);


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

// //-------------Nano config management
// int numberNanos(){
//   int number_nanos = fram.read(config_add + 0x6);
//   return number_nanos;
// }

// int i2cAdd(int nano){
//   int add = nanoConfig_add + (6*(nano-1)) + 0x5;
//   int i2c_add = fram.read(add);
//   return i2c_add;
// }
// //-------------Move ptr to next address
// int sumAdd(int add){
//   add = ((add + 4) % memSize);
//   return add;
// }
// //-------------Head pointer management
// int readHead(){
//   uint8_t buffer[4];  //
//   int head;
//   fram.read(memConfig_add + 1, buffer, 4); //head
//   memcpy((void *)&head, buffer, 4);
//   return head;
// }
// void writeHead(int head){
//   uint8_t buffer[4];  //
//   head = (head % memSize);
//   memcpy(buffer, (void *)&head, 4);
//   fram.write(memConfig_add + 1, buffer, 4); //head
// }
// //-------------Tail pointer management
// int readTail(){
//   uint8_t buffer[4];  //
//   int tail;
//   fram.read(memConfig_add + 5, buffer, 4); //tail
//   memcpy((void *)&tail, buffer, 4);
//   return tail;
// }
// void writeTail(int tail){
//   uint8_t buffer[4];  //
//   memcpy(buffer, (void *)&tail, 4);
//   fram.write(memConfig_add + 1, buffer, 4); //head
// }
// //-------------Read Write Flag management
// uint8_t readFlag(){
//   uint8_t flag = fram.read(memConfig_add);
//   return flag;
// }
// void writeFlag(uint8_t rw_flag){
//   // Serial.println(rw_flag);
//   uint8_t flag = fram.read(memConfig_add);
//   // Serial.println(flag);
//   if (rw_flag != flag){
//     fram.write(memConfig_add, rw_flag);     //RW-falg
//     // Serial.println("edited");
//   }
// }
// //-------------Write data procedure
// uint8_t checkWrite(int hd){
//   uint8_t rw = readFlag();
//   int tl = readTail();
//   // Serial.print("head : ");
//   // Serial.println(hd);
//   // Serial.print("tail : ");
//   // Serial.println(tl);
//   if ((hd == tl) && rw == 1){
//     // Serial.println("you shall not write");
//     return 0;
//   }
//   // Serial.println("you are able to write");
//   return 1;
// }

// template <typename T>
// uint8_t writeData(int add, T data){
//  /* Serial.print("data to store : ");
//   Serial.print(data, 10);
//   Serial.print(" |hex : ");
//   Serial.println(data, HEX);*/
//   uint8_t cont = 0;
//   add = (add % 64) + 768;
//   uint8_t buffer[4];  
//   memcpy(buffer, (void *) &data, 4);
//   while(!cont){
//     // Serial.println("storing data");
//     cont = fram.write(add, buffer, 4);
//     delay(5);
//   }
//   // Serial.println("data stored");
//   return cont;
// }


// // RAM:   [===       ]  28.7% (used 588 bytes from 2048 bytes)
// // Flash: [==        ]  21.2% (used 6506 bytes from 30720 bytes)
// // RAM:   [===       ]  25.9% (used 530 bytes from 2048 bytes)
// // Flash: [==        ]  20.3% (used 6236 bytes from 30720 bytes)
// // RAM:   [===       ]  28.9% (used 592 bytes from 2048 bytes)
// // Flash: [==        ]  21.5% (used 6604 bytes from 30720 bytes)
// // // --------------Sin serial
// // RAM:   [==        ]  18.4% (used 376 bytes from 2048 bytes)
// // Flash: [==        ]  16.2% (used 4990 bytes from 30720 bytes)
// // RAM:   [==        ]  18.4% (used 376 bytes from 2048 bytes)
// // Flash: [==        ]  16.2% (used 4990 bytes from 30720 bytes)