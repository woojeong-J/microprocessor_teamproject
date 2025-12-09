#include "handler.h"
#include "regs_config.h"
#include "clocks_and_modes.h"
#include "Motor.h" 
#include "seven_segment.h"

static uint32_t dist_buffer = 0;
// [튜닝 포인트] 이 숫자로 거리 올라가는 속도를 조절합니다.
// 숫자가 클수록 거리가 천천히 올라갑니다.
// 200,000 (200km/h) 속도일 때 10ms마다 더해지므로, 1초에 20,000,000이 쌓입니다.
// 아래 값으로 설정하면 200km/h일 때 1초에 숫자가 약 2~4 정도 올라갑니다. (적당한 데모 속도)
#define DIST_THRESHOLD 5000000

volatile int scan_index = 0;
volatile int distance = 0;

void adc_start(void)
{
	ADC0_SC1A &= ~((0b111111)<<ADCH_BITS);
	ADC0_SC1A |= (ADC0_SE4<<ADCH_BITS);

}

uint32_t read_adc_chx(void)
{
	while((ADC0_SC1A & (1<<COCO_BIT))==0){}

	return ADC0_RA;
}

void LPIT0_init(void)
{
	PCC_LPIT &= ~((0b111)<<PCS_BITS);
	PCC_LPIT |= ((0b110)<<PCS_BITS);
	PCC_LPIT |= (1<<CGC_BIT);

	LPIT_MCR |= (1<<M_CEN_BIT); 
    //여기까지 공통
    // ch0
	LPIT_MIER |= (1<<TIE0_BIT); // Enable Timer 0 interrupt

	LPIT_TVAL0 = 400000; // 80MHz / 2 / 400000 = 100Hz -> 10ms

	LPIT_TCTRL0 &= ~((0b11)<<MODE_BITS);
	LPIT_TCTRL0 |= (1<<T_EN_BIT);

    // ch1
    LPIT_MIER |= (1<<TIE1_BIT); // Enable Timer 1 interrupt

    LPIT_TVAL1 = 2000; // 80MHz / 2 / 2000 = 20000Hz -> 0.05ms

	LPIT_TCTRL1 &= ~((0b11)<<MODE_BITS);
	LPIT_TCTRL1 |= (1<<T_EN_BIT);

    // ch2
    LPIT_MIER |= (1<<TIE2_BIT); // Enable Timer 1 interrupt

    LPIT_TVAL2 = 4000000; // 80MHz / 2 / 4000000 = 10Hz -> 100ms

	LPIT_TCTRL2 &= ~((0b11)<<MODE_BITS);
	LPIT_TCTRL2 |= (1<<T_EN_BIT);
}

void NVIC_init_IRQs(void)
{
	NVIC_ICPR1 |= (1<<(61 % 32)); // PORTC IRQ
	NVIC_ISER1 |= (1<<(61 % 32));
	NVIC_IPR61 = 10;

	NVIC_ICPR1 |= (1<<(48 % 32)); // LPIT0 IRQ
	NVIC_ISER1 |= (1<<(48 % 32));
	NVIC_IPR48 = 10;

	NVIC_ICPR1 |= (1<<(59 % 32)); // PORTA IRQ
	NVIC_ISER1 |= (1<<(59 % 32));
	NVIC_IPR59 = 10;
}

//LPIT 핸들러

void LPIT0_Ch0_IRQHandler(void) //차량 제어 10ms
{
    adc_start();
	adcResult = read_adc_chx(); //가변 저항 값 0~ 4095

    // 이 함수가 10ms마다 실행되므로, DRV_Control이 선형적으로 속도를 갱신
    if (Accel_Flag == 1) {
        DRV_Control();
    } else if (Brake_Flag == 1) {
        // 급제동 로직
        DRV_Brake_Control();
    } else {
        // 타력 주행 로직
        DRV_Coasting_Control();
    }

    if (current_state == STATE_D && current_speed > 0)
    {
        // 1. 현재 속도에 비례하여 거리를 누적
        dist_buffer += current_speed; 

        // 2. 일정 임계값을 넘으면 거리 1 증가 및 버퍼 초기화
        if (dist_buffer >= DIST_THRESHOLD)
        {
            distance++;       // 거리 1 증가
            dist_buffer = 0;  // 버퍼 초기화
            
            if(distance > 99) distance = 0; // 0~99 반복
        }
    }

	LPIT_MSR |= (1<<TIF0_BIT);
}

