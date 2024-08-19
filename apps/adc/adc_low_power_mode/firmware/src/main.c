/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, sam_9x75_curiosity OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY sam_9x75_curiosity
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes

/*****************************************************
 ADC CH7 - PA31 - Connect to Vcc or GND
 *****************************************************/

#define ADC_VREF               (3.3f)

uint16_t adc_ch7_count;

float adc_ch7_voltage;

volatile bool result_ready = false;

/* This function is called after conversion of last channel in the user sequence */
void ADC_EventHandler(uint32_t status, uintptr_t context)
{
    /* Read the result of AD6 channel */
    adc_ch7_count = ADC_ChannelResultGet(ADC_CH7);
       
    result_ready = true;
}

void sleepmode_fwup_off(void)
{
    printf("\r\n-----------------entering FWUP OFF mode------------------\r\n");
    ADC_SleepModeEnable();
    ADC_FastWakeupDisable();
    ADC_ConversionStart();
}

void sleepmode_fwup_on(void)
{
    printf("\r\n-----------------entering FWUP ON mode------------------\r\n");
    ADC_SleepModeEnable();
    ADC_FastWakeupEnable();
    ADC_ConversionStart(); 
}

void print_menu(void)
{
    printf("\r\n---------------------------------------------------------");
    printf("\r\n                    ADC Low Power Demo                 ");
    printf("\r\n---------------------------------------------------------\r\n");
    printf(" Select an option for FWUP :\r\n"
            " 0 -> both ADC core and Vref are OFF between conversions\r\n"
            " 1 -> ADC core is OFF and Vref is ON between conversions\r\n"
            " =>");

}

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    uint8_t user_input = 0;
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    /* Register callback function for ADC end of conversion interrupt*/
    ADC_CallbackRegister(ADC_EventHandler, (uintptr_t)NULL);
    print_menu();

    scanf("%c", (char *) &user_input);
    
    switch (user_input)
    {
        case '0':
            printf(" 0 selected\r\n");
            sleepmode_fwup_off();
            break;
        case '1':
            printf("1 selected\r\n");
            sleepmode_fwup_on();
            break;
        default:
            printf("\r\n");
            break;
    }
    printf("CH7 Count  CH7 Voltage \r\n");           

    while ( true )
    {
        /* Check if result is ready to be transmitted to console */
        if (result_ready == true)
        {
            adc_ch7_voltage = (float)adc_ch7_count * ADC_VREF/4095U;

            printf("0x%03x      %0.2f V       \t\r", adc_ch7_count, adc_ch7_voltage);
                
            result_ready = false;
 
            PIT_DelayMs(500);

            /* Start ADC conversion */
            ADC_ConversionStart();
        }
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}



/*******************************************************************************
 End of File
*/

