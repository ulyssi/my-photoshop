#ifndef _PIXELMOD_HH_
#define _PIXELMOD_HH_

#include <cmath>

namespace PixelMod {

  /** Constantes */
  const int size = 8;
  const int minValue = 0x0;
  const int maxValue = (0x1 << size) - 1;
  
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
  
  enum YUV { LUMA, CHROMINANCE_U, CHROMINANCE_V };

  enum Type { BINARY = 0, GREY_SCALE = 1, COLOR = 2 };

  /** Accesseurs */
  inline int getAlpha(unsigned int rgb) { return ((ALPHA_MSK & rgb) >> ALPHA_OFFSET); }
  inline int getRed(unsigned int rgb) { return ((RED_MSK & rgb) >> RED_OFFSET); }
  inline int getGreen(unsigned int rgb) { return ((GREEN_MSK & rgb) >> GREEN_OFFSET); }
  inline int getBlue(unsigned int rgb) { return (BLUE_MSK & rgb) >> BLUE_OFFSET; }
  
  inline int getLuma(unsigned int rgb) { return 0.299 * getRed(rgb) + 0.587 * getGreen(rgb) + 0.114 * getBlue(rgb); }
  inline int getChrominanceU(unsigned int rgb) { return -0.14713 * getRed(rgb) - 0.28886 * getGreen(rgb) + 0.436 * getBlue(rgb); }
  inline int getChrominanceV(unsigned int rgb) { return 0.615 * getRed(rgb) - 0.51499 * getGreen(rgb) - 0.10001 * getBlue(rgb); }
  
  inline int threshold(int composante) {
    if (composante < minValue) return minValue;
    if (composante > maxValue) return maxValue;
    return composante;
  }

  /** Methodes */
  inline unsigned int createRGB(int red, int green, int blue, int alpha = OPAQUE) {
    return (alpha << ALPHA_OFFSET) | (red << RED_OFFSET) | (green << GREEN_OFFSET) | (blue << BLUE_OFFSET);
  }

  inline unsigned int createYUV(int luma, int chrominanceU, int chrominanceV, int alpha = OPAQUE) {
    return createRGB(luma + 1.13983 * chrominanceV,
		     luma - 0.39465 * chrominanceU - 0.58060 * chrominanceV,
		     luma + 2.03211 * chrominanceU,
		     alpha);
  }
  
  inline unsigned int createGrayScale(int grey, int alpha = OPAQUE) {
    return createRGB(grey, grey, grey, alpha);
  }
  
  inline unsigned int createBinary(bool color, int alpha = OPAQUE) {
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
