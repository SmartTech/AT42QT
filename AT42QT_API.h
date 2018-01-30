/*******************************************************************************
*   $FILE:  QT_API.h
*   Atmel Corporation:  http://www.atmel.com
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

#ifndef QT_API_H_
#define QT_API_H_

/*============================================================================
// QT Device list
============================================================================*/
#define QT1060  1
#define QT1070  2
#define QT2120  3
#define QT2160  4
#define QT60160 5
#define QT60240 6

/*============================================================================
// Select one of the QT device from above list
============================================================================*/
#define QT_DEVICE QT2160

/*============================================================================
Include files
============================================================================*/

#if (QT_DEVICE == QT1060)
	#include "AT42QT_API/QT1060.h"
#elif (QT_DEVICE == QT1070)
	#include "AT42QT_API/QT1070.h"
#elif (QT_DEVICE == QT2120)
	#include "AT42QT_API/QT2120.h"
#elif (QT_DEVICE == QT2160)
	#include "AT42QT_API/QT2160.h"
#elif (QT_DEVICE == QT60160)
	#include "AT42QT_API/QT60160.h"
#elif (QT_DEVICE == QT60240)
	#include "AT42QT_API/QT60240.h"
#else
	#error "Device not supported"
#endif

#endif /* QT_API_H_ */
/*============================================================================
  END OF FILE 
============================================================================*/	

