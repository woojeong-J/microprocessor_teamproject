#ifndef handler_h
#define handler_h

#include <stdint.h>

void LPIT0_init(void);
void NVIC_init_IRQs(void);
void LPIT0_Ch0_IRQHandler(void);
void LPIT0_Ch1_IRQHandler(void);
void LPIT0_Ch2_IRQHandler(void);
void PORTA_IRQHandler(void);
void PORTC_IRQHandler(void);

typedef enum {
    STATE_OFF,      // 시동 꺼짐
    STATE_P,        // 주차 (Parking)
    STATE_D,        // 주행 (Drive)
    STATE_R,        // 후진 (Reverse)
    STATE_CRUISE    // 크루즈 모드
} CarState_t;

extern volatile int Start_Flag;
extern volatile int Gear_Flag;
extern volatile int Cruise_Flag;
extern volatile int gear;
extern volatile int current_speed;
extern volatile int Accel_Flag;
extern volatile int Brake_Flag;
extern volatile uint32_t adcResult;
extern volatile CarState_t current_state;

#endif
