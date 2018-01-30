#include "AT42QT.h"

/*============================================================================
Name    :  AT42QT
------------------------------------------------------------------------------
Purpose : class constructor
============================================================================*/
AT42QT::AT42QT() :
	wire(&Wire)
{
  
}

#ifdef _WIREBASE_H_
AT42QT::AT42QT(WireBase* _wire) :
	wire(_wire)
{
	
}
#endif

/*============================================================================
Name    : begin
------------------------------------------------------------------------------
Purpose : initialize AT42QT with default address and no reset
============================================================================*/
uint8_t AT42QT::begin() {
  wire->begin();
  if(reset_pin != PIN_UNCONNECTED) {
    pinMode(reset_pin, OUTPUT);
    digitalWrite(reset_pin, HIGH);
  }
  // Reset QT device
  reset();
  // Check communication is ready and able to read Chip ID
  if(!GetCommsReady()) {
	  Serial.println("GetCommsReady error");
	  return false;
  }
  // Read setup block
  if(!ReadSetupBlock(sizeof(setup_block), (uint8_t *)&setup_block)) {
	  Serial.println("ReadSetupBlock error");
	  return false;
  }
  /* TO DO : modify setup block parameters here
   * from default valus if required 
   * For example: To set NTHR for Key 0 to 20
   * setup_block.key0_NTHR = 20; 
   */
  // Write setup block
  return WriteSetupBlock(sizeof(setup_block),(uint8_t *)&setup_block);
}

/*============================================================================
Name    :  extended begin
------------------------------------------------------------------------------
Purpose : initialize AT42QT with address and reset
============================================================================*/
uint8_t AT42QT::begin(uint8_t _addr, uint8_t _reset_pin) {
  addr = _addr;
  reset_pin = _reset_pin;
  return begin();
}

/*============================================================================
Name    :   IRQ_handler
------------------------------------------------------------------------------
Purpose : External Interrupt from AT42QT
============================================================================*/
void AT42QT::IRQ_handler(void) {
  // read all status-bytes
  ReadKeyStatus(sizeof(QtStatus), QtStatus);
  // TO DO : process the received data here...
}

/*============================================================================
Name    :   WriteSetupBlock
------------------------------------------------------------------------------
Purpose : write entire setup block to QT-device
Input   : WriteLength : Number of bytes to write
WritePtr: Pointer to byte array containing write-data
Return  : TRUE if write successful, else FALSE
============================================================================*/
uint8_t AT42QT::WriteSetupBlock(uint8_t WriteLength, uint8_t *WritePtr) {
  uint8_t error;
#if (QT_DEVICE == QT60240)  
  wire->beginTransmission(addr);
  wire->write(QT_SETUPS_WRITE_UNLOCK);
  wire->write(WRITE_UNLOCK);
  error = wire->endTransmission();
#endif
  wire->beginTransmission(addr);
  wire->write(QT_SETUPS_BLOCK_ADDR);
  wire->write(WritePtr, WriteLength);
  error = wire->endTransmission();
  return false;
}

/*============================================================================
Name    :   ReadSetupBlock
------------------------------------------------------------------------------
Purpose : Read entire setup block from QT-device
Input   : ReadLength  : Number of bytes to read
ReadPtr : Pointer to byte array for read-data
Return  : TRUE if read successful, else FALSE
============================================================================*/
uint8_t AT42QT::ReadSetupBlock(uint8_t ReadLength, uint8_t *ReadPtr) {
  uint8_t error;
  wire->beginTransmission(addr);
  wire->write(QT_SETUPS_BLOCK_ADDR);
  error = wire->endTransmission();
  if(error) {
	  Serial.print("ReadSetupBlock addr ");
	  Serial.print(addr);
	  Serial.print(" error ");
	  Serial.println(error);
	  return false;
  }
  wire->requestFrom(addr, ReadLength);
  uint8_t result_lenght = 0;
  while(wire->available()) {
    ReadPtr[result_lenght++] = wire->read();
  }
  return result_lenght;
}

/*============================================================================
Name    :   ReadKeyStatus
------------------------------------------------------------------------------
Purpose : Read detection status of all keys
Input   : ReadLength  : Number of bytes to read
ReadPtr : Pointer to byte array for read-data
Return  : TRUE if read successful, else FALSE
============================================================================*/
uint8_t AT42QT::ReadKeyStatus(uint8_t ReadLength, uint8_t *ReadPtr) {
  uint8_t error;
  wire->beginTransmission(addr);
  wire->write(QT_STATUS_ADDR);
  error = wire->endTransmission();
  if(error) return false;
  wire->requestFrom(addr, ReadLength);
  static uint8_t result_lenght = 0;
  while(wire->available()) {
    ReadPtr[result_lenght++] = wire->read();
  }
  return result_lenght;
}

/*============================================================================
Name    :   GetCommsReady
------------------------------------------------------------------------------
Purpose :   Check communication is ready and able to read Chip ID
============================================================================*/
uint8_t AT42QT::GetCommsReady(void) {
  uint8_t error;
  uint8_t chip_id;
  wire->beginTransmission(addr);
  wire->write(QT_CHIP_ID);
  error = wire->endTransmission();
  if(error) {
	  Serial.print("GetCommsReady addr ");
	  Serial.print(addr);
	  Serial.print(" error ");
	  Serial.println(error);
	  return false;
  }
  wire->requestFrom(addr, 1);
  while(wire->available()) chip_id = wire->read();
  int a = chip_id, b = QT_DEVICE_ID;
  Serial.print("ChipID: ");
  Serial.print(a);
  Serial.print(" QT_DEVICE_ID: ");
  Serial.print(b);
  Serial.print(" is ");
  if(a == b) Serial.println(1);
  else Serial.println(0);
  return true;
}

/*============================================================================
Name    :   ResetQT
------------------------------------------------------------------------------
Purpose :   Performs a hardware reset of the QT device
============================================================================*/
void AT42QT::reset(void) {
  if(reset_pin == PIN_UNCONNECTED) return;
  digitalWrite(reset_pin, LOW);
  delay(1);
  digitalWrite(reset_pin, HIGH);
}

