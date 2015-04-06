#include "user_board.h"

void board_init()
{
  // RED LED connected to P1_1 and IR LED connected to P1_0
  // set P1_0 and P1_1 as peripheril and as output port
  P1SEL&=~((1<<0)|(1<<1));
  P1DIR|=((1<<0) | (1<<1));
}

void timer1_init()
{
  // divide by 128 and count from 00 to T1CC0
  T1CTL|=((3<<2) | 2);
  T1CC0H=0xf0;
  T1CC0L=0x44;
  // enable interrupt , clear on compare , set to compare mode
  T1CCTL0|=((1<<6)|(1<<3)|(1<<2));
  //enable timer 1 interrupt
  ENABLE_TIMER1_INTERRUPT;
}


void timer1_delay(uint8 ms)
{
  // stop timer
  STOP_TIMER1;
  uint16 t1Val;
  // reload timer value
  t1Val=150*ms;
  T1CC0L=t1Val;
  T1CC0H=(t1Val>>8);
  // start timer
  START_TIMER1;
}


void uart_init()
{
  // uart 
  P1SEL|=(1<<5);
  P1DIR|=(1<<5);
  PERCFG|=1;
  // 14,400, should be avoided non standard baud rate
  U0CSR|=((1<<7));
  U0GCR=8;
  U0BAUD=216;
}


void uart_send(uint8 sdata)
{
  U0CSR&=~(1<<1);
  U0DBUF=sdata;
  while(!(U0CSR & 0x02));
 
}




void adc_init()
{
  // adc channel 3 and channel 4
  P0SEL|=((1<<6)|(1<<6));
  APCFG=((1<<6)|(1<<5));
  // trigger by ADCCON1.ST bit
  ADCCON1=((3<<4));
  //set external differential reference,12bit ENOB,upto bit 7
  ADCCON2=((3<<6)|(3<<4)|7);
  

}


void adc_conv(uint8 channel)
{
 // select channel 
   ADCCON3=0xb0|channel;
 // start conversion  
   ADCCON1|=(1<<6);
 // wait untill conversion over
  while(!(ADCCON1&0x80));
 
}