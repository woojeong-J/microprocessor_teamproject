#include "turn.h"
#include "clocks_and_modes.h"
#include "handler.h"
#include "regs_config.h"

/* ================================
 * 전역 변수
 * ================================ */
volatile int mode = 0;   // 0=정지(center), 1=왼쪽(C13), 2=오른쪽(C12)
volatile int step = 0;   // 0~4 LED 순서


/* ================================
 * PORT 초기화: 스위치 + LED + 서보핀
 * ================================ */
void PORT_init_turn(void)
{
    /* ---- PORTC: 스위치 PTC12, PTC13 ---- */
    PCC_PORTC |= (1<<CGC_BIT);  // Port C clock enable

    // PTC12, PTC13 GPIO 설정
    PORTC_PCR12 &= ~((0b111)<<MUX_BITS);
    PORTC_PCR12 |=  (1<<MUX_BITS);      // MUX = 001: GPIO
    PORTC_PCR13 &= ~((0b111)<<MUX_BITS);
    PORTC_PCR13 |=  (1<<MUX_BITS);

    // 입력 모드
    GPIOC_PDDR &= ~(1<<PTC12); // 오른쪽 방향
    GPIOC_PDDR &= ~(1<<PTC13); // 왼쪽 방향

    // 인터럽트: Falling-edge (IRQC = 1001)
    PORTC_PCR12 &= ~((0b1111)<<IRQC_BITS);
    PORTC_PCR12 |=  ((0b1001)<<IRQC_BITS);
    PORTC_PCR13 &= ~((0b1111)<<IRQC_BITS);
    PORTC_PCR13 |=  ((0b1001)<<IRQC_BITS);

    /* ---- PORTA: PTA0, PTA1 (LED) ---- */
    PCC_PORTA |= (1<<CGC_BIT);

    PORTA_PCR0 &= ~((0b111)<<MUX_BITS);
    PORTA_PCR0 |=  (1<<MUX_BITS);   //led 5
    PORTA_PCR1 &= ~((0b111)<<MUX_BITS);
    PORTA_PCR1 |=  (1<<MUX_BITS);   //led 4

    GPIOA_PDDR |= (1<<PTA0)|(1<<PTA1);  // 출력

    /* ---- PORTE: PTE14~16 (LED) ---- */
    PCC_PORTE |= (1<<CGC_BIT);

    PORTE_PCR14 &= ~((0b111)<<MUX_BITS);
    PORTE_PCR14 |=  (1<<MUX_BITS);  // led 3
    PORTE_PCR15 &= ~((0b111)<<MUX_BITS);
    PORTE_PCR15 |=  (1<<MUX_BITS);  // led 2
    PORTE_PCR16 &= ~((0b111)<<MUX_BITS);
    PORTE_PCR16 |=  (1<<MUX_BITS);  // led 1

    GPIOE_PDDR |= (1<<PTE14)|(1<<PTE15)|(1<<PTE16);  // 출력

    /* ---- PORTD: PD11 = FTM2_CH1 (서보 PWM 핀) ---- */
    PCC_PORTD |= (1<<CGC_BIT);
    PORTD_PCR11 &= ~((0b111)<<MUX_BITS);
    PORTD_PCR11 |=  ((0b010)<<MUX_BITS);   // ALT2: FTM2_CH1

    /* 처음에는 LED 모두 OFF */
    GPIOE_PSOR |= (1<<PTE14)|(1<<PTE15)|(1<<PTE16);
    GPIOA_PSOR |= (1<<PTA0)|(1<<PTA1);
}

/* ================================
 * FTM2 CH0 PWM (서보 출력)
 * ================================ */
void FTM2_CH1_PWM(void)
{
    PCC_FTM2 &= ~(1<<CGC_BIT);
    PCC_FTM2 &= ~((0b111)<<PCS_BITS);
    PCC_FTM2 |=  ((0b010)<<PCS_BITS);   // 예: SPLLDIV1
    PCC_FTM2 |=  (1<<CGC_BIT);

    // PWM enable (실습 코드 스타일 유지)
    FTM2_SC |= (1<<PWMEN1_BIT);

    // 프리스케일러 설정: /4
    FTM2_SC &= ~((0b111)<<PS_BITS);
    FTM2_SC |=  ((0b010)<<PS_BITS); // 8MHz/4 => 2MHz

    FTM2_MOD   = 40000 - 1; //2MHz / 40000 = 50Hz (20ms 필수)
    FTM2_CNTIN = 0;

    // Edge-Aligned, High-true PWM
    FTM2_C1SC |= (1<<MSB_BIT);
    FTM2_C1SC |= (1<<ELSB_BIT);
    FTM2_C1SC &= ~(1<<ELSA_BIT);

    // 클럭 소스: 시스템 클럭 선택
    FTM2_SC |= ((0b11)<<CLKS_BITS);

    // 초기값: 가운데(0도)
    FTM2_C1V = SERVO_CENTER;
}
