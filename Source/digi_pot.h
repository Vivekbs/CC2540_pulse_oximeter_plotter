#ifndef DIGI_POT_H
#define DIGI_POT_H

#include "iocc2540.h"
#include "osal.h"



/// NOTE if PORT changed here change also in init_pot() in digi_pot
#define cs      P1_3
#define data    P1_4
#define clk     P1_6

void init_pot(void);
void set_pot(uint8);

#endif