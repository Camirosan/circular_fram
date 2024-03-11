#include <CircularFRAM.h>

// Adafruit_FRAM_I2C fram = Adafruit_FRAM_I2C();

CircularFRAM::CircularFRAM(){
}

CircularFRAM::~CircularFRAM(){
}

void CircularFRAM::setup(uint8_t fram_add){
    fram.begin(fram_add);
}

//-------------Nano config management
int CircularFRAM::numberNanos(){
  int number_nanos = fram.read(config_add + 0x6);
  return number_nanos;
}

int CircularFRAM::i2cAdd(int nano){
  int add = nanoConfig_add + (6*(nano-1)) + 0x5;
  int i2c_add = fram.read(add);
  return i2c_add;
}
//-------------Move ptr to next address
int CircularFRAM::sumAdd(int add){
  add = ((add + 4) % memSize);
  return add;
}
//-------------Head pointer management
int CircularFRAM::readHead(){
  uint8_t buffer[4];
  int head;
  fram.read(memConfig_add + 1, buffer, 4);
  memcpy((void *)&head, buffer, 4);
  return head;
}
void CircularFRAM::writeHead(int head){
  uint8_t buffer[4];  
  head = (head % memSize);
  memcpy(buffer, (void *)&head, 4);
  fram.write(memConfig_add + 1, buffer, 4);
}
//-------------Tail pointer management
int CircularFRAM::readTail(){
  uint8_t buffer[4];  
  int tail;
  fram.read(memConfig_add + 5, buffer, 4);
  memcpy((void *)&tail, buffer, 4);
  return tail;
}
void CircularFRAM::writeTail(int tail){
  uint8_t buffer[4];  
  memcpy(buffer, (void *)&tail, 4);
  fram.write(memConfig_add + 1, buffer, 4);
}
//-------------Read Write Flag management
uint8_t CircularFRAM::readFlag(){
  uint8_t flag = fram.read(memConfig_add);
  return flag;
}
void CircularFRAM::writeFlag(uint8_t rw_flag){
  uint8_t flag = fram.read(memConfig_add);
  if (rw_flag != flag){
    fram.write(memConfig_add, rw_flag);
  }
}
//-------------Write data procedure
uint8_t CircularFRAM::checkWrite(int head){
  uint8_t rw_flag = readFlag();
  int tail = readTail();
  if ((head == tail) && rw_flag == 1){
    return 0;
  }
  return 1;
}

// template <typename T>
// uint8_t CircularFRAM::writeData(int add, T data) {
//     uint8_t cont = 0;
//     add = (add % 64) + 768;
//     uint8_t buffer[4];  
//     memcpy(buffer, (void *) &data, 4);
//     while(!cont){
//         cont = fram.write(add, buffer, 4);
//         delay(5);
//     }
//     return cont;
// }