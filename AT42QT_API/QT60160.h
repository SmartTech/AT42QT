/*******************************************************************************
*   $FILE:  QT60160.h
*   Brief: Header file for the QT60160 device and it consists QT60160 
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

#ifndef _QT60160_H_
#define _QT60160_H_

/*============================================================================
Macros
============================================================================*/
								
// Chip ID (read from device-address 124)
#define QT_DEVICE_ID	0x0A

// I2C address
#define I2C_ADDRESS		117		

// Setup block start address	
#define QT_SETUPS_BLOCK_ADDR	131

// Key detection status
#define QT_STATUS_ADDR	1

/* 
application storage for QT60160 device-status

QtStatus[0] - Detection Status 
		Bits 0 - 7 : Detect status for keys 0 to 7 (Touched keys report as 1)				

QtStatus[1] - Detection Status 
		Bits 0 - 7 : Detect status for keys 8 to 15 (Touched keys report as 1)	

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

enum { // QT60160 registers address
	QT_KEY_STATUS = 1, // (address 1 to 2 for 16 keys status
	QT_KEY0_SIGNAL = 4,
	QT_KEY0_REFERENCE = 6,
	QT_KEY0_DETECT_COUNT = 8,	
	QT_KEY1_SIGNAL = 9,
	QT_KEY1_REFERENCE = 11,
	QT_KEY1_DETECT_COUNT = 13,
	QT_KEY2_SIGNAL = 14,
	QT_KEY2_REFERENCE = 16,
	QT_KEY2_DETECT_COUNT = 18,
	QT_KEY3_SIGNAL = 19,
	QT_KEY3_REFERENCE = 21,
	QT_KEY3_DETECT_COUNT = 23,
	QT_KEY4_SIGNAL = 24,
	QT_KEY4_REFERENCE = 26,
	QT_KEY4_DETECT_COUNT = 28,
	QT_KEY5_SIGNAL = 29,
	QT_KEY5_REFERENCE = 31,
	QT_KEY5_DETECT_COUNT = 33,
	QT_KEY6_SIGNAL = 34,
	QT_KEY6_REFERENCE = 36,
	QT_KEY6_DETECT_COUNT = 38,	
	QT_KEY7_SIGNAL = 39,
	QT_KEY7_REFERENCE = 41,
	QT_KEY7_DETECT_COUNT = 43,
	QT_KEY8_SIGNAL = 44,
	QT_KEY8_REFERENCE = 46,
	QT_KEY8_DETECT_COUNT = 48,	
	QT_KEY9_SIGNAL = 49,
	QT_KEY9_REFERENCE = 51,
	QT_KEY9_DETECT_COUNT = 53,
	QT_KEY10_SIGNAL = 54,
	QT_KEY10_REFERENCE = 56,
	QT_KEY10_DETECT_COUNT = 58,	
	QT_KEY11_SIGNAL = 59,
	QT_KEY11_REFERENCE = 61,
	QT_KEY11_DETECT_COUNT = 63,
	QT_KEY12_SIGNAL = 64,
	QT_KEY12_REFERENCE = 66,
	QT_KEY12_DETECT_COUNT = 68,	
	QT_KEY13_SIGNAL = 69,
	QT_KEY13_REFERENCE = 71,
	QT_KEY13_DETECT_COUNT = 73,
	QT_KEY14_SIGNAL = 74,
	QT_KEY14_REFERENCE = 76,
	QT_KEY14_DETECT_COUNT = 78,	
	QT_KEY15_SIGNAL = 79,
	QT_KEY15_REFERENCE = 81,
	QT_KEY15_DETECT_COUNT = 83,
	QT_CHIP_ID = 124,
	QT_RECALIBRATE,
	QT_SETUPS_WRITE_UNLOCK = 130,
	QT_SETUPS_BLOCK = 130
};

/*============================================================================
Type definitions
============================================================================*/

