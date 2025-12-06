#include "seven_segment.h"
#include "regs_config.h"
#include "clocks_and_modes.h"
#include "Motor.h"

void PORT_init_Segment()
{
	PCC_PORTA |= (1<<CGC_BIT);

	PORTA_PCR12 &= ~((0b111)<<MUX_BITS);
	PORTA_PCR12 |= (1<<MUX_BITS);

	GPIOA_PDDR &= ~(1<<PTA12);

	PORTA_PCR12 &= ~((0b1111)<<IRQC_BITS);
	PORTA_PCR12 |= ((0b1001)<<IRQC_BITS);

	PCC_PORTB |= (1<<CGC_BIT);

	PORTB_PCR8	&=	~((0b111)<<MUX_BITS);
	PORTB_PCR8	|=	((0b001)<<MUX_BITS);
	PORTB_PCR9	&=	~((0b111)<<MUX_BITS);
	PORTB_PCR9	|=	((0b001)<<MUX_BITS);
	PORTB_PCR10	&=	~((0b111)<<MUX_BITS);
	PORTB_PCR10	|=	((0b001)<<MUX_BITS);
	PORTB_PCR11	&=	~((0b111)<<MUX_BITS);
	PORTB_PCR11	|=	((0b001)<<MUX_BITS);
	PORTB_PCR12	&=	~((0b111)<<MUX_BITS);
	PORTB_PCR12	|=	((0b001)<<MUX_BITS);
	PORTB_PCR13	&=	~((0b111)<<MUX_BITS);
	PORTB_PCR13	|=	((0b01)<<MUX_BITS);

	GPIOB_PDDR	|=	(1<<PTB8) | (1<<PTB9) | (1<<PTB10)	|	(1<<PTB11) | (1<<PTB12) | (1<<PTB13);

	PCC_PORTD |= (1<<CGC_BIT);

	PORTD_PCR3	&=	~((0b111)<<MUX_BITS);
	PORTD_PCR3	|=	((0b001)<<MUX_BITS);
	PORTD_PCR5	&=	~((0b111)<<MUX_BITS);
	PORTD_PCR5	|=	((0b001)<<MUX_BITS);
	PORTD_PCR8	&=	~((0b111)<<MUX_BITS);
	PORTD_PCR8	|=	((0b001)<<MUX_BITS);
	PORTD_PCR9	&=	~((0b111)<<MUX_BITS);
	PORTD_PCR9	|=	((0b001)<<MUX_BITS);
	PORTD_PCR12	&=	~((0b111)<<MUX_BITS);
	PORTD_PCR12	|=	((0b001)<<MUX_BITS);
	PORTD_PCR13	&=	~((0b111)<<MUX_BITS);
	PORTD_PCR13	|=	((0b001)<<MUX_BITS);
	PORTD_PCR14	&=	~((0b111)<<MUX_BITS);
	PORTD_PCR14	|=	((0b001)<<MUX_BITS);

	GPIOD_PDDR	|=	(1<<PTD3) | (1<<PTD5) | (1<<PTD8) | (1<<PTD9) | (1<<PTD12) | (1<<PTD13) | (1<<PTD14);
}

void NVIC_init_IRQs(void)
{
	NVIC_ICPR1 |= (1<<(48%32));
	NVIC_ISER1 |= (1<<(48%32));
	NVIC_IPR48 = 5;

	NVIC_ICPR1 |= (1<<(59%32));
	NVIC_ISER1 |= (1<<(59%32));
	NVIC_IPR59 = 10;
}

void LPIT0_init(void)
{
	PCC_LPIT &= ~((0b111)<<PCS_BITS);
	PCC_LPIT |= ((0b110)<<PCS_BITS);
	PCC_LPIT |= (1<<CGC_BIT);

	LPIT_MCR |= (1<<M_CEN_BIT);

	LPIT_MIER |= (1<<TIE0_BIT);

	LPIT_TVAL0 = 20000;

	LPIT_TCTRL0 &= ~((0b11)<<MODE_BITS);
	LPIT_TCTRL0 |= (1<<T_EN_BIT);
}

void set7segmentNumClear()
{
	GPIOD_PCOR |= (1<<PTD3) | (1<<PTD5) | (1<<PTD8) | (1<<PTD9) | (1<<PTD12) | (1<<PTD13) | (1<<PTD14);
}

void set7segmentNum0()
{
	GPIOD_PSOR |= (1<<PTD5) | (1<<PTD8) | (1<<PTD9) | (1<<PTD12) | (1<<PTD13) | (1<<PTD14);
	GPIOD_PCOR |= (1<<PTD3);
}

void set7segmentNum1()
{
	GPIOD_PSOR |= (1<<PTD9) | (1<<PTD12);
	GPIOD_PCOR |= (1<<PTD3) | (1<<PTD5) | (1<<PTD8) | (1<<PTD13) | (1<<PTD14);
}

