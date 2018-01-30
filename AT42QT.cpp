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
	// Reset QT device
	reset();
  }
  
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
  Serial.println("LP_mode:           " + String(setup_block.LP_Mode));
  Serial.println("BREP:              " + String(setup_block.BREP));
  Serial.println("NDRIFT:            " + String(setup_block.NDRIFT));
  Serial.println("PDRIFT:            " + String(setup_block.PDRIFT));
  Serial.println("NDIL:              " + String(setup_block.NDIL));
  Serial.println("NRD:               " + String(setup_block.NRD));
  Serial.println("DHT_AWAKE:         " + String(setup_block.DHT_AWAKE));
  Serial.println("Slider_Num_Keys:   " + String(setup_block.Slider_Num_Keys));
  Serial.println("Slider_HYST:       " + String(setup_block.Slider_HYST));
  Serial.println("Slider_Resolution: " + String(setup_block.Slider_Resolution));
  /* TO DO : modify setup block parameters here
   * from default valus if required 
   * For example: To set NTHR for Key 0 to 20
   * setup_block.key0_NTHR = 20; 
   */
  // Write setup block
  setup_block.LP_Mode = 1;
  setup_block.Slider_Num_Keys = 6;
  setup_block.Slider_HYST = 6;
  setup_block.Slider_Resolution = 6;
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
  Serial.print("ReadKeyStatus: ");
  Serial.println(ReadKeyStatus(sizeof(QtStatus), QtStatus));
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
  delay(1);
#endif
  // Не хватает буфера чтоб послать сразу 68 байт,
  // поэтому отправляем по 30 байт
  uint8_t bytesPerWrite = 30;
  uint8_t counts = 0;
  uint8_t pointer = 0;
  uint8_t counter = 0;
  Serial.println();
  while(counts<WriteLength) {
	  counts += bytesPerWrite;
	  if(counts > WriteLength) bytesPerWrite = WriteLength - (bytesPerWrite*counter);
	  wire->beginTransmission(addr);
	  wire->write(QT_SETUPS_BLOCK_ADDR + pointer);
	  wire->write(&WritePtr[pointer], bytesPerWrite);
	  error = wire->endTransmission();
	  if(error) return false;
	  pointer += bytesPerWrite;
	  counter++;
	  delay(1);
  }
  return true;
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
  delay(1);
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
  delay(1);
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
  uint8_t chip_id = 0;
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
  delay(1);
  wire->requestFrom(addr, 1);
  while(wire->available()) chip_id = wire->read();
  return (chip_id == QT_DEVICE_ID);
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

