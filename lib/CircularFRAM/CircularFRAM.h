#ifndef _CIRCULARFRAM_H
#define _CIRCULARFRAM_H

#include <Arduino.h>
#include "Adafruit_FRAM_I2C.h"

class CircularFRAM
{
    Adafruit_FRAM_I2C fram = Adafruit_FRAM_I2C();
private:
    #define memSize           0x20
    // #define fram_add          0x54
    #define config_add        0x00
    #define nanoConfig_add    0x40
    #define memConfig_add     0x80
    #define data_add          0x300
public:
    CircularFRAM();
    ~CircularFRAM();
    void setup(uint8_t fram_add);
    int numberNanos();
    int i2cAdd(int nano);
    int sumAdd(int add);
    int readHead();
    void writeHead(int head);
    int readTail();
    void writeTail(int tail);
    uint8_t readFlag();
    void writeFlag(uint8_t rw_flag);
    uint8_t checkWrite(int head);
    //-------------------------------------
    template <typename T>
    uint8_t writeData(int add, T data) {
        uint8_t cont = 0;
        add = (add % 64) + 768;
        uint8_t buffer[4];  
        memcpy(buffer, (void *) &data, 4);
        while(!cont){
            cont = fram.write(add, buffer, 4);
            delay(5);
        }
        return cont;
    }
    // uint8_t writeData(int add, T data);
    //-------------------------------------
};

#endif