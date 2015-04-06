#ifndef PACKET_H
#define PACKET_H

#include "osal.h"

#define PACKET_LENGTH   10

struct packet_data
{
  uint8 header;
  uint8 tail;
  uint16 data1;
  uint16 data2;
  uint16 data3;
  uint16 data4;
};

void packet_assemble(uint8*,struct packet_data*);

#endif