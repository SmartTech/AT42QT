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
	  return false;
  }
  // Read setup block
  if(!readSetup()) {
	  return false;
  }
  return true;
  //return WriteSetupBlock(sizeof(setup_block),(uint8_t *)&setup_block);
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
  static uint32_t lastTouchMillis = 0;
  //if(millis()-lastTouchMillis>50) {
	  readStatus();
	//  printStatus();
	//  lastTouchMillis = millis();
  //}
  // TO DO : process the received data here...
}


uint8_t AT42QT::write(uint8_t regAddr, uint8_t* dataPtr, uint8_t dataSize) {
	// Размер буфера I2C ограничен 32 байтами,
	// поэтому реализуем поочередную запись по 30 байт
	uint8_t error = 0;
    uint8_t counts = 0;
    uint8_t pointer = 0;
    uint8_t counter = 0;
    uint8_t bytesPerWrite = 30;
	if(!dataSize) {
		wire->beginTransmission(addr);
	    wire->write(regAddr);
	    error = wire->endTransmission();
		delay(1);
		return !error;
	}
    while(counts<dataSize) {
	    counts += bytesPerWrite;
		if(counts > dataSize) bytesPerWrite = dataSize - (bytesPerWrite*counter);
	    wire->beginTransmission(addr);
	    wire->write(regAddr + pointer);
	    wire->write(&dataPtr[pointer], bytesPerWrite);
	    error = wire->endTransmission();
		delay(1);
	    if(error) return false;
	    pointer += bytesPerWrite;
	    counter++;
	}
	return !error;
}

uint8_t AT42QT::read(uint8_t regAddr, uint8_t* dataPtr, uint8_t dataSize) {
	// Размер буфера I2C ограничен 32 байтами,
	// поэтому реализуем поочередное чтение по 30 байт
	uint8_t error = 0;
    uint8_t counts = 0;
    uint8_t pointer = 0;
    uint8_t counter = 0;
    uint8_t result_lenght = 0;
    uint8_t bytesPerRead = 30;
    while(counts<dataSize) {
	    counts += bytesPerRead;
		if(counts > dataSize) bytesPerRead = dataSize - (bytesPerRead*counter);
		if(!write(regAddr + pointer)) return false;
		wire->requestFrom(addr, bytesPerRead);
		while(wire->available()) {
		  dataPtr[result_lenght++] = wire->read();
		}
	    pointer += bytesPerRead;
	    counter++;
	}
    return result_lenght;
}

uint8_t AT42QT::writeReg(uint8_t regAddr, uint8_t value) {
	if(write(regAddr, &value, sizeof(value))) {
		if(regAddr >= QT_SETUPS_BLOCK_ADDR) {
			*((uint8_t*)(&setup_block)-QT_SETUPS_BLOCK_ADDR+regAddr) = value;
		}
		return true;
	}
	return false;
}

uint8_t AT42QT::readReg(uint8_t regAddr) {
	uint8_t value = 0;
	if(read(regAddr, &value, sizeof(value))) {
		if(regAddr >= QT_SETUPS_BLOCK_ADDR) {
			*((uint8_t*)(&setup_block)-QT_SETUPS_BLOCK_ADDR+regAddr) = value;
		}
	}
	return value;
}

uint8_t AT42QT::readSetup() {
	return read(QT_SETUPS_BLOCK_ADDR, (uint8_t *)&setup_block, sizeof(setup_block));
}

uint8_t AT42QT::writeSetup() {
#if (QT_DEVICE == QT60240)
	if(!writeReg(QT_SETUPS_WRITE_UNLOCK, WRITE_UNLOCK)) return false;
#endif
	return write(QT_SETUPS_BLOCK_ADDR, (uint8_t *)&setup_block, sizeof(setup_block));
}

#ifdef QT_DEBUG
void AT42QT::print(const char* str, uint8_t* valuePtr, uint8_t size) {
	QT_DEBUG.print(DBG); QT_DEBUG.print(str);
	if(size) QT_DEBUG.print(" :");
	for(uint8_t i=0; i<size; i++) {
		QT_DEBUG.print(" ");
		QT_DEBUG.print(*(valuePtr + i));
	} QT_DEBUG.println();
}

void AT42QT::print(const char* str, uint8_t value)  {
	print(str, &value, 1);
}
#endif

