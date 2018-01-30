#ifndef _AT42QT_H_
#define _AT42QT_H_

#include <Arduino.h>
#include <Wire.h>

#ifdef _WIREBASE_H_
#include <SoftWire.h>
#endif

#include "AT42QT_API.h"

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
  
  uint8_t WriteSetupBlock(uint8_t WriteLength, uint8_t *WritePtr);
  uint8_t ReadSetupBlock(uint8_t ReadLength, uint8_t *ReadPtr);
  uint8_t ReadKeyStatus(uint8_t ReadLength, uint8_t *ReadPtr);

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
  
  void    reset(void);

  void    IRQ_handler(void);
  
};

#endif // _AT42QT_H_

