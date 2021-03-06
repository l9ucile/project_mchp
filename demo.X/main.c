/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.80.0
        Device            :  PIC16F18875
        Driver Version    :  2.00
 */

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */

#include <bits/alltypes.h>

#include "mcc_generated_files/mcc.h"

#define PRESSED 0

#define STR_FIRMWARE_DESCRIPTION "Demo for push button and Sleep mode "
#define STR_FIRMWARE_VERSION     "v0.1"  /* Firmware version */

/**
 * @brief counter the number of LED state from starting
 */
uint32_t counter = 0;

/*
 Serial communication

    Les broches par défaut sont :
    TX = RC6
    RX = RC7
    Pour une utilisation avec la carte MPLAB Xpress Evaluation Boards :
    TX = RC0 (F188TXU)
    RX = RC1 (F188RXU)
 */

/*
                         Main application
 */
void main( void )
{
    // initialize the device
    SYSTEM_Initialize( );

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable( );

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable( );

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while ( 1 )
    {
        /* Pour mesurer le temps d'exécution de la boucle principale
         * LED_System_Toggle( );
         */
        
        /* Incrémenter le compteur lorsque BP est pressé */
        if ( PRESSED == pushButton_GetValue( ) )
        {
            while ( PRESSED == pushButton_GetValue( ) );
            __delay_ms( 1 );
            LED_Toggle( );
            ++counter;
        }

        /* Traitement d'une donnée en reception du port série */
        if ( EUSART_is_rx_ready( ) )
        {
            /* If there is at least one byte of data has been received. */
            uint8_t rx_data_from_serial = EUSART_Read( );

            printf( "\r\n" );

            switch ( rx_data_from_serial )
            {
                case '?':
                case ',':
                    printf( "Send C to get counter value.\r\n" );
                    break;

                case 'V':
                case 'v':
                    printf( STR_FIRMWARE_DESCRIPTION STR_FIRMWARE_VERSION "\r\n" );
                    printf( "Build on " __DATE__ " at " __TIME__ "\r\n" );
                    break;

                case 'C':
                case 'c':
                    printf( "Counter value: %d\r\n", counter );
                    break;

                case 'S':
                case 's':
                    printf( "Enter in Sleep mode...\r\n\n" );
                    LED_SetLow( );
                    __delay_ms( 20 );
                    /* datasheet "8.2.3 LOW-POWER SLEEP MODE" page 156 */
                    SLEEP( );
                    __delay_ms( 10 );
                    printf( "\r\nWake up from Sleep mode!\r\n\n" );
                    break;

                default:
                    printf( "Cmd not recognised! Send ? for help.\r\n" );
            }
        }
    }
}




/**
 End of File
 */