void LPIT0_Ch1_IRQHandler(void) // 세그먼트 디스플레이 0.05ms
{
	displayDigitClear();
    if(Start_Flag == 0)
    {
        LPIT_MSR |= (1 << TIF1_BIT);
        return;
    }

	switch(scan_index)
	{
		case 0:
	    	displayDigit6(gear);
	        break;
	    case 1:
	        displayDigit5(current_speed / 100000); //current_speed = 198000 -> /100000 = 1
	        break;
	    case 2:
	        displayDigit4((current_speed / 10000) % 10); //current_speed = 198000 -> /10000 %10 = 9
	        break;
	    case 3:
	        displayDigit3((current_speed/ 1000) % 10); //current_speed = 198000 -> /1000 %10 = 8
	        break;
	    case 4:
	        displayDigit2((distance / 10) % 10);
	        break;
	    case 5:
	        displayDigit1(distance % 10);
	        break;
	    }

	scan_index++;
	if (scan_index > 5)
	{
	    scan_index = 0; 
	}

	LPIT_MSR |= (1 << TIF1_BIT);
}

void LPIT0_Ch2_IRQHandler(void)
{
    // 1ms마다 실행되는 인터럽트 핸들러
    // 필요한 작업 수행

    LPIT_MSR |= (1<<TIF2_BIT); // Flag Clear
}


void PORTA_IRQHandler(void)
{
     // 시동 버튼 (PTA13)이 인터럽트를 발생시켰는지 확인
     
    if (PORTA_PCR13 & (1 << ISF_BIT))
    {
        if (Start_Flag == 0) //시동 off 상태일때
        {
           Start_Flag = 1; //시동 on
        }
        else 
        {
            if(current_state == STATE_P && current_speed==0 )
            {
                Start_Flag = 0; //시동 on이고 p이면서 속도 0이면 시동 off
            }
        }

        PORTA_PCR13 |= (1 << ISF_BIT);
    }

    // 기어 버튼 (PTA12)이 인터럽트를 발생시켰는지 확인

    if (PORTA_PCR12 & (1 << ISF_BIT))
    {
        if (Start_Flag == 1) // 시동 on 상태에서만 기어 변경 가능
        {
            Gear_Flag = 1; 
        }

        PORTA_PCR12 |= (1 << ISF_BIT);
    }
}


void PORTC_IRQHandler(void)
{
    // 가속 버튼 (PTC17)이 인터럽트를 발생시켰는지 확인
   
    if (PORTC_PCR17 & (1 << ISF_BIT)) 
    {
        if(Start_Flag ==1)
        {
            if(current_state == STATE_D || current_state == STATE_R)
            {
                // 가속 버튼의 현재 상태 확인 (눌림/떼짐)
                if ((GPIOC_PDIR & (1 << PTC17)) == 0) // Low = 눌림
                {
                    Accel_Flag = 1;
                    Brake_Flag = 0;
                }
                else // High = 떼짐
                {
                    Accel_Flag = 0; // 가속 중지
                }
            }
        }
        PORTC_PCR17 |= (1 << ISF_BIT);
    }

    // 브레이크 버튼 (PTC16)이 인터럽트를 발생시켰는지 확인
   
    if (PORTC_PCR16 & (1 << ISF_BIT)) 
    {
        if(Start_Flag ==1)
        {
            if(current_state == STATE_D || current_state == STATE_R)
            {
                // 브레이크 버튼의 현재 상태 확인 (눌림/떼짐)
                if ((GPIOC_PDIR & (1 << PTC16)) == 0) // Low = 눌림
                {
                    if (Cruise_Flag == 1) // 크루즈 켜져 있으면
                    {
                        Cruise_Flag = 0; // 크루즈 끄기
                    }
                    Accel_Flag = 0;
                    Brake_Flag = 1; // 브레이크 작동
                }
                else // High = 떼짐
                {
                    Brake_Flag = 0; // 브레이크 해제
                }
            }
        }
        PORTC_PCR16 |= (1 << ISF_BIT);
    }

    // 오토크루즈 버튼 (PTC15)이 인터럽트를 발생시켰는지 확인

    if (PORTC_PCR15 & (1 << ISF_BIT)) 
    {
        if(Start_Flag == 1)
        {
            if(Cruise_Flag == 0)
            {
                if(current_state == STATE_D)
                {
                    Cruise_Flag = 1;
                    Accel_Flag = 1; // 크루즈 모드 진입 시 가속 유지
                }
            }
            else
            {
                Cruise_Flag = 0;
            }
        }

            PORTC_PCR15 |= (1 << ISF_BIT);
    }
}
