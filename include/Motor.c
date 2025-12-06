#include "Motor.h"
#include "regs_config.h"
#include <stdint.h>
#include "clocks_and_modes.h"

int current_speed = 0;
int max_speed = 200000;
int limited_speed = 0;
int speed_time = 10;
int Accel_Flag = 0;
int Brake_Flag = 0;
uint32_t adcResult = 0;

void PORT_init_Motor(void)
{
	PCC_PORTD |= (1<<CGC_BIT);
	PORTD_PCR10 &= ~((0b111)<<MUX_BITS);
	PORTD_PCR10 |= ((0b010)<<MUX_BITS);    //Gpio alternative function for FTM2_CH0


	PCC_PORTB |= (1<<CGC_BIT); // ADC용 포트
	PORTB_PCR0 &= ~((0b111)<<MUX_BITS);


	PCC_PORTC |= (1<<CGC_BIT);
	PORTC_PCR17 &= ~((0b111)<<MUX_BITS);
	PORTC_PCR17 |= (1<<MUX_BITS);  // GPIO
	PORTC_PCR17 &= ~((0b1111)<<IRQC_BITS);
	PORTC_PCR17 |= (0b1011<<IRQC_BITS);

	PORTC_PCR17 |= (1<<1) | (1<<0);

	GPIOC_PDDR &= ~(1<<PTC17); // Input

	PCC_PORTA |= (1<<CGC_BIT);
	PORTA_PCR12 &= ~((0b111)<<MUX_BITS);
	PORTA_PCR12 |= (1<<MUX_BITS);  // GPIO
	PORTA_PCR12 &= ~((0b1111)<<IRQC_BITS);
	PORTA_PCR12 |= (0b1011<<IRQC_BITS);

	PORTA_PCR12 |= (1<<1) | (1<<0);

	GPIOA_PDDR &= ~(1<<PTA12); // Input


}

void ADC0_init(void)
{
    /* ADC0 Clocking */
    PCC_ADC0 &= ~(1<<CGC_BIT);                  /* Disable clock to change PCS */
    PCC_ADC0 &= ~((0b111)<<PCS_BITS);           /* PCS=0b001: Select SOSCDIV2 */
    PCC_ADC0 |= ((0b001)<<PCS_BITS);
    PCC_ADC0 |= (1<<CGC_BIT);                   /* Enable bus clock in ADC0 */

    /* ADC0 Initialization */
    ADC0_SC1A |= ((0b111111)<<ADCH_BITS);        /* ADCH=1F: Module is disabled for conversion */

    ADC0_CFG1 &= ~((0b11)<<ADIV_BITS);          /* The divide ratio is 1 */
    ADC0_CFG1 &= ~((0b11)<<MODE_BITS);          /* MODE=1: 12-bit conversion */
    ADC0_CFG1 |= ((0b01)<<MODE_BITS);

    ADC0_CFG2 &= ~(255<<SMPLTS_BITS);           /* SMPLTS=12(default): sample time is 13 ADC clks */
    ADC0_CFG2 |= (12<<SMPLTS_BITS);

    ADC0_SC2 &= ~(1<<ADTRG_BIT);                /* ADTRG=0: SW trigger */
}

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

void FTM2_CH0_PWM(void)
{
	PCC_FTM2 &= ~(1<<CGC_BIT);
	PCC_FTM2 &= ~((0b111)<<PCS_BITS);
	PCC_FTM2 |= ((0b010)<<PCS_BITS);
	PCC_FTM2 |= (1<<CGC_BIT);

	FTM2_SC |= (1<<PWMEN0_BIT);
	FTM2_SC &= ~((0b111)<<PS_BITS);
	FTM2_SC |= ((0b001)<<PS_BITS);

	FTM2_MOD = 40000 -1; // 80MHz / 2 / 40000 = 1kHz
	FTM2_CNTIN = 0;

	FTM2_C0SC |= (1<<MSB_BIT);
	FTM2_C0SC |= (1<<ELSB_BIT);
	FTM2_C0SC &= ~(1<<ELSA_BIT);

	FTM2_SC |= ((0b11)<<CLKS_BITS);
}

void LPIT0_init(void)
{
	PCC_LPIT &= ~((0b111)<<PCS_BITS);
	PCC_LPIT |= ((0b110)<<PCS_BITS);
	PCC_LPIT |= (1<<CGC_BIT);

	LPIT_MCR |= (1<<M_CEN_BIT);

	LPIT_MIER |= (1<<TIE0_BIT);

	LPIT_TVAL0 = 400000; // 80MHz / 2 / 400000 = 100Hz -> 10ms

	LPIT_TCTRL0 &= ~((0b11)<<MODE_BITS);
	LPIT_TCTRL0 |= (1<<T_EN_BIT);
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

void LPIT0_Ch0_IRQHandler(void)
{
    // Flag Clear (생략)

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


	adc_start();
	adcResult = read_adc_chx(); //가변 저항 값 0~ 4095
	LPIT_MSR |= (1<<TIF0_BIT);
}

void PORTC_IRQHandler(void)
{
	// 가속 버튼 인터럽트 핸들러
	if((GPIOC_PDIR & (1<<PTC17)) == 0) // Low = 눌림
	    {
	        Accel_Flag = 1;
	        Brake_Flag = 0;
	    }
	    else // High = 떼짐
	    {
	        Accel_Flag = 0; // 가속 중지 (Coasting)
	    }

	    PORTC_PCR17 |= (1<<ISF_BIT); // 플래그 클리어
}

void PORTA_IRQHandler(void)
{
	// 브레이크 버튼 인터럽트 핸들러
	if((GPIOA_PDIR & (1<<PTA12)) == 0) // Low = 눌림
	    {
	        Accel_Flag = 0;
	        Brake_Flag = 1; // 브레이크 작동
	    }
	    else // High = 떼짐
	    {
	        Brake_Flag = 0; // 브레이크 해제 (Coasting)
	    }

	    PORTA_PCR12 |= (1<<ISF_BIT); // 플래그 클리어
}


void DRV_Control()
{
	//DC motor control code

	limited_speed = (max_speed * adcResult) / 4095; // 최고 한계 속도 설정
	if(current_speed <= limited_speed)
	{
		current_speed = current_speed + 200; // 가속도(s단위) 에 따라 속도 증가

	}
	else if(current_speed > limited_speed)
	{
		current_speed = limited_speed; // 최대 속도 넘어가면 최대 속도로 고정
	}
	FTM2_C0V = ((uint64_t)current_speed * FTM2_MOD) / max_speed;
}

void DRV_Brake_Control()
{
	//급제동시 DC motor 제어 코드
	if(current_speed > 0)
	{
		current_speed = current_speed - 400; // 5초만에 정지
		if(current_speed < 0)
			current_speed = 0;
	}
	FTM2_C0V = ((uint64_t)current_speed * FTM2_MOD) / max_speed; // PWM duty 변경
}

void DRV_Coasting_Control()
{
	//타력 주행시 DC motor 제어 코드
	if(current_speed > 0)
	{
		current_speed = current_speed - 100; // 20초만에 정지
		if(current_speed < 0)
			current_speed = 0;
	}
	FTM2_C0V = ((uint64_t)current_speed * FTM2_MOD) / max_speed;
}
