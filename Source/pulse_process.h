#ifndef _PULSE_PROCESS_H
#define _PULSE_PROCESS_H

#include "OSAL.h"
#include "ioCC2540.h"
#include "circularBuffer.h"
#include "packet.h"

#define RED_LED P1_1
#define IR_LED  P1_0
// user board contains port connection details




// buffer function
void red_buffer_ch_0(void);
void red_buffer_ch_1(void);
void ir_buffer_ch_0(void);
void ir_buffer_ch_1(void);



bool redon(void);
void red_adc_read(void);
void iron(void);
extern void ir_adc_read(void);
void red_reference_voltage(void);
void ir_reference_voltage(void);
void pointer2buffer(CircularBuffer*);


void pointer2packet(uint8*);



#endif

