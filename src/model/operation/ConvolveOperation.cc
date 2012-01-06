#include "ConvolveOperation.hh"

#include "Tracing.hh"
#include "Kernel.hh"
#include "PixelMod.hh"

/** Constructeurs et destructeur */
ConvolveOperation::ConvolveOperation(Kernel *kernel) :
  m_kernel(kernel)
{}

ConvolveOperation::~ConvolveOperation() {}


/** Methodes */
Tracing* ConvolveOperation::doOperation(Tracing* tracing) {
  double** filterData = m_kernel->getData();
  unsigned int** pictureData = tracing->getData();
  Matrix<unsigned int> source(tracing->getWidth(), tracing->getHeight(), pictureData);
  
  int filterOffset = m_kernel->getSize()/2;
  
  for (int i = filterOffset; i < tracing->getWidth() - filterOffset; i++)
    for (int j = filterOffset; j < tracing->getHeight() - filterOffset; j++) {
      int red = 0, green = 0, blue = 0, alpha = 0;
      for (int i2 = 0; i2 <= m_kernel->getWidth(); i2++)
  	for (int j2 = 0; j2 <= m_kernel->getHeight(); j2++) {
	  red += PixelMod::getRed(pictureData[i+i2-filterOffset][j+j2-filterOffset]) * filterData[i2][j2];
	  green += PixelMod::getGreen(pictureData[i+i2-filterOffset][j+j2-filterOffset]) * filterData[i2][j2];
	  blue += PixelMod::getBlue(pictureData[i+i2-filterOffset][j+j2-filterOffset]) * filterData[i2][j2];
	  alpha += PixelMod::getAlpha(pictureData[i+i2-filterOffset][j+j2-filterOffset]) * filterData[i2][j2];
	}
      pictureData[i][j] = PixelMod::createRGB(red, green, blue, alpha);
    }
  return tracing;
}

Operation* ConvolveOperation::clone() {return 0;}
