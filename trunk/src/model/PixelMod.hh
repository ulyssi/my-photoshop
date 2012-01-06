#ifndef _PIXELMOD_HH_
#define _PIXELMOD_HH_

#define ALPHA_MSK 0xFF000000
#define RED_MSK 0x00FF0000
#define GREEN_MSK 0x0000FF00
#define BLUE_MSK 0x000000FF


namespace PixelMod{

  unsigned int combineAlpha(float,float);
  unsigned int combineRed(unsigned int,unsigned int,float);
  unsigned int combineBlue(unsigned int,unsigned int,float);
  unsigned int combineGreen(unsigned int,unsigned int,float);
  float getAlpha(unsigned int, float);
  int getGreen(unsigned int);
  int getBlue(unsigned int);
  int getRed(unsigned int);
  int getAlpha(unsigned int);
  unsigned int createARGB(int, int, int, int);
};
#endif
