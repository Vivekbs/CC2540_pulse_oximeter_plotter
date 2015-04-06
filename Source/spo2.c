#include "spo2.h"
#include "peak_detect.h"
#include "peak_detect.c"

uint8 spo2(uint16 red_dc,uint16 ir_dc)
{
  
  uint16 red_ac,ir_ac;
  uint8 i,spo2;
  
  for(i=0;i<COUNT;i++)
  {
    red_ac=red_track.max_value[i] - red_track.min_value[i];
    ir_ac=ir_track.max_value[i] - ir_track.min_value[i];
    
  }
   
   red_ac=red_ac/COUNT;
   ir_ac=ir_ac/COUNT;
   
   
 /// 107.4 – 12.57(Pred / Pir)   
   
   spo2= (((107*ir_ac)/ir_dc - (12 *red_ac)/red_dc)*(ir_dc))/ir_ac;
   
    red_track.found=false;
    ir_track.found=false;
   
   return spo2;
}