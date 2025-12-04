/*
 * seven_segment.h
 *
 *  Created on: 2025. 10. 17.
 *      Author: wooju
 */

#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_


#define PCC_BASE      (0x40065000)
#define PCC_PORTB     (*((volatile unsigned*)(PCC_BASE + 0x128)))
#define PCC_PORTD     (*((volatile unsigned*)(PCC_BASE + 0x130)))
#define PCC_PORTE     (*((volatile unsigned*)(PCC_BASE + 0x134)))


#define CGC_BIT       30

// PORT Registers

#define PORTB_BASE    (0x4004A000)
#define PORTB_PCR8    (*((volatile unsigned*)(PORTB_BASE + 0x20)))
#define PORTB_PCR9    (*((volatile unsigned*)(PORTB_BASE + 0x24)))
#define PORTB_PCR10   (*((volatile unsigned*)(PORTB_BASE + 0x28)))
#define PORTB_PCR11   (*((volatile unsigned*)(PORTB_BASE + 0x2C)))
#define PORTB_PCR12   (*((volatile unsigned*)(PORTB_BASE + 0x30)))
#define PORTB_PCR13   (*((volatile unsigned*)(PORTB_BASE + 0x34)))


#define PORTD_BASE    (0x4004C000)
#define PORTD_PCR5    (*((volatile unsigned*)(PORTD_BASE + 0x14)))
#define PORTD_PCR10   (*((volatile unsigned*)(PORTD_BASE + 0x28)))
#define PORTD_PCR11   (*((volatile unsigned*)(PORTD_BASE + 0x2C)))
#define PORTD_PCR12   (*((volatile unsigned*)(PORTD_BASE + 0x30)))
#define PORTD_PCR13   (*((volatile unsigned*)(PORTD_BASE + 0x34)))
#define PORTD_PCR14   (*((volatile unsigned*)(PORTD_BASE + 0x38)))

#define PORTE_BASE    (0x4004D000)
#define PORTE_PCR15   (*((volatile unsigned*)(PORTE_BASE + 0x3C)))
#define PORTE_PCR16   (*((volatile unsigned*)(PORTE_BASE + 0x40)))

#define MUX_BITS      8

// GPIO Registers

#define GPIOB_BASE    (0x400FF040)
#define GPIOB_PSOR    (*((volatile unsigned*)(GPIOB_BASE + 0x4)))
#define GPIOB_PCOR    (*((volatile unsigned*)(GPIOB_BASE + 0x8)))
#define GPIOB_PDDR    (*((volatile unsigned*)(GPIOB_BASE + 0x14)))


#define GPIOD_BASE    (0x400FF0C0)
#define GPIOD_PSOR    (*((volatile unsigned*)(GPIOD_BASE + 0x4)))
#define GPIOD_PCOR    (*((volatile unsigned*)(GPIOD_BASE + 0x8)))
#define GPIOD_PDDR    (*((volatile unsigned*)(GPIOD_BASE + 0x14)))

#define GPIOE_BASE    (0x400FF100)
#define GPIOE_PSOR    (*((volatile unsigned*)(GPIOE_BASE + 0x4)))
#define GPIOE_PCOR    (*((volatile unsigned*)(GPIOE_BASE + 0x8)))
#define GPIOE_PDDR    (*((volatile unsigned*)(GPIOE_BASE + 0x14)))


#define PTB8          8   // COM1
#define PTB9          9   // COM2
#define PTB10         10  // COM3
#define PTB11         11  // COM4
#define PTB12         12  // COM5
#define PTB13         13  // COM6



#define PTD10         10  // SEG_A
#define PTD11         11  // SEG_B
#define PTD12         12  // SEG_C
#define PTD5          5   // SEG_D
#define PTD13         13  // SEG_E
#define PTD14         14  // SEG_F
#define PTE15         15  // SEG_G
#define PTE16         16  // SEG_DP
// D 8,9,12,13,14,3,5

void PORT_init_sevensegment();
void displayDigitA1(int num);




#endif /* SEVEN_SEGMENT_H_ */
