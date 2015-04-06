#include "pulse_process.h"
#include "osal.h"
#include "digi_pot.h"
#include "user_board.h"
#include "circularBuffer.h"
#include "packet.h"

//  buffer
#define BUFF_LEN 100
uint8  red_bufferch0[BUFF_LEN];
uint8  red_pointer_ch0=0;
bool red_bufferch0_full=false;
uint8 red_reference,reddc;
uint16 red_dc,present_red=127;

uint8 ir_bufferch0[BUFF_LEN];
uint8  ir_pointer_ch0=0;
bool ir_bufferch0_full=false;
uint8 ir_reference,irdc;
uint16 ir_dc,present_ir=127;
// user process

CircularBuffer *cbuf;
uint8 *pbuff;

bool redon(void)
{
  RED_LED=1;//making change
 
  if(red_bufferch0_full)
  {
    red_bufferch0_full=false;
    
  }
  set_pot(red_reference);

  return true;
}

void red_adc_read(void)
{
  set_pot(red_reference+1);
  red_buffer_ch_0( );
   set_pot(red_reference-1);
  red_buffer_ch_1( );
  
  RED_LED=0;

}

void iron(void)
{
    
   IR_LED=1;// making 
   
  if(ir_bufferch0_full)
  {
    ir_bufferch0_full=false;
      
  }
   
}

void ir_adc_read(void)
{

   set_pot(ir_reference); 
   ir_buffer_ch_0( );
   ir_buffer_ch_1( );
  
  IR_LED=0;// changed
}




// buffer part
void red_buffer_ch_0(void)
{
  
  adc_conv(6);
  uint16 adcVal=ADCL;
  adcVal|=(ADCH<<8);
  adcVal=adcVal>>2;
  
  

  
  
  red_dc=adcVal;
  adcVal=adcVal>>5;
 
  
  
  
         
  red_bufferch0[red_pointer_ch0]=adcVal;
  red_pointer_ch0=(red_pointer_ch0+1)%BUFF_LEN;
  
   if(red_pointer_ch0==0){
    red_bufferch0_full=true;
    red_reference_voltage();
  }
 
 
  
  
}

void red_buffer_ch_1()
{
  
  
  adc_conv(5);
  uint16 adcVal;
  adcVal|=(ADCH<<8);
  adcVal=adcVal>>2;

   circBufferAdd(cbuf,adcVal);
   ////////////////debug//////////////////
   /* *(pbuff+0)=0xaa;
    *(pbuff+1)=red_dc>>8;
    *(pbuff+2)=red_dc;
    *(pbuff+3)=adcVal>>8;
    *(pbuff+4)=adcVal;
  */
}

void ir_buffer_ch_0()
{
 
  adc_conv(6);
  uint16 adcVal=ADCL;
  adcVal|=(ADCH<<8);
  adcVal=adcVal>>2;// change this
  
  ir_dc=adcVal;
  

 
  
  adcVal=adcVal>>5;
 
  
  
  ir_bufferch0[ir_pointer_ch0]=adcVal;
  ir_pointer_ch0=(ir_pointer_ch0+1)%BUFF_LEN;
  
  if(ir_pointer_ch0==0){
    ir_bufferch0_full=true;
    ir_reference_voltage();
  }
  
  
   
 
}



void ir_buffer_ch_1()
{


  
  uint16 temp;
  adc_conv(5);
  uint16 adcVal=ADCL;
  adcVal|=(ADCH<<8);
  adcVal=adcVal>>2;
  temp=adcVal;
  

  adc_conv(2);
  adcVal=ADCL;
  adcVal|=(ADCH<<8);
  adcVal=adcVal>>2;
  temp=(temp+adcVal)/2;
  
   adc_conv(2);
   adcVal=ADCL;
   adcVal|=(ADCH<<8);
   adcVal=adcVal>>2;
   temp=(temp+adcVal)/2;
  
  
  
   ////////////////debug//////////////////
  /*
    *(pbuff+5)=ir_dc>>8;
    *(pbuff+6)=ir_dc;
    *(pbuff+7)=adcVal>>8;
    *(pbuff+8)=adcVal;
    *(pbuff+9)=0xbb;
  */
}


void red_reference_voltage()
{
  uint16 temp=0;
  uint8 i,delta;
  
    for(i=0;i<BUFF_LEN;i++)
    {
      temp=temp+red_bufferch0[i];
    }
      temp=(temp)/(BUFF_LEN);
       
    /*
    // find the change
    if(reddc>temp)
      delta=reddc-temp;
    else
      delta=temp-reddc;
    
    
   
        reddc=temp;
       present=(uint16) (128+G*temp)/(1+G);
          if(!(present-1==red_reference || present+1== red_reference))
              red_reference=present;
  */ // changed here
    if(temp>=present_red)
      delta=temp-present_red;
    else
      delta=present_red-temp;
   
  if(delta>2)//>2
    present_red=temp;
  
    
  red_reference=(uint16) (180+G*present_red)/(1+G);//110
}

void ir_reference_voltage(void)
{
  uint16 temp=0;
  uint8  i,delta;
  
    for(i=0;i<BUFF_LEN;i++)
    {
      temp=temp+ir_bufferch0[i];
    }
      temp=(temp)/(BUFF_LEN);
       
    
    if(temp>=present_ir)
      delta=temp-present_ir;
    else
      delta=present_ir-temp;
   
  if(delta>1)//>2
    present_ir=temp;
  
    
  ir_reference=(uint16) (180+G*present_ir)/(1+G);//128
       
 
}


void pointer2buffer(CircularBuffer *p)
{
  cbuf=p;
}
                
                
 ///// create packet////////
 
 void pointer2packet(uint8 *pointer)
 {
   pbuff=pointer;
 
 }