typedef struct
{
	// Negative Threshold and negative Drift Compensation
	uint8_t key0_NTHR : 4;		// Key0 Negative Threshold
	uint8_t key0_NDRIFT : 4;	// Key0 negative Drift Compensation
	uint8_t key1_NTHR : 4;		// Key1 Negative Threshold
	uint8_t key1_NDRIFT : 4;	// Key1 negative Drift Compensation
	uint8_t key2_NTHR : 4;		// Key2 Negative Threshold
	uint8_t key2_NDRIFT : 4;	// Key2 negative Drift Compensation
	uint8_t key3_NTHR : 4;		// Key3 Negative Threshold
	uint8_t key3_NDRIFT : 4;	// Key3 negative Drift Compensation
	uint8_t key4_NTHR : 4;		// Key4 Negative Threshold
	uint8_t key4_NDRIFT : 4;	// Key4 negative Drift Compensation
	uint8_t key5_NTHR : 4;		// Key5 Negative Threshold
	uint8_t key5_NDRIFT : 4;	// Key5 negative Drift Compensation
	uint8_t key6_NTHR : 4;		// Key6 Negative Threshold
	uint8_t key6_NDRIFT : 4;	// Key6 negative Drift Compensation
	uint8_t key7_NTHR : 4;		// Key7 Negative Threshold
	uint8_t key7_NDRIFT : 4;	// Key7 negative Drift Compensation
	uint8_t key8_NTHR : 4;		// Key8 Negative Threshold
	uint8_t key8_NDRIFT : 4;	// Key8 negative Drift Compensation	
	uint8_t key9_NTHR : 4;		// Key9 Negative Threshold
	uint8_t key9_NDRIFT : 4;	// Key9 negative Drift Compensation
	uint8_t key10_NTHR : 4;		// Key10 Negative Threshold
	uint8_t key10_NDRIFT : 4;	// Key10 negative Drift Compensation
	uint8_t key11_NTHR : 4;		// Key11 Negative Threshold
	uint8_t key11_NDRIFT : 4;	// Key11 negative Drift Compensation
	uint8_t key12_NTHR : 4;		// Key12 Negative Threshold
	uint8_t key12_NDRIFT : 4;	// Key12 negative Drift Compensation
	uint8_t key13_NTHR : 4;		// Key13 Negative Threshold
	uint8_t key13_NDRIFT : 4;	// Key13 negative Drift Compensation
	uint8_t key14_NTHR : 4;		// Key14 Negative Threshold
	uint8_t key14_NDRIFT : 4;	// Key14 negative Drift Compensation
	uint8_t key15_NTHR : 4;		// Key15 Negative Threshold
	uint8_t key15_NDRIFT : 4;	// Key15 negative Drift Compensation
	uint8_t unused[8];		// These locations are unused for QT60160
		
	// positive Drift Compensation
	uint8_t key0_resvd : 4;
	uint8_t key0_PDRIFT : 4;	// Key0 positive Drift Compensation	
	uint8_t key1_resvd : 4;
	uint8_t key1_PDRIFT : 4;	// Key1 positive Drift Compensation		
	uint8_t key2_resvd : 4;
	uint8_t key2_PDRIFT : 4;	// Key2 positive Drift Compensation		
	uint8_t key3_resvd : 4;
	uint8_t key3_PDRIFT : 4;	// Key3 positive Drift Compensation	
	uint8_t key4_resvd : 4;
	uint8_t key4_PDRIFT : 4;	// Key4 positive Drift Compensation		
	uint8_t key5_resvd : 4;
	uint8_t key5_PDRIFT : 4;	// Key5 positive Drift Compensation	
	uint8_t key6_resvd : 4;
	uint8_t key6_PDRIFT : 4;	// Key6 positive Drift Compensation		
	uint8_t key7_resvd : 4;
	uint8_t key7_PDRIFT : 4;	// Key7 positive Drift Compensation		
	uint8_t key8_resvd : 4; 
	uint8_t key8_PDRIFT : 4;	// Key8 positive Drift Compensation		
	uint8_t key9_resvd : 4;	
	uint8_t key9_PDRIFT : 4;	// Key9 positive Drift Compensation		
	uint8_t key10_resvd : 4;
	uint8_t key10_PDRIFT : 4;	// Key10 positive Drift Compensation		
	uint8_t key11_resvd : 4;
	uint8_t key11_PDRIFT : 4;	// Key11 positive Drift Compensation		
	uint8_t key12_resvd : 4;
	uint8_t key12_PDRIFT : 4;	// Key12 positive Drift Compensation	
	uint8_t key13_resvd : 4;
	uint8_t key13_PDRIFT : 4;	// Key13 positive Drift Compensation		
	uint8_t key14_resvd : 4;
	uint8_t key14_PDRIFT : 4;	// Key14 positive Drift Compensation		
	uint8_t key15_resvd : 4;
	uint8_t key15_PDRIFT : 4;	// Key15 positive Drift Compensation
	uint8_t unused1[8];			// These locations are unused for QT60160
	
	// Normal DI Limit and Fast DI Limit
	uint8_t key0_NDIL : 4;		// key0 Normal DI Limit
	uint8_t key0_FDIL : 4;		// key0 Fast DI Limit
	uint8_t key1_NDIL : 4;		// key1 key Normal DI Limit
	uint8_t key1_FDIL : 4;		// key1 Fast DI Limit
	uint8_t key2_NDIL : 4;		// key2 Normal DI Limit
	uint8_t key2_FDIL : 4;		// key2 Fast DI Limit
	uint8_t key3_NDIL : 4;		// key3 Normal DI Limit
	uint8_t key3_FDIL : 4;		// key3 Fast DI Limit
	uint8_t key4_NDIL : 4;		// key4 Normal DI Limit
	uint8_t key4_FDIL : 4;		// key4 Fast DI Limit
	uint8_t key5_NDIL : 4;		// key5 Normal DI Limit
	uint8_t key5_FDIL : 4;		// key5 Fast DI Limit
	uint8_t key6_NDIL : 4;		// key6 Normal DI Limit
	uint8_t key6_FDIL : 4;		// key6 Fast DI Limit
	uint8_t key7_NDIL : 4;		// key7 Normal DI Limit
	uint8_t key7_FDIL : 4;		// key7 Fast DI Limit
	uint8_t key8_NDIL : 4;		// key8 Normal DI Limit
	uint8_t key8_FDIL : 4;		// key8 Fast DI Limit
	uint8_t key9_NDIL : 4;		// key9 Normal DI Limit
	uint8_t key9_FDIL : 4;		// key9 Fast DI Limit
	uint8_t key10_NDIL : 4;		// key10 Normal DI Limit
	uint8_t key10_FDIL : 4;		// key10 Fast DI Limit	
	uint8_t key11_NDIL : 4;		// key11 Normal DI Limit
	uint8_t key11_FDIL : 4;		// key11 Fast DI Limit
	uint8_t key12_NDIL : 4;		// key12 Normal DI Limit
	uint8_t key12_FDIL : 4;		// key12 Fast DI Limit
	uint8_t key13_NDIL : 4;		// key13 Normal DI Limit
	uint8_t key13_FDIL : 4;		// key13 Fast DI Limit
	uint8_t key14_NDIL : 4;		// key14 Normal DI Limit
	uint8_t key14_FDIL : 4;		// key14 Fast DI Limit
	uint8_t key15_NDIL : 4;		// key15 Normal DI Limit
	uint8_t key15_FDIL : 4;		// key15 Fast DI Limit
	uint8_t unused2[8];			// These locations are unused for QT60160
	
	// Neg recal delay
	uint8_t key0_NRD;	// Key0 Neg recal delay
	uint8_t key1_NRD;	// Key1 Neg recal delay
	uint8_t key2_NRD;	// Key2 Neg recal delay
	uint8_t key3_NRD;	// Key3 Neg recal delay
	uint8_t key4_NRD;	// Key4 Neg recal delay
	uint8_t key5_NRD;	// Key5 Neg recal delay
	uint8_t key6_NRD;	// Key6 Neg recal delay
	uint8_t key7_NRD;	// Key7 Neg recal delay
	uint8_t key8_NRD;	// Key8 Neg recal delay
	uint8_t key9_NRD;	// Key9 Neg recal delay
	uint8_t key10_NRD;	// Key10 Neg recal delay
	uint8_t key11_NRD;	// Key11 Neg recal delay
	uint8_t key12_NRD;	// Key12 Neg recal delay
	uint8_t key13_NRD;	// Key13 Neg recal delay
	uint8_t key14_NRD;	// Key14 Neg recal delay
	uint8_t key15_NRD;	// Key15 Neg recal delay
	uint8_t unused3[8];	// These locations are unused for QT60160
	
	// Wake On Touch enable/disable, Burst Length, AKS and Sync enable\disable	
	uint8_t key0_unused : 3;	// unused bits
	uint8_t key0_WAKE : 1;		// Key0 Wake On Touch
	uint8_t key0_BL : 2;		// Key0 Burst Length
	uint8_t key0_AKS : 1;		// Key0 AKS
	uint8_t key0_SSYNC : 1;		// Key0 Scope Sync	
	uint8_t key1_unused : 3;	// unused bits
	uint8_t key1_WAKE : 1;		// Key1 Wake On Touch
	uint8_t key1_BL : 2;		// Key1 Burst Length
	uint8_t key1_AKS : 1;		// Key1 AKS
	uint8_t key1_SSYNC : 1;		// Key1 Scope Sync
	uint8_t key2_unused : 3;	// unused bits
	uint8_t key2_WAKE : 1;		// Key2 Wake On Touch
	uint8_t key2_BL : 2;		// Key2 Burst Length
	uint8_t key2_AKS : 1;		// Key2 AKS
	uint8_t key2_SSYNC : 1;		// Key2 Scope Sync
	uint8_t key3_unused : 3;	// unused bits
	uint8_t key3_WAKE : 1;		// Key3 Wake On Touch
	uint8_t key3_BL : 2;		// Key3 Burst Length
	uint8_t key3_AKS : 1;		// Key3 AKS
	uint8_t key3_SSYNC : 1;		// Key3 Scope Sync
	uint8_t key4_unused : 3;	// unused bits
	uint8_t key4_WAKE : 1;		// Key4 Wake On Touch
	uint8_t key4_BL : 2;		// Key4 Burst Length
	uint8_t key4_AKS : 1;		// Key4 AKS
	uint8_t key4_SSYNC : 1;		// Key4 Scope Sync
	uint8_t key5_unused : 3;	// unused bits
	uint8_t key5_WAKE : 1;		// Key5 Wake On Touch
	uint8_t key5_BL : 2;		// Key5 Burst Length
	uint8_t key5_AKS : 1;		// Key5 AKS
	uint8_t key5_SSYNC : 1;		// Key5 Scope Sync
	uint8_t key6_unused : 3;	// unused bits
	uint8_t key6_WAKE : 1;		// Key6 Wake On Touch
	uint8_t key6_BL : 2;		// Key6 Burst Length
	uint8_t key6_AKS : 1;		// Key6 AKS
	uint8_t key6_SSYNC : 1;		// Key6 Scope Sync
	uint8_t key7_unused : 3;	// unused bits
	uint8_t key7_WAKE : 1;		// Key7 Wake On Touch
	uint8_t key7_BL : 2;		// Key7 Burst Length
	uint8_t key7_AKS : 1;		// Key7 AKS
	uint8_t key7_SSYNC : 1;		// Key7 Scope Sync
	uint8_t key8_unused : 3;	// unused bits
	uint8_t key8_WAKE : 1;		// Key8 Wake On Touch
	uint8_t key8_BL : 2;		// Key8 Burst Length
	uint8_t key8_AKS : 1;		// Key8 AKS
	uint8_t key8_SSYNC : 1;		// Key8 Scope Sync
	uint8_t key9_unused : 3;	// unused bits
	uint8_t key9_WAKE : 1;		// Key9 Wake On Touch
	uint8_t key9_BL : 2;		// Key9 Burst Length
	uint8_t key9_AKS : 1;		// Key9 AKS
	uint8_t key9_SSYNC : 1;		// Key9 Scope Sync	
	uint8_t key10_unused : 3;	// unused bits
	uint8_t key10_WAKE : 1;		// Key10 Wake On Touch
	uint8_t key10_BL : 2;		// Key10 Burst Length
	uint8_t key10_AKS : 1;		// Key10 AKS
	uint8_t key10_SSYNC : 1;	// Key10 Scope Sync	
	uint8_t key11_unused : 3;	// unused bits
	uint8_t key11_WAKE : 1;		// Key11 Wake On Touch
	uint8_t key11_BL : 2;		// Key11 Burst Length
	uint8_t key11_AKS : 1;		// Key11 AKS
	uint8_t key11_SSYNC : 1;	// Key11 Scope Sync
	uint8_t key12_unused : 3;	// unused bits
	uint8_t key12_WAKE : 1;		// Key12 Wake On Touch
	uint8_t key12_BL : 2;		// Key12 Burst Length
	uint8_t key12_AKS : 1;		// Key12 AKS
	uint8_t key12_SSYNC : 1;	// Key12 Scope Sync
	uint8_t key13_unused : 3;	// unused bits
	uint8_t key13_WAKE : 1;		// Key13 Wake On Touch
	uint8_t key13_BL : 2;		// Key13 Burst Length
	uint8_t key13_AKS : 1;		// Key13 AKS
	uint8_t key13_SSYNC : 1;	// Key13 Scope Sync
	uint8_t key14_unused : 3;	// unused bits
	uint8_t key14_WAKE : 1;		// Key14 Wake On Touch
	uint8_t key14_BL : 2;		// Key14 Burst Length
	uint8_t key14_AKS : 1;		// Key14 AKS
	uint8_t key14_SSYNC : 1;	// Key14 Scope Sync
	uint8_t key15_unused : 3;	// unused bits
	uint8_t key15_WAKE : 1;		// Key15 Wake On Touch
	uint8_t key15_BL : 2;		// Key15 Burst Length
	uint8_t key15_AKS : 1;		// Key15 AKS
	uint8_t key15_SSYNC : 1;	// Key15 Scope Sync
	uint8_t unused4[8];			// These locations are unused for QT60160
	
	// Device Sleep Duration and Mains Sync
	uint8_t QT60160_SLEEP : 3;		// Sleep Duration
	uint8_t QT60160_unused1 : 3;	// unused bits
	uint8_t QT60160_MSYNC : 1;		// Mains Sync
	uint8_t QT60160_unused2 : 1;	// unused bits
	
	// Device Awake Timeout
	uint8_t QT60160_AWAKE;	
	
	// Device Drift Hold Time
	uint8_t QT60160_DHT;
	
}SetupBlock;

/*============================================================================
External variables
============================================================================*/
extern SetupBlock setup_block;
extern uint8_t QtStatus[QT_STATUS_SIZE];				 
					 
#endif /* _QT60160_ */
/*============================================================================
  END OF FILE 
============================================================================*/						 
					 
