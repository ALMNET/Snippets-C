////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// PROJECT INIT /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define _XTAL_FREQ  8000000
#define FCY         _XTAL_FREQ/2



////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// PROJECT LIBRARIES //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/adc1.h"

#include "LCD.h"
#include "MCP4728.h"

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// STANDARD LIBRARIES /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <libpic30.h>

////////////////////////////////////////////////////////////////////////////////
////////////////////////// I/O PINOUT AND DEFINITIONS //////////////////////////
////////////////////////////////////////////////////////////////////////////////


#define PCF8574_ADDRESS 64




//////////////////////////////////// INPUTS ////////////////////////////////////

/////////////////////////////////// OUTPUTS ////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// CONSTANTS  //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////// DEFINITIONS //////////////////////////////////

#define INPUT		1
#define OUTPUT		0

#define ON			1
#define OFF			0

#define HIGH		1
#define LOW			0

#define TDS_CHANNEL         0x00
#define TURBIDITY_CHANNEL   0x01

// TDS Compensation Factor = 5000 / Max_reading_mV => 5000/4092 = 1.2219
#define  TDS_COMP_FACTOR    1.2219

// Turbidity Compensation Factor
#define  TURB_COMP_FACTOR   0.15625

#define SAMPLING_DELAY      100


////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// VARIABLES  ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

unsigned char buffer[128];

typedef uint32_t sensors_t;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// PROTOTYPE FUNCTIONS /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//extern inline static void ADC1_ChannelSelect( ADC1_CHANNEL channel );

void delay_ms(long delay_value);
void delay_us(long delay_value);

void ADC_Channels_Test();
uint16_t cal(uint16_t value, uint16_t fS, uint16_t fE, uint16_t tS, uint16_t tE);

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// MAIN FUNCTION /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    // initialize the device
    
    sensors_t TDSValue; 
    sensors_t turbidityValue;
    
    
    SYSTEM_Initialize();
    
    ADC_Channels_Test();
        
    while (1)
    {
        // Data Adquisition
        
        delay_ms(200);
        
    }

    return 1;
}

void ADC_Channels_Test(){
    
    sensors_t TDSValue; 
    sensors_t turbidityValue;
    
    char buffer[128];
    
    Lcd_Init();
    Lcd_Cmd (LCD_CURSOR_OFF);
    Lcd_Cmd (LCD_CURSOR_OFF);
    Lcd_Cmd (LCD_CLEAR);   
    
    uint16_t MCP_Value = 0;
        
    do{
      
        I2C_MCP4728_Single_Write(MCP4728_DAC_CH1, MCP_Value++);
        // TDS Sampling and mv conversion
        TDSValue  = ADC1_GetConversion(TDS_CHANNEL) * (5000 / 1023);
        
        // TDS Compensation
        TDSValue  *= TDS_COMP_FACTOR;
        
        // Turbidity Sampling and conversion
        
//        The operation of turbidity sensor is as follows
//        Without no liquid presence, the sensor will give
//        maximum output level possible, so our sensor will
//        receive "100" and with liquid presence it will receive
//        a percentage according the turbidity of the liquid
        turbidityValue  = 100 - ADC1_GetConversion(TURBIDITY_CHANNEL) * TURB_COMP_FACTOR;
  
        // Print on UART for debug purposes
        printf("\nTDS Value  = %lu, Turbidity Value  = %lu", TDSValue, turbidityValue);
        
        // Load a formated string on a temporal 128 bytes buffer
        sprintf(buffer, "TDS = %4lu mV", TDSValue);
        // Load the buffer on the LCD first line
        Lcd_Out(1, 8 - (strlen(buffer) / 2), buffer);
        
        // The same earlier process but for second line
        sprintf(buffer, "Turb = %3lu%%", turbidityValue);
        Lcd_Out(2, 8 - (strlen(buffer) / 2), buffer);
        
        // Sampling delay
        delay_ms(SAMPLING_DELAY);
    }while(1);
    
}


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// AUX FUNCTIONS /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//////////////////////////// GENERAL DELAY FUNCTION ////////////////////////////

void delay_ms(long delay_value){
    long x;
    for(x=0; x < delay_value; x++) __delay_ms(1);
}

void delay_us(long delay_value){
    long x;
    for(x=0; x < delay_value; x++) __delay_us(1);
}

//////////////////////////// CALIBRATION FUNCTION ////////////////////////////
uint16_t cal(uint16_t value, uint16_t fS, uint16_t fE, uint16_t tS, uint16_t tE) {
    return ((long)(value - fS) * (long)(tE - tS)) / (fE - fS) + tS;
}



