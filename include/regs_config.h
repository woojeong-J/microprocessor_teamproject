#ifndef regs_config_H
#define regs_config_H
#include <stdint.h>

#define PCC_BASE 	(0x40065000)
#define PCC_PORTA 	*((volatile unsigned*)(PCC_BASE + 0X124))
#define PCC_PORTB 	*((volatile unsigned*)(PCC_BASE + 0X128))
#define PCC_PORTC 	*((volatile unsigned*)(PCC_BASE + 0X12C))
#define PCC_PORTD 	*((volatile unsigned*)(PCC_BASE + 0X130))
#define PCC_PORTE 	*((volatile unsigned*)(PCC_BASE + 0X134))
#define PCC_FTM2 	*((volatile unsigned*)(PCC_BASE + 0XE8))
#define PCC_ADC0    *((volatile unsigned*)(PCC_BASE + 0xEC))
#define PCC_LPIT    *((volatile unsigned*)(PCC_BASE + 0xDC))

#define CGC_BIT 	30
#define PCS_BITS 	24

// PORT Registers
#define PORTA_BASE 	(0x40049000)
#define PORTA_PCR0  *((volatile unsigned*)(PORTA_BASE + 0x0)) // led 5
#define PORTA_PCR1  *((volatile unsigned*)(PORTA_BASE + 0x4)) // led 4
#define PORTA_PCR12 *((volatile unsigned*)(PORTA_BASE + 0x30))  //sw4 기어버튼
#define PORTA_PCR13 *((volatile unsigned*)(PORTA_BASE + 0x34))  //sw5 시동버튼

#define PORTB_BASE 	(0x4004A000)
#define PORTB_PCR0 *((volatile unsigned*)(PORTB_BASE + 0x0)) //port B 0 - 가변 저항 값 읽기 (ADC)
#define PORTB_PCR8	*((volatile unsigned*)(PORTB_BASE + 0x20)) //com1
#define PORTB_PCR9	*((volatile unsigned*)(PORTB_BASE + 0x24)) //com2
#define PORTB_PCR10	*((volatile unsigned*)(PORTB_BASE + 0x28)) //com3
#define PORTB_PCR11	*((volatile unsigned*)(PORTB_BASE + 0x2C)) //com4
#define PORTB_PCR12	*((volatile unsigned*)(PORTB_BASE + 0x30)) //com5
#define PORTB_PCR13	*((volatile unsigned*)(PORTB_BASE + 0x34)) //com6

#define PORTC_BASE 	(0x4004B000)
#define PORTC_PCR12 *((volatile unsigned*)(PORTC_BASE + 0x30)) // 스위치1 (오른쪽 방향)
#define PORTC_PCR13 *((volatile unsigned*)(PORTC_BASE + 0x34)) // 스위치2 (왼쪽 방향)
#define PORTC_PCR15 *((volatile unsigned*)(PORTC_BASE + 0x3C)) //sw1 오토크루즈 버튼
#define PORTC_PCR16 *((volatile unsigned*)(PORTC_BASE + 0x40)) //sw2 브레이크 버튼
#define PORTC_PCR17 *((volatile unsigned*)(PORTC_BASE + 0x44)) //sw3 가속버튼

#define PORTD_BASE 	(0x4004C000)
#define PORTD_PCR10 *((volatile unsigned*)(PORTD_BASE + 0x28)) //port D 10 - DC motor 제어 (PWM)
#define PORTD_PCR11 *((volatile unsigned*)(PORTD_BASE + 0x2C)) //port D 11 - servo motor 제어 (PWM)
#define PORTD_PCR3  *((volatile unsigned*)(PORTD_BASE + 0xC))  //seg a
#define PORTD_PCR5	*((volatile unsigned*)(PORTD_BASE + 0x14)) //seg b
#define PORTD_PCR8  *((volatile unsigned*)(PORTD_BASE + 0x20)) //seg c
#define PORTD_PCR9	*((volatile unsigned*)(PORTD_BASE + 0x24)) //seg d
#define PORTD_PCR12	*((volatile unsigned*)(PORTD_BASE + 0x30)) //seg e
#define PORTD_PCR13	*((volatile unsigned*)(PORTD_BASE + 0x34)) //seg f
#define PORTD_PCR14	*((volatile unsigned*)(PORTD_BASE + 0x38)) //seg g

