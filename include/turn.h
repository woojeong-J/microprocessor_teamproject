#ifndef turn_H
#define turn_H

#include "regs_config.h"
#include "handler.h"
#include "clocks_and_modes.h"

extern volatile int mode;   // 0=정지(center), 1=왼쪽(C13), 2=오른쪽(C12)
extern volatile int step;   // 0~4 LED 순서

void PORT_init_turn(void);
void FTM2_CH1_PWM(void);

#define SERVO_LEFT   1200
#define SERVO_RIGHT  5200
#define SERVO_CENTER 3200

#endif