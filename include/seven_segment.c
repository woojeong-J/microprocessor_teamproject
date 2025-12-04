/*
 * seven_segment.c
 *
 *  Created on: 2025. 10. 17.
 *      Author: wooju
 */
#include "seven_segment.h"


void PORT_init_sevensegment()
{
    /* Initialization for GPIO Output */
    PCC_PORTB |= (1<<CGC_BIT);        /* Enable clocks to peripherals (PORT modules) */
                                      /* Enable clock to PORT B */

    PORTB_PCR8  &= ~((0b111)<<MUX_BITS);  /* PORT B8: MUX = Alternative1 (GPIO) */
    PORTB_PCR8  |=  ((0b001)<<MUX_BITS);
    PORTB_PCR9  &= ~((0b111)<<MUX_BITS);  /* PORT B9: MUX = Alternative1 (GPIO) */
    PORTB_PCR9  |=  ((0b001)<<MUX_BITS);
    PORTB_PCR10 &= ~((0b111)<<MUX_BITS);  /* PORT B10: MUX = Alternative1 (GPIO) */
    PORTB_PCR10 |=  ((0b001)<<MUX_BITS);
    PORTB_PCR11 &= ~((0b111)<<MUX_BITS);  /* PORT B11: MUX = Alternative1 (GPIO) */
    PORTB_PCR11 |=  ((0b001)<<MUX_BITS);
    PORTB_PCR12 &= ~((0b111)<<MUX_BITS);  /* PORT B12: MUX = Alternative1 (GPIO) */
    PORTB_PCR12 |=  ((0b001)<<MUX_BITS);
    PORTB_PCR13 &= ~((0b111)<<MUX_BITS);  /* PORT B13: MUX = Alternative1 (GPIO) */
    PORTB_PCR13 |=  ((0b001)<<MUX_BITS);

    GPIOB_PDDR |= (1<<PTB8) | (1<<PTB9) | (1<<PTB10) | (1<<PTB11) | (1<<PTB12) | (1<<PTB13);
                                      /* PORT B8-13: GPIO output */



    /* Initialization for GPIO Output */
    PCC_PORTD |= (1<<CGC_BIT);        /* Enable clocks to peripherals (PORT modules) */
                                      /* Enable clock to PORT D */

    PORTD_PCR5  &= ~((0b111)<<MUX_BITS);  /* PORT D5: MUX = Alternative1 (GPIO) */
    PORTD_PCR5  |=  ((0b001)<<MUX_BITS);
    PORTD_PCR10 &= ~((0b111)<<MUX_BITS);  /* PORT D10: MUX = Alternative1 (GPIO) */
    PORTD_PCR10 |=  ((0b001)<<MUX_BITS);
    PORTD_PCR11 &= ~((0b111)<<MUX_BITS);  /* PORT D11: MUX = Alternative1 (GPIO) */
    PORTD_PCR11 |=  ((0b001)<<MUX_BITS);
    PORTD_PCR12 &= ~((0b111)<<MUX_BITS);  /* PORT D12: MUX = Alternative1 (GPIO) */
    PORTD_PCR12 |=  ((0b001)<<MUX_BITS);
    PORTD_PCR13 &= ~((0b111)<<MUX_BITS);  /* PORT D13: MUX = Alternative1 (GPIO) */
    PORTD_PCR13 |=  ((0b001)<<MUX_BITS);
    PORTD_PCR14 &= ~((0b111)<<MUX_BITS);  /* PORT D14: MUX = Alternative1 (GPIO) */
    PORTD_PCR14 |=  ((0b001)<<MUX_BITS);

    GPIOD_PDDR |= (1<<PTD5) | (1<<PTD10) | (1<<PTD11) | (1<<PTD12) | (1<<PTD13) | (1<<PTD14);
                                      /* PORT D5, D10-14: GPIO output */

    /* Initialization for GPIO Output */
    PCC_PORTE |= (1<<CGC_BIT);        /* Enable clocks to peripherals (PORT modules) */
                                      /* Enable clock to PORT E */

    PORTE_PCR15 &= ~((0b111)<<MUX_BITS);  /* PORT E15: MUX = Alternative1 (GPIO) */
    PORTE_PCR15 |=  ((0b001)<<MUX_BITS);
    PORTE_PCR16 &= ~((0b111)<<MUX_BITS);  /* PORT E16: MUX = Alternative1 (GPIO) */
    PORTE_PCR16 |=  ((0b001)<<MUX_BITS);

    GPIOE_PDDR |= (1<<PTE15) | (1<<PTE16);
                                      /* PORT E15-16: GPIO output */
}
void set7segmentNumClear()
{
    GPIOD_PCOR |= (1<<PTD10) | (1<<PTD11) | (1<<PTD12) | (1<<PTD5) | (1<<PTD13) | (1<<PTD14);
    GPIOE_PCOR |= (1<<PTE15) | (1<<PTE16);
}

void set7segmentNum0()
{
    GPIOD_PSOR |= (1<<PTD10) | (1<<PTD11) | (1<<PTD12) | (1<<PTD5) | (1<<PTD13) | (1<<PTD14);
    GPIOE_PCOR |= (1<<PTE15) | (1<<PTE16);
}

void set7segmentNum1()
{
    GPIOD_PSOR |= (1<<PTD11) | (1<<PTD12);
    GPIOD_PCOR |= (1<<PTD10) | (1<<PTD5) | (1<<PTD13) | (1<<PTD14);
    GPIOE_PCOR |= (1<<PTE15) | (1<<PTE16);
}

