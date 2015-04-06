#include "pulse_oxi.h"
#include "pulse_process.h"
#include "user_board.h"
#include "circularBuffer.h"





//debug 
static uint8 k=0;
static uint8 ms[4]={1,1,1,1};
bool msg=true;

void init_process_queue(void)
{
  k=0;
  timer1_delay(ms[0]);

}

bool process_queue()
{
  

  // sudo implementation of queue processing
 // PHY_Command(PHY_CMD_BLE_RX_RAW);
 
   switch(k)
    {
        case 0: msg=redon();
                break;
        case 1: red_adc_read();
                break;
        case 2:while((RFSTAT & 0x03)!=0x00);
                iron();
                break;
        case 3:ir_adc_read();
                break;
         
      default:
              break;
    }

  
 
 //   queue.process_pointer=(queue.process_pointer+1)%no_process;
   k=(k+1)%2;
   timer1_delay(ms[k]);//queue.time[1]);
  
    
}