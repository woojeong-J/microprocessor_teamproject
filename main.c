#include "Motor.h"
#include "clocks_and_modes.h"
#include <stdint.h>
#include "regs_config.h"
#include "handler.h"

#define GEAR_P 0
#define GEAR_D 1
#define GEAR_R 2
#define GEAR_C 3

volatile int gear; // 디스플레이용 변수 (0:P, 1:D, 2:R, 3:C)

// 현재 상태 변수
volatile CarState_t current_state = STATE_OFF;

// 버튼 눌림 플래그 (인터럽트에서 1로 설정)
volatile int Start_Flag = 0; // 시동 (PTA13)
volatile int Gear_Flag = 0;     // 기어 (PTA12)
volatile int Cruise_Flag = 0;   // 크루즈 (PTC15)

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
      	if(Start_Flag == 1)
	  	{
		  // 시동이 켜져 있을 때
			if (Gear_Flag == 1) // 기어 변경 요청
			{
			 	switch (current_state)
			  	{
				  	case STATE_OFF:
					  	current_state = STATE_P;
					  	gear = GEAR_P;
					  	break;
				  	case STATE_P:
					  	current_state = STATE_D;
					 	 gear = GEAR_D;
					  	break;
				  	case STATE_D:
					  	current_state = STATE_R;
					 	 gear = GEAR_R;
					 	 break;
				 	case STATE_R:
					 	current_state = STATE_P;
					  	gear = GEAR_P;
					  	break;
					case STATE_CRUISE:
						current_state = STATE_CRUISE; // 크루즈 모드에서는 기어 변경 불가
						gear = GEAR_C;
						break;
				  	default:
						break;
			  	}
			  	Gear_Flag = 0; // 기어 변경 플래그 초기화
		    }
	  	}
    } // end for
}
