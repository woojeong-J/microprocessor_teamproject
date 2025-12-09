#include "Motor.h"
#include "regs_config.h"
#include <stdint.h>
#include "clocks_and_modes.h"
#include "handler.h"

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
	// 브레이크 버튼
	PORTC_PCR16 &= ~((0b111)<<MUX_BITS);
	PORTC_PCR16 |= (1<<MUX_BITS);  // GPIO
	PORTC_PCR16 &= ~((0b1111)<<IRQC_BITS);	 
	PORTC_PCR16 |= (0b1011<<IRQC_BITS); //either rising or falling edge
	PORTC_PCR16 |= (1<<1) | (1<<0);
	GPIOC_PDDR &= ~(1<<PTC16); // Input
	// 가속 버튼
	PORTC_PCR17 &= ~((0b111)<<MUX_BITS);
	PORTC_PCR17 |= (1<<MUX_BITS);  // GPIO
	PORTC_PCR17 &= ~((0b1111)<<IRQC_BITS);
	PORTC_PCR17 |= (0b1011<<IRQC_BITS); //either rising or falling edge
	PORTC_PCR17 |= (1<<1) | (1<<0);
	GPIOC_PDDR &= ~(1<<PTC17); // Input
	// 오토크루즈 버튼
	PORTC_PCR15 &= ~((0b111)<<MUX_BITS);
	PORTC_PCR15 |= (1<<MUX_BITS);  // GPIO
	PORTC_PCR15 &= ~((0b1111)<<IRQC_BITS);
	PORTC_PCR15 |= (0b1010<<IRQC_BITS); //falling edge
	PORTC_PCR15 |= (1<<1) | (1<<0);
	GPIOC_PDDR &= ~(1<<PTC15); // Input

	PCC_PORTA |= (1<<CGC_BIT);
	// 기어버튼
	PORTA_PCR12 &= ~((0b111)<<MUX_BITS);
	PORTA_PCR12 |= (1<<MUX_BITS);  // GPIO
	PORTA_PCR12 &= ~((0b1111)<<IRQC_BITS);
	PORTA_PCR12 |= (0b1010<<IRQC_BITS); //falling edge
	PORTA_PCR12 |= (1<<1) | (1<<0);
	GPIOA_PDDR &= ~(1<<PTA12); // Input
	// 시동버튼
	PORTA_PCR13 &= ~((0b111)<<MUX_BITS);
	PORTA_PCR13 |= (1<<MUX_BITS);  // GPIO
	PORTA_PCR13 &= ~((0b1111)<<IRQC_BITS);
	PORTA_PCR13 |= (0b1010<<IRQC_BITS); //falling edge
	PORTA_PCR13 |= (1<<1) | (1<<0);
	GPIOA_PDDR &= ~(1<<PTA13); // Input
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
