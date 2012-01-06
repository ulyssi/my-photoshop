#include "PixelMod.hh"



unsigned int PixelMod::combineAlpha(float a1,float a2)
{
  return ((unsigned int)((a1+a2-(a1*a2))*255))<<24;
}

unsigned int PixelMod::combineRed(unsigned int p1,unsigned int p2, float a2){
  return ((unsigned int)((p1&RED_MSK>>16)*(1-a2)+(p2&RED_MSK>>16)*a2))<<16;
}

unsigned int PixelMod::combineBlue(unsigned int p1,unsigned int p2, float a2){
  return(unsigned int) ((p1&BLUE_MSK)*(1-a2)+(p2&BLUE_MSK)*a2);
}

unsigned int PixelMod::combineGreen(unsigned int p1,unsigned int p2, float a2) {
  return ((unsigned int)((p1&GREEN_MSK>>8)*(1-a2)+(p2&GREEN_MSK>>8)*a2)) <<8;
}

float PixelMod::getAlpha(unsigned int p, float a){
  return ((float)((p & ALPHA_MSK)>>24))*a;
}
