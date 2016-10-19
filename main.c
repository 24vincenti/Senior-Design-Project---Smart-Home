#include "driverlib.h"

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void init_clock();
void init_uart();
void UART_transmit_data(const char* data);

const eUSCI_UART_Config uartConfig =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        78,                                     // BRDIV = 78
        2,                                       // UCxBRF = 3
        0,                                       // UCxBRS = 0x25
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};

int main(void)
{
	init_clock();
	init_uart();

	uint8_t received_data;

	while(1)
	{
		received_data = MAP_UART_receiveData( EUSCI_A2_BASE );

		switch(received_data){
			case 'c':
				UART_transmit_data("$$$");
				break;
			case 'a':
				UART_transmit_data("set$wlan$suth$4");
				break;
			case 'p':
				UART_transmit_data("set$wlan$phrase");
				break;
			case 's':
				UART_transmit_data("join$GitmoGridAdmin");
				break;ing
	}

		/* echoes user input back to terminal */
		// MAP_UART_transmitData( EUSCI_A2_BASE, (char)received_data );

		received_data = 0;

		UART_transmit_data("testing");

	}
}

void UART_transmit_data(const char* data)
{
	int i;
	for(i = 0; i < strlen(data); i++){MAP_UART_transmitData(EUSCI_A2_BASE, data[i]);}
	MAP_UART_transmitData(EUSCI_A2_BASE, '\r');
}

void init_uart()
{
	/* Selecting P3.2 and P3.3 in UART mode */
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
			GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

	MAP_UART_initModule(EUSCI_A2_BASE, &uartConfig);
	MAP_UART_enableModule(EUSCI_A2_BASE);

	/* used for msp to terminal comm */
	/* Selecting P1.2 and P1.3 in UART mode */
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
			GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

	MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);
	MAP_UART_enableModule(EUSCI_A0_BASE);
}

void init_clock()
{
	/* Halting WDT  */
	MAP_WDT_A_holdTimer();

//	/* Enable floating point unit to set DCO frequency */
//	MAP_FPU_enableModule();
//
//	MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
//	MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);
//
//	/* Increasing core voltage to handle higher frequencies */
//	MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);

	/* Setting DCO to 24MHz */
	MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);
}

}