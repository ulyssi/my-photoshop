#ifndef _PIXELMOD_HH_
#define _PIXELMOD_HH_

#include <math.h>

#define ALPHA_MSK 0xFF000000
#define RED_MSK 0x00FF0000
#define GREEN_MSK 0x0000FF00
#define BLUE_MSK 0x000000FF



namespace PixelMod{

  enum Type { BINARY, GREY_SCALE, COLOR };

  const int DefaultAlpha = 0;
  const int minValue = 0;
  const int maxValue = 0xFF;
  
  inline  unsigned int combineAlpha(float a1,float a2){
    return ((unsigned int)(floor((a1+a2-(a1*a2))*255.0f+0.5f)))<<24;
  }

  inline unsigned int combineRed(unsigned int p1,unsigned int p2, float a2){
    return ((unsigned int)(floor(float((p1&RED_MSK)>>16)*(1.0f-a2)+float((p2&RED_MSK)>>16)*a2+0.5)))<<16;
  }

  inline unsigned int combineBlue(unsigned int p1,unsigned int p2, float a2){
    return (unsigned int) floor(float(p1&BLUE_MSK)*(1.0f-a2)+float(p2&BLUE_MSK)*a2+0.5f);
  }

  inline unsigned int combineGreen(unsigned int p1,unsigned int p2, float a2) {
    return ((unsigned int)floor(float((p1&GREEN_MSK)>>8)*(1.0f-a2)+float((p2&GREEN_MSK)>>8)*a2+0.5f))<<8;
  }

  inline float getAlpha(unsigned int p, float a){
    return (float((p & ALPHA_MSK)>>24))*a/255.0f;
  }

  inline int getAlpha(unsigned int rgb) { return ((ALPHA_MSK & rgb)>>24); }
  inline int getRed(unsigned int rgb) { return ((RED_MSK & rgb)>>16); }
  inline int getBlue(unsigned int rgb) { return (BLUE_MSK & rgb); }
  inline int getGreen(unsigned int rgb) { return ((GREEN_MSK & rgb)>>8); }
  
  inline unsigned int createRGB(int red, int green, int blue, int alpha = DefaultAlpha) {
    return((alpha << 24) | (red << 16) | (green << 8) | blue);
  }

  inline unsigned int createGrayScale(int grey, int alpha = DefaultAlpha) {
    return createRGB(grey, grey, grey, alpha);
  }

  inline unsigned int createBinary(bool color, int alpha = DefaultAlpha) {
    if (color) return createGrayScale(255, alpha);
    return createGrayScale(0, alpha);
  }

  inline Type getTypeFromRGB(unsigned int rgb) {
    if (getRed(rgb) == getBlue(rgb) && getGreen(rgb) == getBlue(rgb)) {
      if (getBlue(rgb) == 0 || getBlue(rgb) == 255) return BINARY;
      return GREY_SCALE;
    }
    return COLOR;
  }

  inline Type max(Type t1, Type t2) {
    if (t1 == COLOR || t2 == COLOR) return COLOR;
    if (t1 == GREY_SCALE || t2 == GREY_SCALE) return GREY_SCALE;
    return BINARY;
  }

  inline Type min(Type t1, Type t2) {
    if (t1 == BINARY || t2 == BINARY) return BINARY;
    if (t1 == GREY_SCALE || t2 == GREY_SCALE) return GREY_SCALE;
    return COLOR;
  }
};

#endif