void set7segmentNum2()
{
	GPIOD_PSOR |= (1<<PTD3) | (1<<PTD5) | (1<<PTD8) | (1<<PTD9) | (1<<PTD13);
	GPIOD_PCOR |= (1<<PTD12) | (1<<PTD14);
}

void set7segmentNum3()
{
	GPIOD_PSOR |= (1<<PTD3) | (1<<PTD5) | (1<<PTD8) | (1<<PTD9) | (1<<PTD12);
	GPIOD_PCOR |= (1<<PTD13) | (1<<PTD14);
}

void set7segmentNum4()
{
	GPIOD_PSOR |= (1<<PTD3) | (1<<PTD9) | (1<<PTD12) | (1<<PTD14);
	GPIOD_PCOR |= (1<<PTD5) | (1<<PTD8) | (1<<PTD13);
}

void set7segmentNum5()
{
	GPIOD_PSOR |= (1<<PTD3) | (1<<PTD5) | (1<<PTD8) | (1<<PTD12) | (1<<PTD14);
	GPIOD_PCOR |= (1<<PTD9) | (1<<PTD13);
}

void set7segmentNum6()
{
	GPIOD_PSOR |= (1<<PTD3) | (1<<PTD5) | (1<<PTD8) | (1<<PTD12) | (1<<PTD13) | (1<<PTD14);
	GPIOD_PCOR |= (1<<PTD9);
}

void set7segmentNum7()
{
	GPIOD_PSOR |= (1<<PTD8) | (1<<PTD9) | (1<<PTD12) | (1<<PTD14);
	GPIOD_PCOR |= (1<<PTD3) | (1<<PTD5) | (1<<PTD13);
}

void set7segmentNum8()
{
	GPIOD_PSOR |= (1<<PTD3) | (1<<PTD5) | (1<<PTD8) | (1<<PTD9) | (1<<PTD12) | (1<<PTD13) | (1<<PTD14);
}

void set7segmentNum9()
{
	GPIOD_PSOR |= (1<<PTD3) | (1<<PTD5) | (1<<PTD8) | (1<<PTD9) | (1<<PTD12) | (1<<PTD14);
	GPIOD_PCOR |= (1<<PTD13);
}

void set7segmentDrive()
{
	GPIOD_PSOR |= (1<<PTD3) | (1<<PTD5) | (1<<PTD9) | (1<<PTD12) | (1<<PTD13);
	GPIOD_PCOR |= (1<<PTD8) | (1<<PTD14);
}

void set7segmentReverse()
{
	GPIOD_PSOR |= (1<<PTD8) | (1<<PTD13) | (1<<PTD14);
	GPIOD_PCOR |= (1<<PTD3) | (1<<PTD5) | (1<<PTD9) | (1<<PTD12);
}

void set7segmentCruise()
{
	GPIOD_PSOR |= (1<<PTD5) | (1<<PTD8) | (1<<PTD13) | (1<<PTD14);
	GPIOD_PCOR |= (1<<PTD3) | (1<<PTD9) | (1<<PTD12);
}

void set7segmentNum(int num)
{
	switch(num)
	{
		case 0 :
			set7segmentNum0();
			break;

		case 1 :
			set7segmentNum1();
			break;

		case 2 :
			set7segmentNum2();
			break;

		case 3 :
			set7segmentNum3();
			break;

		case 4 :
			set7segmentNum4();
			break;

		case 5 :
			set7segmentNum5();
			break;

		case 6 :
			set7segmentNum6();
			break;

		case 7 :
			set7segmentNum7();
			break;

		case 8 :
			set7segmentNum8();
			break;

		case 9 :
			set7segmentNum9();
			break;

		default:
			set7segmentNumClear();
	}
}

void set7segmentStr(char mode)
{
	switch(mode)
	{
    case 'd':
    	set7segmentDrive();
        break;

    case 'r':
    	set7segmentReverse();
        break;

    case 'c':
    	set7segmentCruise();
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

void displayDigit6(char mode)
{
	GPIOB_PSOR |= (1<<PTB13);

	set7segmentStr(mode);
}

volatile char gear = 'd';
volatile int distance =88;
volatile int scan_index = 0;


void PORTA_IRQHandler(void)
{
    if (gear == 'd')
    {
        gear = 'r';
    }
    else
    {
        gear = 'd';
    }

    PORTA_PCR12 |= (1 << ISF_BIT);         /* Clear ISF BIT */
}

	void LPIT0_Ch0_IRQHandler(void)
	{
	    displayDigitClear();

	    switch(scan_index)
	    {
	        case 0:
	            displayDigit6(gear);
	            break;
	        case 1:
	            displayDigit5(current_speed / 100);
	            break;
	        case 2:
	            displayDigit4((current_speed / 10) % 10);
	            break;
	        case 3:
	            displayDigit3(current_speed % 10);
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

	    LPIT_MSR |= (1 << TIF0_BIT);
	}
