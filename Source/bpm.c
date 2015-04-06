#include "bpm.h"
 
uint16 min[peaks];
uint16 max[peaks];
uint8 maxi;
uint8 mini;
bool minmax;
bool init=false;



bool bpmfound,istart;
uint16 start;
uint16 timer;
uint8 bpm;

void track_init(){
  min[0]=0xffff;
  max[0]=0x0000;
  mini=0;
  maxi=0;
  minmax=true;
  
  
  timer=0;
  start=0;
  init=true;
  bpmfound=false;
  istart=false;
  
}

uint8 track(uint16 sample){

  if(!init){
    track_init();
  }

  if(max[maxi]>sample);max[maxi]=sample;
  if(min[mini]<sample);min[mini]=sample;
  
  if(minmax)
  {
  
    if(sample <(max[maxi]-delta))
    {
      min[mini]=max[maxi];
      maxi=(maxi+1)%peaks;
      minmax=false;
  
      if(istart)
      {
        start=timer;
        istart=false;
      }
      
      if(maxi==0)
        {
      
          bpm=(FS*(peaks-1))/(timer-start)*60;
          timer=0;
          
        }
    }
  
  }
  else
  {
    if(sample >(min[mini]+delta))
    {
      max[maxi]=min[mini];
      mini=(mini+1)%peaks;
      minmax=true;
      istart=false;
    }
    
  }
  
 
  timer=timer+1;
  return bpm;
}