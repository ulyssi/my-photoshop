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

int PixelMod::getAlpha(unsigned int rgb){
  return ((ALPHA_MSK & rgb)>>24);  
}

int PixelMod::getRed(unsigned int rgb){
  return ((RED_MSK & rgb)>>16);  
}

int PixelMod::getBlue(unsigned int rgb){
  return (BLUE_MSK & rgb);  
}

int PixelMod::getGreen(unsigned int rgb){
  return ((GREEN_MSK & rgb)>>8);  
}

unsigned int PixelMod::createARGB(int red, int green, int blue, int alpha = 255){
    return((alpha << 24) | (red << 16) | (green << 8) | blue);
}

PixelMod::Type PixelMod::getTypeFromRGB(unsigned int rgb) {
  if (getRed(rgb) == getBlue(rgb) && getGreen(rgb) == getBlue(rgb)) {
    if (getBlue(rgb) == 0 || getBlue(rgb) == 255) return BINARY;
    return GREY_SCALE;
  }
  return COLOR;
}

PixelMod::Type PixelMod::max(Type t1, Type t2) {
  if (t1 == COLOR || t2 == COLOR) return COLOR;
  if (t1 == GREY_SCALE || t2 == GREY_SCALE) return GREY_SCALE;
  return BINARY;
}

PixelMod::Type PixelMod::min(Type t1, Type t2) {
  if (t1 == BINARY || t2 == BINARY) return BINARY;
  if (t1 == GREY_SCALE || t2 == GREY_SCALE) return GREY_SCALE;
  return COLOR;
}
