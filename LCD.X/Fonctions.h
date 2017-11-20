/* 
 * File:   Fonctions.h
 * Author: Olivier Belval, Danaé Dufour-Forget
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef FONCTIONS_H
#define	FONCTIONS_H

#define _XTAL_FREQ_ 8000000


#define READ 1
#define WRITE 0
#define FONCTION_AV 1

#include <xc.h> 
#include <stdio.h>
#include <stdbool.h>

void InitLCD ();

void Timer0Init ();

void Timer0Start();

void Timer0Stop();

void Timer0IntInit();

void IOInit();

bool ClockToggle();

bool CSToggle();

void DataWrite(bool data);

void LCDWait(int delaiUs);

void LCDBusy();

void LCDReady();

void InitDataLCD (bool RS, bool RW, char data, int delayUs);

void WriteLCD();
 
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#endif	/* XC_HEADER_TEMPLATE_H */

