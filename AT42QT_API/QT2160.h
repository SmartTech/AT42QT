/*******************************************************************************
*   $FILE:  QT2160.h
*   Brief: Header file for the AT42QT2160 device and it consists AT42QT2160 
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

#ifndef _QT2160_H_
#define _QT2160_H_


/*============================================================================
Macros
============================================================================*/

// Chip ID (read from device-address 0)
#define QT_DEVICE_ID	0x11

// I2C address (I2CA1 = I2CA0 = 0)	
#define QT_I2C_ADDRESS  0x0D

// Setup block start address	
#define QT_SETUPS_BLOCK_ADDR	12

// Detection status and key status start address	
#define QT_STATUS_ADDR	2

/* 
application storage for QT2160 device-status

QtStatus[0] - General Status 
        Bit0 - SDET : This bit is set if a touch is detected on the slider.
        Bit1 - CC : This Common Change bit is set if all the selected 
            keys have a signal change of more than half the 
            detection threshold, NTHR.
        bit6 - CYCLE OVERRUN : This bit is set if the cycle time more than 16ms.
        bit7 - RESET : This bit is set after a reset
				
QtStatus[1] - Key Status 
		bits 0 - 7 : Detect status for keys 0 to 7 (Touched keys report as 1)
				
QtStatus[2] - Key Status 
		bits 0 - 7 : Detect status for keys 8 to 15 (Touched keys report as 1)

QtStatus[3] - Slider Touch Position 
		bits 0 - 7 : Last position of the touch on the slider

QtStatus[4] - GPIO Read
		bits 2 - 4 : indicates the state of GPIO1 to GPIO3  
                  that are configured as inputs 
*/	

// QtStatus array size
#define QT_STATUS_SIZE	5

/*============================================================================
Enums
============================================================================*/
/* 
 * This address map can be used for read\write particular info from QT device
 * using the interfaces twi_read() or twi_write()
 */

enum { // QT2160 registers
	QT_CHIP_ID = 0,
	QT_CODE_VERSION,
	QT_GENERAL_STATUS,
	QT_KEY_STATUS_1,
	QT_KEY_STATUS_2,
	QT_SLIDER_POSITION,
	QT_GPIO_READ,
	QT_CALIBRATE = 10,
	QT_RESET,
	QT_LP_MODE,
	QT_BREP,
	QT_NEG_DRIFT_COMP = 15,
	QT_POS_DRIFT_COMP,
	QT_DI_LIMIT,
	QT_NEG_RECAL_DELAY,
	QT_DRIFT_HOLD_TIME,
	QT_SLIDER_CONTROL,
	QT_SLIDER_OPTIONS,
	QT_KEY0_AKS_GRP,
	QT_KEY1_AKS_GRP,
	QT_KEY2_AKS_GRP,
	QT_KEY3_AKS_GRP,
	QT_KEY4_AKS_GRP,
	QT_KEY5_AKS_GRP,
	QT_KEY6_AKS_GRP,
	QT_KEY7_AKS_GRP,
	QT_KEY8_AKS_GRP,
	QT_KEY9_AKS_GRP,
	QT_KEY10_AKS_GRP,
	QT_KEY11_AKS_GRP,
	QT_KEY12_AKS_GRP,
	QT_KEY13_AKS_GRP,
	QT_KEY14_AKS_GRP,
	QT_KEY15_AKS_GRP,
	QT_KEY0_NTHR,
	QT_KEY1_NTHR,
	QT_KEY2_NTHR,
	QT_KEY3_NTHR,
	QT_KEY4_NTHR,
	QT_KEY5_NTHR,
	QT_KEY6_NTHR,
	QT_KEY7_NTHR,
	QT_KEY8_NTHR,
	QT_KEY9_NTHR,
	QT_KEY10_NTHR,
	QT_KEY11_NTHR,
	QT_KEY12_NTHR,
	QT_KEY13_NTHR,
	QT_KEY14_NTHR,
	QT_KEY15_NTHR,
	QT_KEY0_BL,
	QT_KEY1_BL,
	QT_KEY2_BL,
	QT_KEY3_BL,
	QT_KEY4_BL,
	QT_KEY5_BL,
	QT_KEY6_BL,
	QT_KEY7_BL,
	QT_KEY8_BL,
	QT_KEY9_BL,
	QT_KEY10_BL,
	QT_KEY11_BL,
	QT_KEY12_BL,
	QT_KEY13_BL,
	QT_KEY14_BL,
	QT_KEY15_BL,
	QT_GPO_DRIVE,
	QT_GPIO_DRIVE,
	QT_GPIO_DIR = 73,
	QT_GPO_PWM,
	QT_GPIO_PWM,
	QT_PWM_LEVEL,
	QT_GPIO_WAKE,
	QT_COMM_CHG_KEYS_1,
	QT_COMM_CHG_KEYS_2,
	QT_KEY0_SIGNAL = 100,
	QT_KEY1_SIGNAL = 102,
	QT_KEY2_SIGNAL = 104,
	QT_KEY3_SIGNAL = 106,
	QT_KEY4_SIGNAL = 108,
	QT_KEY5_SIGNAL = 110,
	QT_KEY6_SIGNAL = 112,
	QT_KEY7_SIGNAL = 114,
	QT_KEY8_SIGNAL = 116,
	QT_KEY9_SIGNAL = 118,
	QT_KEY10_SIGNAL = 120,
	QT_KEY11_SIGNAL = 122,
	QT_KEY12_SIGNAL = 124,
	QT_KEY13_SIGNAL = 126,
	QT_KEY14_SIGNAL = 128,
	QT_KEY15_SIGNAL = 130,		
	QT_KEY0_REFERENCE = 132,
	QT_KEY1_REFERENCE = 134,
	QT_KEY2_REFERENCE = 136,
	QT_KEY3_REFERENCE = 138,
	QT_KEY4_REFERENCE = 140,	
	QT_KEY5_REFERENCE = 142,
	QT_KEY6_REFERENCE = 144,	
	QT_KEY7_REFERENCE = 146,
	QT_KEY8_REFERENCE = 148,	
	QT_KEY9_REFERENCE = 150,
	QT_KEY10_REFERENCE = 152,	
	QT_KEY11_REFERENCE = 154,
	QT_KEY12_REFERENCE = 156,	
	QT_KEY13_REFERENCE = 158,
	QT_KEY14_REFERENCE = 160,	
	QT_KEY15_REFERENCE = 162,	
};

