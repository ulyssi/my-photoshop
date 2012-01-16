#include "ConvolveOperation.hh"

#include "Picture.hh"
#include "Tracing.hh"


/** Constructeurs et destructeur */
ConvolveOperation::ConvolveOperation(Picture* picture, Operation* operation) :
  m_operation(operation),
  m_picture(picture),
  m_kernel(NULL),
  m_red(true),
  m_green(true),
  m_blue(true),
  m_alpha(false),
  m_pictureData(NULL),
  m_previewData(NULL)
{}

ConvolveOperation::~ConvolveOperation() {}


/** Accesseurs */
Picture* ConvolveOperation::getPicture() { return m_picture; }

PixelMod::Type ConvolveOperation::getInputType() { return PixelMod::COLOR; }

PixelMod::Type ConvolveOperation::getOutputType() { 
  // if (m_operation != NULL) return m_operation->getOutType();
  return PixelMod::COLOR; 
}


/** Mutateurs */
void ConvolveOperation::setKernel(Matrix<double>* kernel) { m_kernel = kernel; }

void ConvolveOperation::setRGBA(bool red, bool green, bool blue, bool alpha) {
  setRed(red);
  setGreen(green);
  setBlue(blue);
  setAlpha(alpha);
}

void ConvolveOperation::setRed(bool red) { m_red = red; }

void ConvolveOperation::setGreen(bool green) { m_green = green; }

void ConvolveOperation::setBlue(bool blue) { m_blue = blue; }

void ConvolveOperation::setAlpha(bool alpha) { m_alpha = alpha; }


/** Methodes */
Matrix<unsigned int>* ConvolveOperation::updatePreview() {
  if (m_previewData != NULL) delete m_previewData;
  m_pictureData = m_picture->getData();
  m_previewData = new Matrix<unsigned int>(m_pictureData->getWidth(), m_pictureData->getHeight());
  
  double** filterData = m_kernel->getData();
  int filterOffsetX = (m_kernel->getWidth()-1)/2;
  int filterOffsetY = (m_kernel->getHeight()-1)/2;
  
  double convolutionCoef = 0;
  for (int i = 0; i < m_kernel->getWidth(); i++)
    for (int j = 0; j < m_kernel->getHeight(); j++)
      convolutionCoef += filterData[i][j];
  
  int decalage = 0;
  if (convolutionCoef <= 0) {
    convolutionCoef = 1;
    if (convolutionCoef == 0) decalage = 128;
    else decalage = 256;
  }

  for (int i = filterOffsetX; i < m_pictureData->getWidth() - filterOffsetX; i++)
    for (int j = filterOffsetY; j < m_pictureData->getHeight() - filterOffsetY; j++) {
      int red = decalage, green = decalage, blue = decalage, alpha = decalage;
      if (!m_red) red = PixelMod::getRed(m_pictureData->getValue(i, j));
      if (!m_green) green = PixelMod::getGreen(m_pictureData->getValue(i, j));
      if (!m_blue) blue = PixelMod::getBlue(m_pictureData->getValue(i, j));
      if (!m_alpha) alpha = PixelMod::getAlpha(m_pictureData->getValue(i, j));
      for (int i2 = 0; i2 < m_kernel->getWidth(); i2++)
      	for (int j2 = 0; j2 < m_kernel->getHeight(); j2++) {
          unsigned int color = m_pictureData->getValue(i + i2 - filterOffsetX, j + j2 - filterOffsetY);
          if (m_red) red += PixelMod::getRed(color) * filterData[i2][j2] / convolutionCoef;
      	  if (m_green) green += PixelMod::getGreen(color) * filterData[i2][j2] / convolutionCoef;
      	  if (m_blue) blue += PixelMod::getBlue(color) * filterData[i2][j2] / convolutionCoef;
      	  if (m_alpha) alpha += PixelMod::getAlpha(color) * filterData[i2][j2] / convolutionCoef;
      	}
      m_previewData->setValue(i, j, PixelMod::createRGB(PixelMod::threshold(red), PixelMod::threshold(green), PixelMod::threshold(blue), PixelMod::threshold(alpha)));
    }
  return m_previewData;
}

Picture* ConvolveOperation::applyOperation() {
  m_pictureData = m_picture->getData();
  m_picture->getBackground()->setData(updatePreview());
  m_picture->refresh();
  return m_picture;
}

// Tracing* ConvolveOperation::doOperation(Tracing* tracing) {
//   double** filterData = m_kernel->getData();
//   unsigned int** pictureData = tracing->getData();
//   Matrix<unsigned int> source(tracing->getWidth(), tracing->getHeight(), pictureData);
  
//   int filterOffsetX = (m_kernel->getWidth()-1)/2;
//   int filterOffsetY = (m_kernel->getHeight()-1)/2;
 
//   double convolutionCoef = 0;
//   for (int i = 0; i < m_kernel->getWidth(); i++)
//     for (int j = 0; j < m_kernel->getHeight(); j++)
//       convolutionCoef += filterData[i][j];
  
//   int decalage = 0;
//   if (convolutionCoef < 0) { 
//     decalage = 256;
//     convolutionCoef = 1;
//   }
//   else if (convolutionCoef == 0) { 
//     decalage = 128;
//     convolutionCoef = 1;
//   }
//   std::cout << "convolutionCoef = " << convolutionCoef << " decalage = " << decalage<< std::endl;
//   for (int i = filterOffsetX; i < tracing->getWidth() - filterOffsetX; i++)
//     for (int j = filterOffsetY; j < tracing->getHeight() - filterOffsetY; j++) {
//       int red = 0, green = 0, blue = 0, alpha = 0;
//       for (int i2 = 0; i2 < m_kernel->getWidth(); i2++)
//       	for (int j2 = 0; j2 < m_kernel->getHeight(); j2++) {
// 	  unsigned int color = source.getValue(i + i2 - filterOffsetX, j + j2 - filterOffsetY);
// 	  red += PixelMod::getRed(color) * filterData[i2][j2] / convolutionCoef;
//       	  green += PixelMod::getGreen(color) * filterData[i2][j2] / convolutionCoef;
//       	  blue += PixelMod::getBlue(color) * filterData[i2][j2] / convolutionCoef;
//       	  alpha += PixelMod::getAlpha(color) * filterData[i2][j2] / convolutionCoef;
//       	}
//       pictureData[i][j] = PixelMod::createRGB(PixelMod::threshold(red + decalage),
// 					      PixelMod::threshold(green + decalage),
// 					      PixelMod::threshold(blue + decalage),
// 					      PixelMod::getAlpha(pictureData[i][j]));
//     }
//   return tracing;
// }

// Operation* ConvolveOperation::clone() { return NULL; }
