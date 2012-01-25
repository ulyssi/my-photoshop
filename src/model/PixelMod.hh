#ifndef _PIXELMOD_HH_
#define _PIXELMOD_HH_

#include <cmath>

namespace PixelMod {

  /** Constantes */
  const int nbLayers = 4;
  const int size = 32 / nbLayers;
  const int nbValue = 0x1 << size;
  const int minValue = 0x0;
  const int maxValue = nbValue - 1;
  
  /** Types internes */
  enum RGB { ALPHA = 3, RED = 2, GREEN = 1, BLUE = 0 };
  
  enum Offset {
    ALPHA_OFFSET = size * ALPHA,
    RED_OFFSET = size * RED,
    GREEN_OFFSET = size * GREEN,
    BLUE_OFFSET = size * BLUE 
  };

  enum Mask {
    ALPHA_MSK = maxValue << ALPHA_OFFSET, 
    RED_MSK = maxValue << RED_OFFSET, 
    GREEN_MSK = maxValue << GREEN_OFFSET,
    BLUE_MSK = maxValue << BLUE_OFFSET 
  };

  enum Alpha { TRANSLUCID = minValue, OPAQUE = maxValue };
  
  enum YUV { LUMA = 2, CHROMINANCE_U = 1, CHROMINANCE_V = 0 };

  enum Type { BINARY = 0, GREY_SCALE = 1, COLOR = 2 };

  /** Accesseurs */
  inline int getAlpha(unsigned int rgb) { return ((ALPHA_MSK & rgb) >> ALPHA_OFFSET); }
  inline int getRed(unsigned int rgb) { return ((RED_MSK & rgb) >> RED_OFFSET); }
  inline int getGreen(unsigned int rgb) { return ((GREEN_MSK & rgb) >> GREEN_OFFSET); }
  inline int getBlue(unsigned int rgb) { return (BLUE_MSK & rgb) >> BLUE_OFFSET; }
  
  inline double getLuma(unsigned int rgb) { return 0.299 * (double)getRed(rgb) + 0.587 * (double)getGreen(rgb) + 0.114 * (double)getBlue(rgb); }
  inline double getChrominanceU(unsigned int rgb) { return -0.14713 * (double)getRed(rgb) - 0.28886 * (double)getGreen(rgb) + 0.436 * (double)getBlue(rgb); }
  inline double getChrominanceV(unsigned int rgb) { return 0.615 * (double)getRed(rgb) - 0.51499 * (double)getGreen(rgb) - 0.10001 * (double)getBlue(rgb); }
  
  inline int threshold(int composante) {
    if (composante < minValue) return minValue;
    if (composante > maxValue) return maxValue;
    return composante;
  }

  /** Methodes */
  inline unsigned int createRGB(int red, int green, int blue, int alpha = OPAQUE) {
    return (alpha << ALPHA_OFFSET) | (red << RED_OFFSET) | (green << GREEN_OFFSET) | (blue << BLUE_OFFSET);
  }
  
  inline int getIntFromDouble(double x){
    if(fmod(x*1000.0,1000.0) > 500.0) return ceil(x);
    else return floor(x);
  }

  inline unsigned int createYUV(double luma, double chrominanceU, double chrominanceV, int alpha = OPAQUE) {
    return createRGB(getIntFromDouble(luma + 1.13983 * chrominanceV),
		     getIntFromDouble(luma - 0.39465 * chrominanceU - 0.58060 * chrominanceV),
		     getIntFromDouble(luma + 2.03211 * chrominanceU),
		     alpha);
  }

  inline unsigned int createGrayScale(int grey, int alpha = OPAQUE) {
    return createRGB(grey, grey, grey, alpha);
  }
  
  inline unsigned int createBinary(bool color, int alpha = OPAQUE) {
    if (color) return createGrayScale(maxValue, alpha);
    return createGrayScale(minValue, alpha);
  }


  inline Type getTypeFromRGB(unsigned int rgb) {
    if (getRed(rgb) == getBlue(rgb) && getGreen(rgb) == getBlue(rgb)) {
      if (getBlue(rgb) == minValue || getBlue(rgb) == maxValue) return BINARY;
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
