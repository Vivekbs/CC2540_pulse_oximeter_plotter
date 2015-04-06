#ifndef USER_BOARD_H
#define USER_BOARD_H

#include "ioCC2540.h"
#include "osal.h"


#define ENABLE_INTERRUPT                IEN0|=0x80
#define DISABLE_INTERRUPT               IEN0&=0x7f
#define ENABLE_TIMER1_INTERRUPT         IEN1|=0x02
#define START_TIMER1                    T1CTL|=2            
#define STOP_TIMER1                     T1CTL&=0xfc

#define FS      100     // 100Hz        sampling frequency
#define TMIN    2       // 2sec          0.5 hz ie 30BPM
#define G       68      // Gain of second stage
#define LEVEL   128     // vcc/2
#define LEN     20      // Buffer length 

void board_init(void);
void timer1_init(void);
void timer1_delay(uint8);
void uart_init(void);
void uart_send(uint8);
void adc_init(void);
void adc_conv(uint8);

#endif