void set7segmentNum2()
{
    GPIOD_PSOR |= (1<<PTD10) | (1<<PTD11) | (1<<PTD5) | (1<<PTD13);
    GPIOD_PCOR |= (1<<PTD12) | (1<<PTD14);
    GPIOE_PSOR |= (1<<PTE15);
    GPIOE_PCOR |= (1<<PTE16);
}

void set7segmentNum3()
{
    GPIOD_PSOR |= (1<<PTD10) | (1<<PTD11) | (1<<PTD12) | (1<<PTD5);
    GPIOD_PCOR |= (1<<PTD13) | (1<<PTD14);
    GPIOE_PSOR |= (1<<PTE15);
    GPIOE_PCOR |= (1<<PTE16);
}

void set7segmentNum4()
{
    GPIOD_PSOR |= (1<<PTD11) | (1<<PTD12)| (1<<PTD14);
    GPIOD_PCOR |= (1<<PTD10) | (1<<PTD5) | (1<<PTD13);
    GPIOE_PSOR |= (1<<PTE15);
    GPIOE_PCOR |= (1<<PTE16);
}

void set7segmentNum5()
{
    GPIOD_PSOR |= (1<<PTD10) | (1<<PTD12) | (1<<PTD5) | (1<<PTD14);
    GPIOD_PCOR |= (1<<PTD11) | (1<<PTD13);
    GPIOE_PSOR |= (1<<PTE15);
    GPIOE_PCOR |= (1<<PTE16);
}

void set7segmentNum6()
{
    GPIOD_PSOR |= (1<<PTD10) | (1<<PTD12) | (1<<PTD5) | (1<<PTD13) | (1<<PTD14);
    GPIOD_PCOR |= (1<<PTD11);
    GPIOE_PSOR |= (1<<PTE15);
    GPIOE_PCOR |= (1<<PTE16);
}

void set7segmentNum7()
{
    GPIOD_PSOR |= (1<<PTD10) | (1<<PTD11) | (1<<PTD12) | (1<<PTD14);
    GPIOD_PCOR |= (1<<PTD5) | (1<<PTD13);
    GPIOE_PCOR |= (1<<PTE15) | (1<<PTE16);
}

void set7segmentNum8()
{
    GPIOD_PSOR |= (1<<PTD10) | (1<<PTD11) | (1<<PTD12) | (1<<PTD5) | (1<<PTD13) | (1<<PTD14);
    GPIOE_PSOR |= (1<<PTE15);
    GPIOE_PCOR |= (1<<PTE16);
}

void set7segmentNum9()
{
    GPIOD_PSOR |= (1<<PTD10) | (1<<PTD11) | (1<<PTD12) | (1<<PTD5) | (1<<PTD14);
    GPIOD_PCOR |= (1<<PTD13);
    GPIOE_PSOR |= (1<<PTE15);
    GPIOE_PCOR |= (1<<PTE16);
}

void set7segmentNum(int num)
{
	switch(num)
	{
		case 0:
			set7segmentNum0();
			break;
		case 1:
			set7segmentNum1();
			break;
		case 2:
			set7segmentNum2();
			break;
		case 3:
			set7segmentNum3();
			break;
		case 4:
			set7segmentNum4();
			break;
		case 5:
			set7segmentNum5();
			break;
		case 6:
			set7segmentNum6();
			break;
		case 7:
			set7segmentNum7();
			break;
		case 8:
			set7segmentNum8();
			break;
		case 9:
			set7segmentNum9();
			break;
		default:
			set7segmentNumClear();
			break;
	}
}

void displayDigitClear()
{
    set7segmentNumClear();
    GPIOB_PCOR |= (1<<PTB8) | (1<<PTB9) | (1<<PTB10) | (1<<PTB11) | (1<<PTB12) | (1<<PTB13);
}

void displayDigit1(int num)
{
    GPIOB_PSOR |= (1<<PTB8);
    set7segmentNum(num);
}

void displayDigit2(int num)
{
    GPIOB_PSOR |= (1<<PTB9);
    set7segmentNum(num);
}

void displayDigit3(int num)
{
    GPIOB_PSOR |= (1<<PTB10);
    set7segmentNum(num);
    //GPIOE_PSOR |= (1 << PTE16); // DP
}

void displayDigit4(int num)
{
    GPIOB_PSOR |= (1<<PTB11);
    set7segmentNum(num);
}

void displayDigit5(int num)
{
    GPIOB_PSOR |= (1<<PTB12);
    set7segmentNum(num);
}

void displayDigit6(int num)
{
    GPIOB_PSOR |= (1<<PTB13);
    set7segmentNum(num);
}

void displayDigitA1(int num)
{
	int num1, num2, num3, num4, num5, num6;

	num1 = num % 10; // 1의자리
	num2 = (num / 10) % 10; // 10의자리
	num3 = (num / 100) % 10; // 100의자리
	num4 = (num / 1000) % 10; // 1000의자리
	num5 = (num / 10000) % 10;
	num6 = (num / 100000) % 10;


	displayDigitClear();
	displayDigit1(num1);

	displayDigitClear();
	displayDigit2(num2);

	displayDigitClear();
	displayDigit3(num3);

	displayDigitClear();
	displayDigit4(num4);

	displayDigitClear();
	displayDigit5(num5);

	displayDigitClear();
	displayDigit6(num6);

}

