#include "peak_detect.h"



struct peak_track red_track,ir_track;
bool struct_init=false;

void peak_track_init()
{  
  red_track.maxi=0;
  red_track.mini=0;
  
  red_track.max_value[red_track.maxi]=0;
  red_track.min_value[red_track.mini]=0x0fff;

  
  red_track.found=false;
  red_track.track=true;
  
  ir_track.maxi=0;
  ir_track.mini=0;
  
  ir_track.max_value[ir_track.maxi]=0;
  ir_track.min_value[ir_track.mini]=0x0fff;
  
  ir_track.found=false;
  ir_track.track=true;
  
  struct_init=true;
}



void red_peak_track(uint16 sample)
{
  if(!struct_init)
    peak_track_init();
  
  if(sample > red_track.max_value[red_track.maxi])
  {
    red_track.max_value[red_track.maxi]=sample;  
  }
  
  if(sample <red_track.min_value[red_track.mini])
  {
    red_track.min_value[red_track.mini]=sample;
  }
  
  if(red_track.track)
  {
    if(sample < (red_track.max_value[red_track.maxi] - DELTA ))
    {
      red_track.min_value[red_track.mini]= red_track.max_value[red_track.maxi];
      red_track.maxi= (red_track.maxi+1) % COUNT;
      red_track.track=false;
    }
  }
  else
  {
    if(sample > (red_track.min_value[red_track.mini] + DELTA ))
    {
      red_track.max_value[red_track.maxi]= red_track.min_value[red_track.mini];
      red_track.mini= (red_track.mini+1) % COUNT;
      red_track.track=true;
    }
    
    if(red_track.maxi==0 & red_track.mini==0)
      red_track.found=true;
  }
  
}
  
  
  
uint8 ir_peak_track(uint16 sample,uint16 red_dc,uint16 ir_dc )
{
  if(!struct_init)
    peak_track_init();
  
  if(sample > ir_track.max_value[ir_track.maxi])
  {
    ir_track.max_value[ir_track.maxi]=sample;  
  }
  
  if(sample <ir_track.min_value[ir_track.mini])
  {
    ir_track.min_value[ir_track.mini]=sample;
  }
  
  if(ir_track.track)
  {
    if(sample < (ir_track.max_value[ir_track.maxi] - DELTA ))
    {
      ir_track.min_value[ir_track.mini]= ir_track.max_value[ir_track.maxi];
      ir_track.maxi= (ir_track.maxi+1) % COUNT;
      ir_track.track=false;
    }
  }
  else
  {
    if(sample > (ir_track.min_value[ir_track.mini] + DELTA ))
    {
      ir_track.max_value[ir_track.maxi]= ir_track.min_value[ir_track.mini];
      ir_track.mini= (ir_track.mini+1) % COUNT;
      ir_track.track=true;
    }
    
    if(ir_track.maxi==0 & ir_track.mini==0)
      ir_track.found=true;
  }
  
  if(red_track.found && ir_track.found)
  {
    return(spo2(red_dc,ir_dc));
    
  }
  
  else 
    return 0;
  
}



uint16 spo2(uint16 red_dc,uint16 ir_dc)
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
   
   spo2=(ir_ac*100/red_ac);
   
    red_track.found=false;
    ir_track.found=false;
   
   return spo2;
}