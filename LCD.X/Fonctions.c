/*
 Fonctions associé au LCD mpour la librairie
 
 Date : 19 novembre 2017
 
 Auteurs :  Danaé Dufour-Forget
            Olivier Belval
 */

#include "Fonctions.h"


bool LCDbusy = 0;
int CNT1 = 0;
int CNT2 = 0;
int NextCNT2 = 0;
long DataLCD = 0;
bool FlagCSToggle = 0;

void InitLCD ()
{
    Timer0Init(0);
    IOInit();
    Timer0IntInit();
    LCDWait(100000);
    //A FAIRE : RETURN HOME ET CLEAR LCD
    
}

void Timer0Init ()
{
    // IMPORTANT
    // S'ASSURER QUE LA FRÉQUENCE DU TIMER SOIT EN DESSOUS DE 4MHz
    
    //Configuration du timer
    Timer0Stop();           // Arrete le timer avant de le configurer
    T0CONbits.T08BIT = 1;   // 0 = compteur sur 16 bit et 1 = compteur sur 8 bits
    T0CONbits.T0CS = 1;     // 01 = La source de clock est la clock interne
    T0CONbits.PSA = 1;      // 0 = Autorise la pre-scaler
    T0CONbits.T0PS = 0;   // Ajuste la férquence du timer selon Div
    TMR0L = 0xFF;
}

void Timer0Start()
{
    T0CONbits.TMR0ON = 1; //Démarre le timer
}

void Timer0Stop()
{
    T0CONbits.TMR0ON = 0;   // Arrete le timer
}

void Timer0IntInit()
{
    INTCON2bits.TMR0IP = 0; // Low priority
    INTCONbits.TMR0IE = 1;  // Enable Timer0 interrupt
    INTCONbits.PEIE = 1;    // Enable Peripheral interrupt
    INTCONbits.GIE = 1;     // Enable Global interrupt
    RCONbits.IPEN = 1;      // Enable priority interrupt
}

void IOInit()
{
    TRISDbits.TRISD4 = 0;   // Output mode (SDO2)
    TRISDbits.TRISD3 = 0;   // Output mode (SS2)
    TRISDbits.TRISD2 = 0;   // Output mode (SCLK2)
    TRISDbits.TRISD1 = 1;   // Input mode (SDI2)
    
    LATDbits.LATD3 = 1;     // Mettre SS2 à HIGH
    LATDbits.LATD2 = 1;     // Mettre SCLK2 à HIGH
}

bool ClockToggle()
{
    LATDbits.LATD2 += 1;
    return LATDbits.LATD2;
}

bool CSToggle()
{
    LATDbits.LATD3 += 1;    // Toggle SS2
    return LATDbits.LATD3;
}

void DataWrite(bool data)
{
    LATDbits.LATD4 = data;  //Output Data
}

void LCDWait(int delaiUs)
{
    LCDBusy();
    CNT2 = delaiUs;
}

void LCDBusy()
{
    LCDbusy = 1;
}

void LCDReady()
{
    LCDbusy = 0;
}

void InitDataLCD (bool RS, bool RW, char data, int delayUs)
{           
    while(CNT1);
    NextCNT2 = delayUs;
    CNT1 = 24;

    DataLCD  = 0;
    DataLCD = ((long)data & 0xF0);
    DataLCD <<= 4;
    DataLCD += ((long)data & 0x0F);
    DataLCD <<= 2;
    DataLCD += (long)RS;
    DataLCD <<= 1;
    DataLCD += (long)RW;
    DataLCD <<= 5;
    DataLCD += 0x1F;
    FlagCSToggle = 1;
    Timer0Start();
}

void WriteLCD()
{
    if(FlagCSToggle && !CNT2)
    {
        FlagCSToggle = 0;
        CSToggle();
    }
    if(!LCDbusy)
    {
        bool clock = ClockToggle();

        if (!clock)
        {
            DataWrite((bool)(DataLCD & 1));
            DataLCD = DataLCD >> 1;
        }

        if (clock)
        {
            CNT1--;
        }

        if (!CNT1)
        {
            CSToggle();
            LCDBusy();
            CNT2 = NextCNT2;
        }
    }
    else
    {
        CNT2--;
        if(!CNT2)
        {
            LCDReady();
        }
    }
    
}