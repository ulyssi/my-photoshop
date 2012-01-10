#ifndef _PIXELMOD_HH_
#define _PIXELMOD_HH_

#include <cmath>

#define ALPHA_MSK 0xFF000000
#define RED_MSK 0x00FF0000
#define GREEN_MSK 0x0000FF00
#define BLUE_MSK 0x000000FF

namespace PixelMod {

  enum Type { BINARY, GREY_SCALE, COLOR };

  const int DefaultAlpha = 0;
  const int minValue = 0;
  const int maxValue = 0xFF;
  
  inline int getAlpha(unsigned int rgb) { return ((ALPHA_MSK & rgb)>>24); }
  inline int getRed(unsigned int rgb) { return ((RED_MSK & rgb)>>16); }
  inline int getBlue(unsigned int rgb) { return (BLUE_MSK & rgb); }
  inline int getGreen(unsigned int rgb) { return ((GREEN_MSK & rgb)>>8); }
  
  inline int threshold(int composante) {
    if (composante < 0) return 0;
    if (composante > 255) return 255;
    return composante;
  }

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
