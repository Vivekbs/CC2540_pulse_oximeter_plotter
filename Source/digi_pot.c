#include "digi_pot.h"

void init_pot()
{
  cs=1;// active low ,disable pot
  clk=0;
  P1SEL&=~((1<<3)|(1<<4)|(1<<6));
  P1DIR|=((1<<3) | (1<<4) |(1<<6));
}

void set_pot(uint8 val)
{
  uint8 i;
  
  cs=0;
  clk=0;
  
    for(i=0;i<8;i++)
    {
      clk=0;
      
      if(val&0x80)
        data=1;
      
      else
        data=0;
        
      val=val<<1;
      clk=1;
    }
   
   cs=1;
  
}
  