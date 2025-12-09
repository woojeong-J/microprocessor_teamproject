#include "seven_segment.h"
#include "regs_config.h"
#include "clocks_and_modes.h"
#include "Motor.h"
#include "handler.h"

void PORT_init_Segment()
{
	//com1~6 : PTB8~PTB13
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
	//com1~6 출력으로 설정
	GPIOB_PDDR	|=	(1<<PTB8) | (1<<PTB9) | (1<<PTB10)	|	(1<<PTB11) | (1<<PTB12) | (1<<PTB13);
	
	PCC_PORTD |= (1<<CGC_BIT);
	// 세그먼트 a~g : PTD8,PTD9,PTD12,PTD5,PTD13,PTD14,PTD3
	PORTD_PCR8	&=	~((0b111)<<MUX_BITS);
	PORTD_PCR8	|=	((0b001)<<MUX_BITS);
	PORTD_PCR9	&=	~((0b111)<<MUX_BITS);
	PORTD_PCR9	|=	((0b001)<<MUX_BITS);
	PORTD_PCR12	&=	~((0b111)<<MUX_BITS);
	PORTD_PCR12	|=	((0b001)<<MUX_BITS);
	PORTD_PCR5	&=	~((0b111)<<MUX_BITS);
	PORTD_PCR5	|=	((0b001)<<MUX_BITS);
	PORTD_PCR13	&=	~((0b111)<<MUX_BITS);
	PORTD_PCR13	|=	((0b001)<<MUX_BITS);
	PORTD_PCR14	&=	~((0b111)<<MUX_BITS);
	PORTD_PCR14	|=	((0b001)<<MUX_BITS);
	PORTD_PCR3	&=	~((0b111)<<MUX_BITS);
	PORTD_PCR3	|=	((0b001)<<MUX_BITS);
	//세그먼트 a~g 출력으로 설정
	GPIOD_PDDR	|=	(1<<PTD3) | (1<<PTD5) | (1<<PTD8) | (1<<PTD9) | (1<<PTD12) | (1<<PTD13) | (1<<PTD14);
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

void set7segmentParking() //a b e f g
{
	GPIOD_PSOR |= (1<<PTD8) | (1<<PTD9) | (1<<PTD13) | (1<<PTD14) | (1<<PTD3); // a b e f g
	GPIOD_PCOR |= (1<<PTD12) | (1<<PTD5); // c d
}

void set7segmentDrive() // b c d e g
{
	GPIOD_PSOR |= (1<<PTD9) | (1<<PTD12) | (1<<PTD5) | (1<<PTD13) | (1<<PTD3); // b c d e g
	GPIOD_PCOR |= (1<<PTD8) | (1<<PTD14); // a f
}

void set7segmentReverse() // e g
{
	GPIOD_PSOR |= (1<<PTD13) | (1<<PTD3); // e g
	GPIOD_PCOR |= (1<<PTD8) | (1<<PTD9) | (1<<PTD12) | (1<<PTD5) | (1<<PTD14); // a b c d f
}

void set7segmentCruise() // a d e f
{
	GPIOD_PSOR |= (1<<PTD8) | (1<<PTD5) |  (1<<PTD13) | (1<<PTD14); // a d e f
	GPIOD_PCOR |= (1<<PTD9) | (1<<PTD12) |(1<<PTD3); // b c g
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

void displayDigit6(int gear)
{
	GPIOB_PSOR |= (1<<PTB13);

	set7segmentStr(gear);
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

void set7segmentStr(int gear)
{
	switch(gear)
	{
	case 0:
		set7segmentParking();
		break;
		
    case 1:
    	set7segmentDrive();
        break;

    case 2:
    	set7segmentReverse();
        break;

    case 3:
    	set7segmentCruise();
        break;

    default:
    	set7segmentNumClear();
        break;
	}
}