#ifndef PEAK_DETECT_H
#define PEAK_DETECT_H

#include<osal.h>


#define DELTA 150
#define COUNT 5
struct peak_track
{
  uint16 max_value[COUNT];
  uint16 min_value[COUNT];
  uint8 maxi;
  uint8 mini;
  bool found;
  bool track;// o for minima ,1 for maxima
};

void peak_track_init(void);
void red_peak_track(uint16);
bool ir_peak_track(uint16);
uint16 spo2(uint16,uint16);
bool red_found();
uint8 red_bpm();

#endif
