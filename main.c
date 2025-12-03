#include "Motor.h"
#include "clocks_and_modes.h"
#include <stdint.h>
#include "regs_config.h"

int main(void)
{
	SOSC_init_8MHz();
	SPLL_init_160MHz();
	NormalRUNmode_80MHz();
	PORT_init_Motor();
	FTM2_CH0_PWM();
	ADC0_init();
	NVIC_init_IRQs();
	LPIT0_init();


	for(;;)
	{
		
	}
}
