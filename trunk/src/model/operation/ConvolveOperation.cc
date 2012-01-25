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
  m_previewData(NULL),
  m_edgeControl(CROP_EDGE)
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

void ConvolveOperation::setEdgeControl(EdgeControl edgeControl) { m_edgeControl = edgeControl; }


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

  int startI = 0, endI = m_pictureData->getWidth(), startJ = 0, endJ = m_pictureData->getWidth();
  int startI2 = -(m_kernel->getWidth()-1)/2, endI2 = (m_kernel->getWidth()-1)/2;
  int startJ2 = -(m_kernel->getHeight()-1)/2, endJ2 = (m_kernel->getHeight()-1)/2;

  if (m_edgeControl == CROP_EDGE) {
    startI += endI2;
    endI += startI2;
    startJ += endJ2;
    endJ += startJ2;
  }
  for (int i = startI; i < endI; i++)
    for (int j = startJ; j < endJ; j++) {
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
      m_previewData->setValue(i, j, PixelMod::createRGB(PixelMod::threshold(red),
                                                        PixelMod::threshold(green),
                                                        PixelMod::threshold(blue),
                                                        PixelMod::threshold(alpha)));
    }
  return m_previewData;
}

Picture* ConvolveOperation::applyOperation() {
  m_pictureData = m_picture->getData();
  m_picture->getBackground()->setData(updatePreview());
  m_picture->refresh();
  return m_picture;
}


/** Methodes internes */
unsigned int ConvolveOperation::getPixelColor(int i, int j) {
  int x = m_pictureData->getWidth(), y = m_pictureData->getHeight();
  switch (m_edgeControl) {
  case EXTEND_EDGE:
    if (i < 0) x = i; else if (i < x) x = i;
    if (j < 0) y = j; else if (j < y) y = j;
    return m_pictureData->getValue(x, y);
  case WRAP_EDGE:
    if (i < 0) x = i; else if (i < x) x = i;
    if (j < 0) y = j; else if (j < y) y = j;
    return m_pictureData->getValue(x, y);
  case CROP_EDGE: 
  default: return m_pictureData->getValue(i, j);
  }
}
