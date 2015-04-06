
#ifndef PULSE_OXI_H
#define PULSE_OXI_H

#include "circularBuffer.h"
#include "osal.h"

// no. of process
#define         no_process     4  


// process id
#define         red_on          0
#define         red_adc         1
#define         ir_on           2
#define         ir_adc          3


// delay time in ms
#define red_on_delay            1
#define red_adc_read_delay      1
#define ir_on_delay             1
#define ir_adc_read_delay       1


struct process_queue
{
  uint8         process_id[10];// name of of the process,process in sequence
  uint8         time[10];// delay in process  next process
  uint8         process_pointer;// pointer to process,next process to be process
};


void init_process_queue(void);
bool process_queue(void);

#endif