void AT42QT::printSetup() {
#ifdef QT_DEBUG
    print("QT setup block info:");
	
	print("LP_Mode    ", setup_block.LP_Mode);
	print("BREP       ", setup_block.BREP);
	print("NDRIFT     ", setup_block.NDRIFT);
	print("PDRIFT     ", setup_block.PDRIFT);
	print("NDIL       ", setup_block.NDIL);
	print("NRD        ", setup_block.NRD);
	print("DHT_AWAKE  ", setup_block.DHT_AWAKE);
	print("Slider_Keys", setup_block.Slider_Num_Keys);
	print("Slider_HYST", setup_block.Slider_HYST);
	print("Slider_Res ", setup_block.Slider_Resolution);
	
	print("Keys_AKS   ", &setup_block.Key0_AKS,  16);
	print("Keys_NTHR  ", &setup_block.Key0_NTHR, 16);
	print("Keys_BL    ", &setup_block.Key0_BL,   16);
	
	print("GPO_Drive1 ", setup_block.GPIO_GPO_Drive1);
	print("GPO_Drive2 ", setup_block.GPIO_GPO_Drive2);
	print("GPIO_Dir   ", setup_block.GPIO_Direction);
	print("GPO_PWM1   ", setup_block.GPIO_GPO_PWM1);
	print("GPO_PWM2   ", setup_block.GPIO_GPO_PWM2);
	print("PWM_level  ", setup_block.PWM_level);
	print("GPIO_Wake  ", setup_block.GPIO_Wake);
	print("CC_Keys1   ", setup_block.CC_Keys1);
	print("CC_Keys2   ", setup_block.CC_Keys2);
		
    print("QT setup block end");
#endif
}

void AT42QT::printStatus() {
#ifdef QT_DEBUG
    print("QT status info:");
	print("QT_GENERAL_STATUS ", QtStatus[0]);
	print("QT_KEY_STATUS_1   ", QtStatus[1]);
	print("QT_KEY_STATUS_2   ", QtStatus[2]);
	print("QT_SLIDER_POSITION", QtStatus[3]);
	print("QT_GPIO_READ      ", QtStatus[4]);
    print("QT status end");
#endif
}

/*============================================================================
Name    :   GetCommsReady
------------------------------------------------------------------------------
Purpose :   Check communication is ready and able to read Chip ID
============================================================================*/
uint8_t AT42QT::GetCommsReady(void) {
	return (readReg(QT_CHIP_ID)==QT_DEVICE_ID);
}

uint8_t AT42QT::readStatus(void) {
  return read(QT_STATUS_ADDR, QtStatus, sizeof(QtStatus));
}

/*============================================================================
Name    :   ResetQT
------------------------------------------------------------------------------
Purpose :   Performs a software reset of the QT device
============================================================================*/
uint8_t AT42QT::reset(void)  {
	if(writeReg(QT_RESET, 1)) return true;
	return false;
}

/*============================================================================
Name    :   HardResetQT
------------------------------------------------------------------------------
Purpose :   Performs a hardware reset of the QT device
============================================================================*/
void AT42QT::hardReset(void) {
  if(reset_pin == PIN_UNCONNECTED) return;
  digitalWrite(reset_pin, LOW);
  delay(1);
  digitalWrite(reset_pin, HIGH);
}

/*============================================================================
Name    :   CalibrateQT
------------------------------------------------------------------------------
Purpose :   Performs a calibration of the QT device
============================================================================*/
uint8_t AT42QT::calibrate() {
	if(writeReg(QT_CALIBRATE, 1)) return true;
	return false;
}

uint8_t AT42QT::init() {
	return writeSetup();
}

void AT42QT::setSlider(uint8_t lenght, uint8_t hyst, uint8_t res) {
	setup_block.Slider_Num_Keys = constrain(lenght, 0, 8);
	setup_block.Slider_HYST = constrain(hyst, 0, 15);
	setup_block.Slider_Resolution = constrain(res, 0, 6);
}

void AT42QT::setKeyBL(uint8_t num, uint8_t value) {
	if(num < 16) num += QT_KEY0_BL;
	if(num < QT_KEY0_BL || num > QT_KEY15_BL) return;
	*((uint8_t*)(&setup_block)-QT_SETUPS_BLOCK_ADDR+num) = value;
}

void AT42QT::setKeyAKS(uint8_t num, uint8_t value) {
	if(num < 16) num += QT_KEY0_AKS_GRP;
	if(num < QT_KEY0_AKS_GRP || num > QT_KEY15_AKS_GRP) return;
	*((uint8_t*)(&setup_block)-QT_SETUPS_BLOCK_ADDR+num) = constrain(value, 0, 3);
}

