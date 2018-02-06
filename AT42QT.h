#ifndef _AT42QT_H_
#define _AT42QT_H_

#include <Arduino.h>

#ifdef _WIREBASE_H_
#include <SoftWire.h>
#else
#include <Wire.h>
#endif

#include "AT42QT_API.h"

#define QT_DEBUG Serial
#define DBG "[DBG] "

/*============================================================================
Macros
============================================================================*/


#if (QT_DEVICE == QT60240)
#define WRITE_UNLOCK  0x55 // write unlock data
#endif

#define PIN_UNCONNECTED        255

class AT42QT {
  
  private: //-------------------------------------------------------

  uint8_t GetCommsReady(void);
  
  uint8_t write(uint8_t regAddr, uint8_t* dataPtr = 0, uint8_t dataSize = 0);
  uint8_t read(uint8_t regAddr, uint8_t* dataPtr, uint8_t dataSize);
  
#ifdef QT_DEBUG
  void print(const char* str, uint8_t* valuePtr=0, uint8_t size=0);
  void print(const char* str, uint8_t value);
#endif

  uint8_t QtStatus[QT_STATUS_SIZE]; // application storage for QT device-status
  
  SetupBlock setup_block; // Setup block structure

  uint8_t addr = QT_I2C_ADDRESS;
  uint8_t reset_pin = PIN_UNCONNECTED;
  
  #ifdef _WIREBASE_H_
  WireBase* wire;
  #else
  TwoWire* wire;
  #endif
  
  public: //--------------------------------------------------------
  
  AT42QT();
  
  #ifdef _WIREBASE_H_
  AT42QT(WireBase* _wire);
  #endif
  
  uint8_t begin();
  uint8_t begin(uint8_t _addr, uint8_t _reset_pin=PIN_UNCONNECTED);
  
  uint8_t init();
  
  void    hardReset();
  
  uint8_t calibrate();
  uint8_t reset();
  
  uint8_t writeReg(uint8_t regAddr, uint8_t value);
  uint8_t readReg(uint8_t regAddr);
  
  uint8_t readSetup();
  uint8_t writeSetup();
  
  uint8_t readStatus(void);
  
  void    printSetup();
  void    printStatus();
      
  void    pwm(uint8_t gpio, uint8_t pwm);
  
  void    setGPIO(uint8_t state);
  uint8_t getGPIO();
  
  void    setPWM(uint8_t pwmLevel);

  void    IRQ_handler(void);
  
  void    setSlider(uint8_t lenght, uint8_t hyst=0, uint8_t res=6);
  
  void    setKeyCC(uint8_t num, uint8_t value);
  void    setKeyBL(uint8_t num, uint8_t value);
  void    setKeyAKS(uint8_t num, uint8_t value);
  void    setKeyNTHR(uint8_t num, uint8_t value);
  
  void    setKeyCC(uint8_t numFrom, uint8_t numTo, uint8_t value);
  void    setKeyBL(uint8_t numFrom, uint8_t numTo, uint8_t value);
  void    setKeyAKS(uint8_t numFrom, uint8_t numTo, uint8_t value);
  void    setKeyNTHR(uint8_t numFrom, uint8_t numTo, uint8_t value);
  
  uint8_t getKey(uint8_t num);
  uint16_t getKeyMask(void);
  
  
  /*
  
  void writeKeyBL(uint8_t num, uint8_t value);
  void writeKeyBL(uint8_t numFrom, uint8_t numTo, uint8_t value);
  void writeKeyAKS(uint8_t num, uint8_t value);
  void writeKeyAKS(uint8_t numFrom, uint8_t numTo, uint8_t value);
  void writeKeyNTHR(uint8_t num, uint8_t value);
  void writeKeyNTHR(uint8_t numFrom, uint8_t numTo, uint8_t value);
  
  uint8_t readKeyBL(uint8_t num);
  */
};

#endif // _AT42QT_H_

