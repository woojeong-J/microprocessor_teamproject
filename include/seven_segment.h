#ifndef seven_segment_h
#define seven_segment_h

void PORT_init_Segment();
void NVIC_init_IRQs(void);
void LPIT0_init(void);
void set7segmentNumClear();
void set7segmentNum0();
void set7segmentNum1();
void set7segmentNum2();
void set7segmentNum3();
void set7segmentNum4();
void set7segmentNum5();
void set7segmentNum6();
void set7segmentNum7();
void set7segmentNum8();
void set7segmentNum9();
void set7segmentDrive();
void set7segmentReverse();
void set7segmentNum(int num);
void set7segmentStr(int gear);
void displayDigit1(int num);
void displayDigit2(int num);
void displayDigit3(int num);
void displayDigit4(int num);
void displayDigit5(int num);
void displayDigit6(int gear);

extern volatile int gear;

#endif