#define PORTD_PCR15    *((volatile unsigned*)(PORTD_BASE + 0x3C)) //led red

#define PORTE_BASE 	(0x4004D000)
#define PORTE_PCR14 *((volatile unsigned*)(PORTE_BASE + 0x38)) // led 3
#define PORTE_PCR15 *((volatile unsigned*)(PORTE_BASE + 0x3C)) // led 2
#define PORTE_PCR16 *((volatile unsigned*)(PORTE_BASE + 0x40)) // led 1

#define PTA0    0 // led 5
#define PTA1    1 // led 4
#define PTA12 12 // sw4 기어버튼
#define PTA13 13 // sw5 시동버튼

#define PTC12   12  // 스위치1 (오른쪽 방향)
#define PTC13   13  // 스위치2 (왼쪽 방향)
#define PTC15 15 // sw1 오토크루즈 버튼
#define PTC16 16 // sw2 브레이크 버튼
#define PTC17 17 // sw3 가속버튼

#define PTB8	8	//com1
#define PTB9	9	//com2
#define PTB10	10	//com3
#define PTB11	11	//com4
#define PTB12	12	//com5
#define PTB13	13	//com6

#define PTD8	8   //A
#define	PTD9	9	//B
#define PTD12	12	//C
#define PTD5	5	//D
#define PTD13	13	//E
#define PTD14	14	//F
#define	PTD3	3	//G

#define PTD15   15  //led red

#define PTE14   14 // led 3
#define PTE15   15 // led 2
#define PTE16   16 // led 1

#define MUX_BITS 	8

// FTM2 Registers
#define FTM2_BASE 	(0x4003A000)
#define FTM2_SC 	*((volatile unsigned*)(FTM2_BASE + 0X0))
#define FTM2_MOD 	*((volatile unsigned*)(FTM2_BASE + 0X8))
#define FTM2_C0SC 	*((volatile unsigned*)(FTM2_BASE + 0XC)) // FTM2 CH0
#define FTM2_C0V 	*((volatile unsigned*)(FTM2_BASE + 0X10)) // FTM2 CH0
#define FTM2_CNTIN 	*((volatile unsigned*)(FTM2_BASE + 0X4C))

#define FTM2_C1SC   *((volatile unsigned*)(FTM2_BASE + 0X14)) // FTM2 CH1
#define FTM2_C1V    *((volatile unsigned*)(FTM2_BASE + 0X18)) // FTM2 CH1

#define PWMEN0_BIT 	16
#define PWMEN1_BIT 	17
#define CLKS_BITS 	3
#define PS_BITS 	0
#define MSB_BIT 	5
#define MSA_BIT 	4
#define ELSB_BIT 	3
#define ELSA_BIT 	2

// LPIT Registers
#define LPIT_BASE 	(0x40037000)
#define LPIT_MCR	*(volatile unsigned*)(LPIT_BASE + 0x8)
#define LPIT_MSR	*(volatile unsigned*)(LPIT_BASE + 0xC)
#define LPIT_MIER	*(volatile unsigned*)(LPIT_BASE + 0x10)

#define LPIT_TVAL0	*(volatile unsigned*)(LPIT_BASE + 0x20)
#define LPIT_TCTRL0	*(volatile unsigned*)(LPIT_BASE + 0x28)

#define LPIT_TVAL1	*(volatile unsigned*)(LPIT_BASE + 0x30)
#define LPIT_TCTRL1	*(volatile unsigned*)(LPIT_BASE + 0x38)

#define LPIT_TVAL2    *(volatile unsigned*)(LPIT_BASE + 0x40)
#define LPIT_TCTRL2   *(volatile unsigned*)(LPIT_BASE + 0x48)

#define M_CEN_BIT 	0

#define TIF0_BIT 	0
#define TIF1_BIT 	1
#define TIF2_BIT 	2

#define TIE0_BIT 	0
#define TIE1_BIT 	1
#define TIE2_BIT 	2

#define MODE_BITS   2
#define T_EN_BIT 	0

// NVIC Registers
#define NVIC_ISER_BASE      (0xE000E100)
#define NVIC_ISER1          *((volatile unsigned*)(NVIC_ISER_BASE + 0x4))

#define NVIC_ICPR_BASE      (0xE000E280)
#define NVIC_ICPR1          *((volatile unsigned*)(NVIC_ICPR_BASE + 0x4))

