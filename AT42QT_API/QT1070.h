/*******************************************************************************
*   $FILE:  QT1070.h
*   Brief: Header file for the AT42QT1070 device and it consists AT42QT1070 
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

#ifndef _QT1070_H_
#define _QT1070_H_

/*============================================================================
Macros
============================================================================*/

// Chip ID (read from device-address 0)
#define QT_DEVICE_ID	0x2E

// I2C address	
#define I2C_ADDRESS		0x1B	

// Setup block start address
#define QT_SETUPS_BLOCK_ADDR	32

// detection status and key status start address
#define QT_STATUS_ADDR	2

/* 
application storage for QT1070 device-status

QtStatus[0] - Detection Status 
				Bit0 - TOUCH : This bit is set if any keys are in detect.
				Bit6 - OVERFLOW : This bit is set if the time to acquire all 
                key signals exceeds 8ms
				bit7 - CALIBRATE : This bit is set during a calibrate sequence
				
QtStatus[1] - Key Status 
				bits 0 - 6 : Indicates which keys are in detection 
                  (Touched keys report as 1) 
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

enum { // QT1070 registers
	QT_CHIP_ID = 0,
	QT_FIRMWARE_VERSION,
	QT_DETECTION_STATUS,
	QT_KEY_STATUS,
	QT_KEY0_SIGNAL,
	QT_KEY1_SIGNAL = 6,
	QT_KEY2_SIGNAL = 8,
	QT_KEY3_SIGNAL = 10,
	QT_KEY4_SIGNAL = 12,
	QT_KEY5_SIGNAL = 14,
	QT_KEY6_SIGNAL = 16,
	QT_KEY0_REFERENCE = 18,
	QT_KEY1_REFERENCE = 20,
	QT_KEY2_REFERENCE = 22,
	QT_KEY3_REFERENCE = 24,
	QT_KEY4_REFERENCE = 26,
	QT_KEY5_REFERENCE = 28,
	QT_KEY6_REFERENCE = 30,
	QT_KEY0_NTHR = 32,
	QT_KEY1_NTHR,
	QT_KEY2_NTHR,
	QT_KEY3_NTHR,
	QT_KEY4_NTHR,
	QT_KEY5_NTHR,
	QT_KEY6_NTHR,
	QT_KEY0__AVE_AKS = 39,
	QT_KEY1_AVE_AKS,
	QT_KEY2_AVE_AKS,
	QT_KEY3_AVE_AKS,
	QT_KEY4_AVE_AKS,
	QT_KEY5_AVE_AKS,
	QT_KEY6_AVE_AKS,
	QT_KEY0_DI = 46,
	QT_KEY1_DI,
	QT_KEY2_DI,
	QT_KEY3_DI,
	QT_KEY4_DI,
	QT_KEY5_DI,
	QT_KEY6_DI,
	QT_FO_MO_GDNO,
	QT_LP,
	QT_MAX_ON_DURATION,
	QT_CALIBRATE,
	QT_RESET,
};

/*============================================================================
Type definitions
============================================================================*/

typedef struct
{
	// Negative Threshold(NTHR)	
	uint8_t key0_NTHR;  // Key0 Negative Threshold
	uint8_t key1_NTHR;  // Key1 Negative Threshold
	uint8_t key2_NTHR;  // Key2 Negative Threshold	
	uint8_t key3_NTHR;  // Key3 Negative Threshold	
	uint8_t key4_NTHR;  // Key4 Negative Threshold	
	uint8_t key5_NTHR;  // Key5 Negative Threshold
	uint8_t key6_NTHR;  // Key6 Negative Threshold
	
	// Averaging factor(AVE)/Adjucent key suppression level(AKS)	
	uint8_t key0_AKS : 2;  // Key0 AKS group
	uint8_t key0_AVE : 6;  // Key0 AVE	
	uint8_t key1_AKS : 2;  // Key1 AKS group
	uint8_t key1_AVE : 6;  // Key1 AVE	
	uint8_t key2_AKS : 2;  // Key2 AKS group
	uint8_t key2_AVE : 6;  // Key2 AVE	
	uint8_t key3_AKS : 2;  // Key3 AKS group
	uint8_t key3_AVE : 6;  // Key3 AVE	
	uint8_t key4_AKS : 2;  // Key4 AKS group
	uint8_t key4_AVE : 6;  // Key4 AVE	
	uint8_t key5_AKS : 2;  // Key5 AKS group
	uint8_t key5_AVE : 6;  // Key5 AVE	
	uint8_t key6_AKS : 2;  // Key6 AKS group
	uint8_t key6_AVE : 6;  // Key6 AVE	
	
	// Detection Integrator(DI)	
	int8_t key0_DI;  // Key0 Detection Integrator counter
	int8_t key1_DI;  // Key1 Detection Integrator counter
	int8_t key2_DI;  // Key2 Detection Integrator counter
	int8_t key3_DI;  // Key3 Detection Integrator counter
	int8_t key4_DI;  // Key4 Detection Integrator counter
	int8_t key5_DI;  // Key5 Detection Integrator counter
	int8_t key6_DI;  // Key6 Detection Integrator counter
	
	// Fast out DI, max cal, Guard channel	
	uint8_t GUARD_CHANNEL : 4;  // Guard key no
	uint8_t MAX_CAL : 1;        // Max Cal
	uint8_t FO : 1;             // Fast Out DI
	uint8_t resvd : 2;          // unused bits	
	
	// 8ms intervals between key measurements	
	uint8_t LP_Mode;
	
	// Max On Duaration
	uint8_t Max_On_Dur;	
	
}SetupBlock;

/*============================================================================
External variables
============================================================================*/
extern SetupBlock setup_block;
extern uint8_t QtStatus[QT_STATUS_SIZE];			 				 
					 
#endif /* _QT1070_H_ */
/*============================================================================
  END OF FILE 
============================================================================*/						 
					 
