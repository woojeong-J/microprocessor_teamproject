#include "Motor.h"
#include "clocks_and_modes.h"
#include <stdint.h>
#include "regs_config.h"
#include "handler.h"
#include "seven_segment.h"
#include "turn.h"

#define GEAR_P 0
#define GEAR_D 1
#define GEAR_R 2
#define GEAR_C 3

volatile int gear; // 디스플레이용 변수 (0:P, 1:D, 2:R, 3:C)

volatile int fuel = 99;


// 현재 상태 변수
volatile CarState_t current_state = STATE_OFF;

// 버튼 눌림 플래그 (인터럽트에서 1로 설정)
volatile int Start_Flag = 0; // 시동 (PTA13)
volatile int Gear_Flag = 0;     // 기어 (PTA12)
volatile int Cruise_Flag = 0;   // 크루즈 (PTC15)

extern volatile int mode;

int main(void)
{
	SOSC_init_8MHz();
	SPLL_init_160MHz();
	NormalRUNmode_80MHz();
	PORT_init_Motor();
	PORT_init_Segment();
	PORT_init_turn();
	FTM2_CH0_PWM();
	FTM2_CH1_PWM();
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
			 	for(volatile int i=0; i<2000000; i++);
			  	Gear_Flag = 0; // 기어 변경 플래그 초기화
		    }
	  	}

		// 정지 상태(mode == 0)이면 LED 항상 OFF 유지
        if (mode == 0) 
		{
            GPIOE_PSOR |= (1<<PTE14)|(1<<PTE15)|(1<<PTE16);
            GPIOA_PSOR |= (1<<PTA0)|(1<<PTA1);
        }
        // mode 1,2 일 때는
        // LED 토글은 LPIT0_Ch0_IRQHandler에서 주기적으로 실행
        // 서보 각도 변경은 PORTC_IRQHandler에서 버튼 눌릴 때만 실행
		fuel = 99 - distance;
		if(fuel < 11)
		{
			GPIOD_PCOR = (1<<PTD15); //led red on
		}
		
    } // end for
}