void AT42QT::setKeyNTHR(uint8_t num, uint8_t value) {
	if(num < 16) num += QT_KEY0_NTHR;
	if(num < QT_KEY0_NTHR || num > QT_KEY15_NTHR) return;
	*((uint8_t*)(&setup_block)-QT_SETUPS_BLOCK_ADDR+num) = constrain(value, 1, 255);
}

void AT42QT::setKeyCC(uint8_t num, uint8_t value) {
	if(num>15) return;
	if(value>1) value = 1;
	if(num<8) bitWrite(setup_block.CC_Keys1, num,   value);
	else      bitWrite(setup_block.CC_Keys2, num-8, value);
}

void AT42QT::setKeyBL(uint8_t numFrom, uint8_t numTo, uint8_t value) {
	if(numTo < numFrom) numTo = numFrom;
	for(uint8_t i=numFrom; i<=numTo; i++) setKeyBL(i, value);
}

void AT42QT::setKeyAKS(uint8_t numFrom, uint8_t numTo, uint8_t value) {
	if(numTo < numFrom) numTo = numFrom;
	for(uint8_t i=numFrom; i<=numTo; i++) setKeyAKS(i, value);
}

void AT42QT::setKeyNTHR(uint8_t numFrom, uint8_t numTo, uint8_t value) {
	if(numTo < numFrom) numTo = numFrom;
	for(uint8_t i=numFrom; i<=numTo; i++) setKeyNTHR(i, value);
}

void AT42QT::setKeyCC(uint8_t numFrom, uint8_t numTo, uint8_t value) {
	if(numTo < numFrom) numTo = numFrom;
	for(uint8_t i=numFrom; i<=numTo; i++) setKeyCC(i, value);
}

uint8_t AT42QT::getKey(uint8_t num) {
	if(num>15) return 0;
	     if(num < 8)  return bitRead(QtStatus[1], num);
	else if(num < 16) return bitRead(QtStatus[2], num-8);
	else return 0;
}

uint16_t AT42QT::getKeyMask() {
	uint16_t value = QtStatus[2];
	value <<= 8;
	value |= QtStatus[1];
	return value;
}

// -------------------------------------------------------------------
/*
uint8_t AT42QT::readKeyBL(uint8_t num) {
	if(num < 16) num += QT_KEY0_BL;
	if(num < QT_KEY0_BL || num > QT_KEY15_BL) return;
	
    ReadKeyStatus(1, (uint8_t *) setup_block.key0_BL);
}





void AT42QT::writeKeyBL(uint8_t num, uint8_t value) {
	writeKeyBL(num, num, value);
}

void AT42QT::writeKeyBL(uint8_t numFrom, uint8_t numTo, uint8_t value) {
	if(numTo < numFrom) numTo = numFrom;
	setKeyBL(numFrom, numTo, value);
	WriteSetupBlock(numTo-numFrom+1, (uint8_t *)&setup_block.key0_BL);
}

// -------------------------------------------------------------------





void AT42QT::writeKeyAKS(uint8_t num, uint8_t value) {
	writeKeyAKS(num, num, value);
}

void AT42QT::writeKeyAKS(uint8_t numFrom, uint8_t numTo, uint8_t value) {
	if(numTo < numFrom) numTo = numFrom;
	setKeyAKS(numFrom, numTo, value);
	WriteSetupBlock(numTo-numFrom+1, (uint8_t *)&setup_block.Key0_AKS);
}

// -------------------------------------------------------------------



void AT42QT::writeKeyNTHR(uint8_t num, uint8_t value) {
	writeKeyNTHR(num, num, value);
}

void AT42QT::writeKeyNTHR(uint8_t numFrom, uint8_t numTo, uint8_t value) {
	if(numTo < numFrom) numTo = numFrom;
	setKeyNTHR(numFrom, numTo, value);
	WriteSetupBlock(numTo-numFrom+1, (uint8_t *)&setup_block.key0_NTHR);
}

// -------------------------------------------------------------------
*/


void AT42QT::pwm(uint8_t gpio, uint8_t pwm) {
		 if(!pwm)     setup_block.PWM_level = 255;
	else if(pwm==255) setup_block.PWM_level = 0;
	else setup_block.PWM_level = map(pwm, 1, 254, 11, 249);
}

void AT42QT::setGPIO(uint8_t state) {
	
}

uint8_t AT42QT::getGPIO() {
	
}

void AT42QT::setPWM(uint8_t pwmLevel) {
	
}
