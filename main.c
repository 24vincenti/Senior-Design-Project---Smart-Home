#include "driverlib.h"

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void init_clock();
void init_uart();
void UART_transmit_data(const char* data);

const eUSCI_UART_Config uartConfig =
{
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,     		   // SMCLK Clock Source
    13,                                			   // BRDIV
    0,                                       	   // UCxBRF
    37,                                      	   // UCxBRS
    EUSCI_A_UART_NO_PARITY,                  	   // No Parity
    EUSCI_A_UART_LSB_FIRST,                  	   // MSB First
    EUSCI_A_UART_ONE_STOP_BIT,              	   // One stop bit
    EUSCI_A_UART_MODE,                             // UART mode
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};

int main(void)
{
	init_clock();
	init_uart();



    while(1)
    {


    }
}

void UART_transmit_data(const char* data)
{


}

void init_uart()
{


}

void init_clock()
{

	/* Halting WDT  */
	MAP_WDT_A_holdTimer();

	/* Enable floating point unit to set DCO frequency */
	MAP_FPU_enableModule();

	MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
	MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);

	/* Increasing core voltage to handle higher frequencies */
	MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);

	/* Setting DCO to 24MHz */
	MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);

}
