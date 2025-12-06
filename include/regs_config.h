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
#define PORTA_PCR12 *((volatile unsigned*)(PORTA_BASE + 0x30))  //브레이크 버튼

#define PORTB_BASE 	(0x4004A000)
#define PORTB_PCR0 *((volatile unsigned*)(PORTB_BASE + 0x0)) //port B 0 - 가변 저항 값 읽기 (ADC)

#define PORTC_BASE 	(0x4004B000)
#define PORTC_PCR17 *((volatile unsigned*)(PORTC_BASE + 0x44)) // 가속 버튼

#define PORTD_BASE 	(0x4004C000)
#define PORTD_PCR10 *((volatile unsigned*)(PORTD_BASE + 0x28)) //port D 10 - DC motor 제어 (PWM)

#define PORTE_BASE 	(0x4004D000)

#define PTA12 12

#define PTC17 17

#define MUX_BITS 	8

// FTM2 Registers
#define FTM2_BASE 	(0x4003A000)
#define FTM2_SC 	*((volatile unsigned*)(FTM2_BASE + 0X0))
#define FTM2_MOD 	*((volatile unsigned*)(FTM2_BASE + 0X8))
#define FTM2_C0SC 	*((volatile unsigned*)(FTM2_BASE + 0XC))
#define FTM2_C0V 	*((volatile unsigned*)(FTM2_BASE + 0X10))
#define FTM2_CNTIN 	*((volatile unsigned*)(FTM2_BASE + 0X4C))

#define PWMEN0_BIT 	16
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

#define M_CEN_BIT 	0
#define TIF0_BIT 	0
#define TIE0_BIT 	0
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



#endif
