#ifndef Motor_H
#define Motor_H
#include <stdint.h>


void PORT_init_Motor(void);
void ADC0_init(void);
void adc_start(void);
uint32_t read_adc_chx(void);
void FTM2_CH0_PWM(void);
void DRV_Control(void);
void DRV_Brake_Control(void);
void DRV_Coasting_Control(void);

#endif