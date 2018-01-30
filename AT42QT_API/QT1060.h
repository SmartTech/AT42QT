/*******************************************************************************
*   $FILE:  QT1060.h
*   Brief: Header file for the AT42QT1060 device and it consists AT42QT1060 
*           Setup Block structure and address map enums
*   Atmel Corporation:  http:/www.atmel.com
*   Support email:  touch@atmel.com
******************************************************************************/
/*  License
*   Copyright (c) 2012, Atmel Corporation All rights reserved.
*
*   Redistribution and use in source and binary forms, with or without
*   modification, are permitted provided that the following conditions are met:
*
*   1. Redistributions of source code must retain the above copyright notice,
*   this list of conditions and the following disclaimer.
*
*   2. Redistributions in binary form must reproduce the above copyright notice,
*   this list of conditions and the following disclaimer in the documentation
*   and/or other materials provided with the distribution.
*
*   3. The name of ATMEL may not be used to endorse or promote products derived
*   from this software without specific prior written permission.
*
*   THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
*   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
*   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
*   SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
*   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
*   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
*   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
*   THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _QT1060_H_
#define _QT1060_H_

/*============================================================================
Macros
============================================================================*/

// Chip ID (read from device-address 0)
#define QT_DEVICE_ID	0x31

// I2C address
#define I2C_ADDRESS		0x12

// Setup block start address
#define QT_SETUPS_BLOCK_ADDR	14	

// Key detection status address
#define QT_STATUS_ADDR	0x04	

/* 
application storage for QT1060 device-status

QtStatus[0] - Detection Status 
        Bits 0 - 5 : Indicates which keys are in detection 
                      (Touched keys report as 1)				
        bit7 - CAL : This bit is set during a calibrate sequence
				
QtStatus[1] - Input Port Status 
		bits 0 - 6 : Indicates the state of IO that are configured as inputs.
*/				 

// QtStatus array size
#define QT_STATUS_SIZE	2

/*============================================================================
Enums
============================================================================*/
/* 
 * This address map can be used for read\write particular info from QT device
 * using the interfaces twi_read() or twi_write()
 */

enum { // QT1060 registers address
	QT_CHIP_ID = 0,
	QT_VERSION,
	QT_MINOR_VERSION,
	QT_DETECTION_STATUS = 4,
	QT_INPUT_PORT_STATUS,
	QT_CALIBRATE = 12,
	QT_RESET,
	QT_DRIFT_OPTION,
	QT_POSITIVE_RECAL_DELAY,
	QT_KEY0_NTHR,
	QT_KEY1_NTHR,
	QT_KEY2_NTHR,
	QT_KEY3_NTHR,
	QT_KEY4_NTHR,
	QT_KEY5_NTHR,
	QT_LP,
	QT_IO_MASK,
	QT_KEY_MASK,
	QT_AKS_MASK,
	QT_PWM_MASK,
	QT_DETECTION_MASK,
	QT_ACTIVE_LEVEL_MASK,
	QT_USER_OUTPUT_BUFFER,
	QT_DI,
	QT_PWM_LEVEL,	
	QT_KEY0_SIGNAL = 40,
	QT_KEY1_SIGNAL = 42,
	QT_KEY2_SIGNAL = 44,
	QT_KEY3_SIGNAL = 46,
	QT_KEY4_SIGNAL = 48,
	QT_KEY5_SIGNAL = 50,
	QT_KEY0_REFERENCE = 52,
	QT_KEY1_REFERENCE = 54,
	QT_KEY2_REFERENCE = 56,
	QT_KEY3_REFERENCE = 58,
	QT_KEY4_REFERENCE = 60,
	QT_KEY5_REFERENCE = 62
};

/*============================================================================
Type definitions
============================================================================*/

typedef struct
{
	// Drift option
	uint8_t drift_option;
	
	// Positive recalibration delay
	uint8_t positive_recal_delay; 
	
	// Negative Threshold (NTHR)	
	uint8_t key0_NTHR;   // Key0 Negative Threshold
	uint8_t key1_NTHR;   // Key1 Negative Threshold
	uint8_t key2_NTHR;   // Key2 Negative Threshold	
	uint8_t key3_NTHR;   // Key3 Negative Threshold	
	uint8_t key4_NTHR;   // Key4 Negative Threshold	
	uint8_t key5_NTHR;   // Key5 Negative Threshold
	
	// 16ms intervals between key measurements	
	uint8_t LP_Mode;
	
	// IO pin direction control
	uint8_t IO_Mask;
	
	// Change pin transition control
	uint8_t Key_Mask;
	
	// AKS group control
	uint8_t AKS_Mask;
	
	// PWM signal control for IO pins which are configured as output
	uint8_t PWM_Mask;
	
	// IO pin control by their corresponding capacitive key
	uint8_t Detection_Mask;
	
	// IO pin level control
	uint8_t Active_Level_Mask;
	
	// User output level control
	uint8_t User_Output_Buffer;
	
	// Detection Integrater
	uint8_t DI;
		
	// PWM duty cycle control
	uint8_t PWM_level;	
	
}SetupBlock;

/*============================================================================
External variables
============================================================================*/
extern SetupBlock setup_block;
extern uint8_t QtStatus[QT_STATUS_SIZE];
					 
#endif /* _QT1060_H_ */
/*============================================================================
  END OF FILE 
============================================================================*/						 
					 
