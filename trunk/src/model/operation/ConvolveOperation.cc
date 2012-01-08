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
  
  int filterOffsetX = m_kernel->getWidth()/2;
  int filterOffsetY = m_kernel->getHeight()/2;
  
  for (int i = filterOffsetX; i < tracing->getWidth() - filterOffsetX; i++)
    for (int j = filterOffsetY; j < tracing->getHeight() - filterOffsetY; j++) {
      int red = 0, green = 0, blue = 0, alpha = 0;
      for (int i2 = 0; i2 <= m_kernel->getWidth(); i2++)
  	for (int j2 = 0; j2 <= m_kernel->getHeight(); j2++) {
	  red += PixelMod::getRed(pictureData[i+i2-filterOffsetX][j+j2-filterOffsetY]) * filterData[i2][j2];
	  green += PixelMod::getGreen(pictureData[i+i2-filterOffsetX][j+j2-filterOffsetY]) * filterData[i2][j2];
	  blue += PixelMod::getBlue(pictureData[i+i2-filterOffsetX][j+j2-filterOffsetY]) * filterData[i2][j2];
	  alpha += PixelMod::getAlpha(pictureData[i+i2-filterOffsetX][j+j2-filterOffsetY]) * filterData[i2][j2];
	}
      pictureData[i][j] = PixelMod::createRGB(red, green, blue, alpha);
    }
  return tracing;
}

Operation* ConvolveOperation::clone() {return 0;}