/*============================================================================
Type definitions
============================================================================*/

typedef struct
{
	// LP Mode
	uint8_t LP_Mode;
	
	// Burst Repetition	
	uint8_t BREP;	
	
	// unused address
	uint8_t Reserved;
	
	// Neg Drift Compensation
	uint8_t NDRIFT;
	
	// Pos Drift Compensation
	uint8_t PDRIFT;
	
	// Normal Detect Integrator
	uint8_t NDIL;
	
	// Negative Recal Delay
	uint8_t NRD;
	
	// Drift Hold Time/Awake Timeout
	uint8_t DHT_AWAKE;
	
	// Slider Control
	uint8_t Slider_Num_Keys : 4;	// Number of keys
	uint8_t Slider_HYST : 4;		// Hysteresis
	
	// Slider Options
	uint8_t Slider_Resolution; //Resolution
	
	// Key control (AKS Group)
	uint8_t Key0_AKS;
	uint8_t Key1_AKS;
	uint8_t Key2_AKS;
	uint8_t Key3_AKS;
	uint8_t Key4_AKS;
	uint8_t Key5_AKS;
	uint8_t Key6_AKS;
	uint8_t Key7_AKS;
	uint8_t Key8_AKS;
	uint8_t Key9_AKS;
	uint8_t Key10_AKS;
	uint8_t Key11_AKS;
	uint8_t Key12_AKS;
	uint8_t Key13_AKS;
	uint8_t Key14_AKS;
	uint8_t Key15_AKS;
	
	// Negative Threshold (NTHR)		
	uint8_t key0_NTHR;		
	uint8_t key1_NTHR;	
	uint8_t key2_NTHR;
	uint8_t key3_NTHR;
	uint8_t key4_NTHR;
	uint8_t key5_NTHR;
	uint8_t key6_NTHR;
	uint8_t key7_NTHR;
	uint8_t key8_NTHR;
	uint8_t key9_NTHR;
	uint8_t key10_NTHR;
	uint8_t key11_NTHR;
	uint8_t key12_NTHR;
	uint8_t key13_NTHR;
	uint8_t key14_NTHR;
	uint8_t key15_NTHR;
	
	// Burst Length (BL)
	uint8_t key0_BL;		
	uint8_t key1_BL;	
	uint8_t key2_BL;
	uint8_t key3_BL;
	uint8_t key4_BL;
	uint8_t key5_BL;
	uint8_t key6_BL;
	uint8_t key7_BL;
	uint8_t key8_BL;
	uint8_t key9_BL;
	uint8_t key10_BL;
	uint8_t key11_BL;
	uint8_t key12_BL;
	uint8_t key13_BL;
	uint8_t key14_BL;
	uint8_t key15_BL;
	
	// GPIO/GPO Drive
	uint8_t GPIO_GPO_Drive1;	//Shared X line GPOs
	uint8_t GPIO_GPO_Drive2;	//GPIO Drive
	
	// unused address
	uint8_t Reserved1;
	
	// GPIO Direction
	uint8_t GPIO_Direction;
	
	// GPIO/GPO PWM
	uint8_t GPIO_GPO_PWM1;	//Shared X line GPOs
	uint8_t GPIO_GPO_PWM2;	//GPIOs
	
	// PWM Level
	uint8_t PWM_level;	
	
	// GPIO Wake
	uint8_t GPIO_Wake;	
	
	// Common Change keys
	uint8_t CC_Keys1; //key0 to key7
	uint8_t CC_Keys2; //key8 to key15	
	
}SetupBlock;

/*============================================================================
External variables
============================================================================*/
extern SetupBlock setup_block;
extern uint8_t QtStatus[QT_STATUS_SIZE];				 
					 
#endif /* _QT2160_H_ */
/*============================================================================
  END OF FILE 
============================================================================*/						 
					 
