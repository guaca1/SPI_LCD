/*
 * File:   main.c
 * Author: belo1601
 *
 * Created on 19 novembre 2017, 13:45
 */

//Includes

#include <stdio.h>
#include <stdbool.h>
#include <xc.h>
#include "Fonctions.h"

//////////////////////////////////////////////////////////////

void interrupt low_priority myIsr (void)
{
    if(INTCONbits.TMR0IF)
    {
        ClockToggle();
        INTCONbits.TMR0IF = 0;
        TMR0H = 0xFF;
        TMR0L = 0xFF;
    }
    
}

void main(void) {
    
    InitLCD();
    InitDataLCD(0,0,0x02,1600);
    
    
    while(1)
    {
        InitDataLCD(0,WRITE,0x48,50);
    }
    
    return;
}