#define NVIC_IPR_BASE       (0xE000E400)
#define NVIC_IPR61          *((volatile unsigned char*)(NVIC_IPR_BASE + 0x3D)) // 61 = 0x3D
#define NVIC_IPR48          *((volatile unsigned char*)(NVIC_IPR_BASE + 0x30)) // 48 = 0x30
#define NVIC_IPR59          *((volatile unsigned char*)(NVIC_IPR_BASE + 0x3B)) // 56 = 0x38

#define IRQC_BITS 	16
#define ISF_BIT 	24

// ADC0 Registers
#define ADC0_BASE       (0x4003B000)
#define ADC0_SC1A       *((volatile unsigned *)(ADC0_BASE + 0x0))
#define ADC0_CFG1       *((volatile unsigned *)(ADC0_BASE + 0x40))
#define ADC0_CFG2       *((volatile unsigned *)(ADC0_BASE + 0x44))
#define ADC0_RA         *((volatile unsigned *)(ADC0_BASE + 0x48))
#define ADC0_SC2        *((volatile unsigned *)(ADC0_BASE + 0x90))
#define ADC0_SC3        *((volatile unsigned *)(ADC0_BASE + 0x94))

#define ADCH_BITS       0
#define COCO_BIT        7
#define MODE_BITS       2
#define ADIV_BITS       5
#define SMPLTS_BITS     0
#define ADTRG_BIT       6
#define ADC0_SE4        4

// GPIO Registers
#define GPIOA_BASE (0x400FF000)
#define GPIOA_PSOR (*((volatile unsigned*)(GPIOA_BASE + 0x4)))
#define GPIOA_PCOR (*((volatile unsigned*)(GPIOA_BASE + 0x8)))
#define GPIOA_PTOR (*((volatile unsigned*)(GPIOA_BASE + 0xC)))
#define GPIOA_PDDR (*((volatile unsigned*)(GPIOA_BASE + 0x14)))
#define GPIOA_PDIR (*((volatile unsigned*)(GPIOA_BASE + 0x10)))

#define GPIOC_BASE (0x400FF080)
#define GPIOC_PSOR (*((volatile unsigned*)(GPIOC_BASE + 0x4)))
#define GPIOC_PCOR (*((volatile unsigned*)(GPIOC_BASE + 0x8)))
#define GPIOC_PTOR (*((volatile unsigned*)(GPIOC_BASE + 0xC)))
#define GPIOC_PDDR (*((volatile unsigned*)(GPIOC_BASE + 0x14)))
#define GPIOC_PDIR (*((volatile unsigned*)(GPIOC_BASE + 0x10)))

#define GPIOB_BASE (0x400FF040)
#define GPIOB_PSOR (*((volatile unsigned*)(GPIOB_BASE + 0x4)))
#define GPIOB_PCOR (*((volatile unsigned*)(GPIOB_BASE + 0x8)))
#define GPIOB_PTOR (*((volatile unsigned*)(GPIOB_BASE + 0xC)))
#define GPIOB_PDDR (*((volatile unsigned*)(GPIOB_BASE + 0x14)))
#define GPIOB_PDIR (*((volatile unsigned*)(GPIOB_BASE + 0x10)))

#define GPIOD_BASE	(0x400FF0C0)
#define GPIOD_PSOR (*((volatile unsigned*)(GPIOD_BASE + 0x4)))
#define GPIOD_PCOR (*((volatile unsigned*)(GPIOD_BASE + 0x8)))
#define GPIOD_PTOR (*((volatile unsigned*)(GPIOD_BASE + 0xC)))
#define GPIOD_PDDR (*((volatile unsigned*)(GPIOD_BASE + 0x14)))
#define GPIOD_PDIR (*((volatile unsigned*)(GPIOD_BASE + 0x10)))

#define GPIOE_BASE  (0x400FF100)
#define GPIOE_PSOR (*((volatile unsigned*)(GPIOE_BASE + 0x4)))
#define GPIOE_PCOR (*((volatile unsigned*)(GPIOE_BASE + 0x8)))
#define GPIOE_PTOR (*((volatile unsigned*)(GPIOE_BASE + 0xC)))
#define GPIOE_PDDR (*((volatile unsigned*)(GPIOE_BASE + 0x14)))
#define GPIOE_PDIR (*((volatile unsigned*)(GPIOE_BASE + 0x10)))

#endif
