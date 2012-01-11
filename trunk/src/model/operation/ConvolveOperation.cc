#include "ConvolveOperation.hh"

#include "Tracing.hh"
#include "PixelMod.hh"

/** Constructeurs et destructeur */
ConvolveOperation::ConvolveOperation(Matrix<double>* kernel) :
  m_kernel(kernel)
{}

ConvolveOperation::~ConvolveOperation() {}


/** Methodes */
Tracing* ConvolveOperation::doOperation(Tracing* tracing) {
  double** filterData = m_kernel->getData();
  unsigned int** pictureData = tracing->getData();
  Matrix<unsigned int> source(tracing->getWidth(), tracing->getHeight(), pictureData);
  
  int filterOffsetX = (m_kernel->getWidth()-1)/2;
  int filterOffsetY = (m_kernel->getHeight()-1)/2;
 
  double convolutionCoef = 0;
  for (int i = 0; i < m_kernel->getWidth(); i++)
    for (int j = 0; j < m_kernel->getHeight(); j++)
      convolutionCoef += filterData[i][j];
  
  int decalage = 0;
  if (convolutionCoef < 0) decalage = 256;
  else if (convolutionCoef == 0) decalage = 128;
  
  for (int i = filterOffsetX; i < tracing->getWidth() - filterOffsetX; i++)
    for (int j = filterOffsetY; j < tracing->getHeight() - filterOffsetY; j++) {
      int red = 0, green = 0, blue = 0, alpha = 0;
      for (int i2 = 0; i2 < m_kernel->getWidth(); i2++)
      	for (int j2 = 0; j2 < m_kernel->getHeight(); j2++) {
	  unsigned int color = source.getValue(i + i2 - filterOffsetX, j + j2 - filterOffsetY);
	  red += PixelMod::getRed(color) * filterData[i2][j2];
      	  green += PixelMod::getGreen(color) * filterData[i2][j2];
      	  blue += PixelMod::getBlue(color) * filterData[i2][j2];
      	  alpha += PixelMod::getAlpha(color) * filterData[i2][j2];
      	}
      pictureData[i][j] = PixelMod::createRGB(PixelMod::threshold(red + decalage),
					      PixelMod::threshold(green + decalage),
					      PixelMod::threshold(blue + decalage),
					      PixelMod::getAlpha(pictureData[i][j]));
    }
  return tracing;
}

Operation* ConvolveOperation::clone() { return NULL; }
