#include "packet.h"




void packet_assemble(uint8 *pbuff,struct packet_data *packet1)
{
  uint8 pointer;

  
  *(pbuff+0)=packet1->header;
  *(pbuff+9)=packet1->tail;
  
  *(pbuff+1)=packet1->data1;
  *(pbuff+2)=packet1->data1>>8;
    
  *(pbuff+3)=packet1->data2;
  *(pbuff+4)=packet1->data2>>8;
    
  *(pbuff+5)=packet1->data3;
  *(pbuff+6)=packet1->data3>>8;
    
  *(pbuff+7)=packet1->data4;
  *(pbuff+8)=packet1->data4>>8;
}

