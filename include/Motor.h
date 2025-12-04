#ifndef Motor_H
#define Motor_H
#include <stdint.h>


void PORT_init_Motor(void);
void ADC0_init(void);
void NVIC_init_IRQs(void);
void LPIT0_init(void);
void DRV_Control(void);
void DRV_Brake_Control(void);
void DRV_Coasting_Control(void);
void LPIT0_Ch0_IRQHandler(void);
void PORTC_IRQHandler(void);
void PORTA_IRQHandler(void);
void adc_start(void);
uint32_t read_adc_chx(void);
void FTM2_CH0_PWM(void);



extern int current_speed;
extern int max_speed;
extern int limited_speed;
extern int speed_time;
extern int Accel_Flag;
extern int Brake_Flag;

#endif