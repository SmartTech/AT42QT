#include <AT42QT.h>

#define TOUCH_ADDR      0x10
#define TOUCH_IRQ_PIN    PA5
#define TOUCH_RTS_PIN    PA6

/* I2C interface ===================================== */
//HardWire I2C_WIRE(1, I2C_FAST_MODE); // Hardware I2C class
//TwoWire I2C_WIRE(PB6, PB7, SOFT_FAST); // Software I2C class

AT42QT touch();
//AT42QT touch(&Wire);
//AT42QT touch(&I2C_WIRE);

/* Interrupt flags ------------------------------------*/
uint8_t TOUCH_INT_flag = false;

/* Interrupt routing ================================= */
void TOUCH_interrupt() { TOUCH_INT_flag = true; }

void setup() {
	
  Serial.begin();
  
  pinMode(TOUCH_IRQ_PIN, INPUT_PULLUP);
  
  // AT42QT initialization ------------------------
  touch.begin();
  //touch.begin(TOUCH_ADDR);
  //touch.begin(TOUCH_ADDR, TOUCH_RTS_PIN);
  
  attachInterrupt(TOUCH_IRQ_PIN, TOUCH_interrupt, CHANGE);
  
  // ------------------------
}

void loop() {
	
  if(TOUCH_INT_flag) {
    Serial.println("Is Touch interrupt");
    touch.IRQ_handler();
    TOUCH_INT_flag = false;
  }

}
