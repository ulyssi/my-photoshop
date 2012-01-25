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
  m_convolutionCoef(1.0),
  m_decalage(0),
  m_pictureData(NULL),
  m_previewData(NULL),
  m_edgeControl(CROP_EDGE),
  m_operator(TIMES_OPERATOR)
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

void ConvolveOperation::setOperator(Operator op) { m_operator = op; }


/** Methodes */
Matrix<unsigned int>* ConvolveOperation::updatePreview() {
  if (m_previewData != NULL) delete m_previewData;
  m_pictureData = m_picture->getData();
  m_previewData = new Matrix<unsigned int>(m_pictureData->getWidth(), m_pictureData->getHeight());

  m_convolutionCoef = 0;
  for (int i = 0; i < m_kernel->getWidth(); i++)
    for (int j = 0; j < m_kernel->getHeight(); j++)
      m_convolutionCoef += m_kernel->getValue(i, j);
  
  m_decalage = 0;
  if (m_convolutionCoef <= 0) {
    m_convolutionCoef = 1;
    if (m_convolutionCoef == 0) m_decalage = 128;
    else m_decalage = 256;
  }

  int startI = 0, endI = m_pictureData->getWidth(), startJ = 0, endJ = m_pictureData->getHeight();
  m_startI2 = -(m_endI2 = (m_kernel->getWidth()-1)/2);
  m_startJ2 = -(m_endJ2 = (m_kernel->getHeight()-1)/2);
  
  if (m_edgeControl == CROP_EDGE) {
    startI += m_endI2;
    endI += m_startI2;
    startJ += m_endJ2;
    endJ += m_startJ2;
  }
  for (int i = 0; i < m_pictureData->getWidth(); i++)
    for (int j = 0; j < m_pictureData->getHeight(); j++) {
      unsigned int color = m_pictureData->getValue(i, j);
      if (startI <= i && i < endI && startJ <= j && j < endJ) {
        if (m_operator == TIMES_OPERATOR) color = timesOperator(i, j);
        else if (m_operator == MEDIAN_OPERATOR) color = medianOperator(i, j);
        else if (m_operator == MIN_OPERATOR) color = minOperator(i, j);
        else if (m_operator == MAX_OPERATOR) color = maxOperator(i, j);
      }
      m_previewData->setValue(i, j, color);
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
unsigned int ConvolveOperation::timesOperator(int i, int j) {
  unsigned int color = m_pictureData->getValue(i, j);
  int red = PixelMod::getRed(color);
  int green = PixelMod::getGreen(color);
  int blue = PixelMod::getBlue(color);
  int alpha =  PixelMod::getAlpha(color);

  if (m_red) red = m_decalage;
  if (m_green) green = m_decalage;
  if (m_blue) blue = m_decalage;
  if (m_alpha) alpha = m_decalage;
  for (int i2 = m_startI2; i2 < m_endI2 + 1; i2++)
    for (int j2 = m_startJ2; j2 < m_endJ2 + 1; j2++) {
      unsigned int color = getPixelColor(i + i2, j + j2);
      if (m_red) red += (double)PixelMod::getRed(color) 
                   * m_kernel->getValue(i2 + m_endI2, j2 + m_endJ2) / m_convolutionCoef;
      if (m_green) green += (double)PixelMod::getGreen(color) 
                     * m_kernel->getValue(i2 + m_endI2, j2 + m_endJ2) / m_convolutionCoef;
      if (m_blue) blue += (double)PixelMod::getBlue(color) 
                    * m_kernel->getValue(i2 + m_endI2, j2 + m_endJ2) / m_convolutionCoef;
      if (m_alpha) alpha += (double)PixelMod::getAlpha(color) 
                     * m_kernel->getValue(i2 + m_endI2, j2 + m_endJ2) / m_convolutionCoef;
    }
  return PixelMod::createRGB(PixelMod::threshold(red),
                             PixelMod::threshold(green),
                             PixelMod::threshold(blue),
                             PixelMod::threshold(alpha));
}

unsigned int ConvolveOperation::medianOperator(int i, int j) {
  return m_pictureData->getValue(i, j);
}

unsigned int ConvolveOperation::maxOperator(int i, int j) {
  unsigned int color = m_pictureData->getValue(i, j);
  unsigned int sum = 0;

  if (m_red) sum += PixelMod::getRed(color);
  if (m_green) sum += PixelMod::getGreen(color);
  if (m_blue) sum += PixelMod::getBlue(color);
  if (m_alpha) sum += PixelMod::getAlpha(color);

  for (int i2 = m_startI2; i2 < m_endI2 + 1; i2++)
    for (int j2 = m_startJ2; j2 < m_endJ2 + 1; j2++) {
      unsigned int colorTmp = getPixelColor(i + i2, j + j2);
      unsigned int sumTmp = 0;
      
      if (m_red) sumTmp += PixelMod::getRed(colorTmp);
      if (m_green) sumTmp += PixelMod::getGreen(colorTmp);
      if (m_blue) sumTmp += PixelMod::getBlue(colorTmp);
      if (m_alpha) sumTmp += PixelMod::getAlpha(colorTmp);
      
      if (sumTmp > sum) {
        sum = sumTmp;
        color = colorTmp;
      }
    }
  return color;
}

unsigned int ConvolveOperation::minOperator(int i, int j) {
  return m_pictureData->getValue(i, j);
}

unsigned int ConvolveOperation::getPixelColor(int i, int j) {
  if (m_edgeControl == EXTEND_EDGE) {
    if (i < 0) i = 0; else if (m_pictureData->getWidth() <= i) i = m_pictureData->getWidth()-1;
    if (j < 0) j = 0; else if (m_pictureData->getHeight() <= j) j = m_pictureData->getHeight()-1;
  }
  else if (m_edgeControl == WRAP_EDGE) {
    if (i < 0) i = m_pictureData->getWidth()-1; else if (m_pictureData->getWidth() <= i) i = 0;
    if (j < 0) j = m_pictureData->getHeight()-1; else if (m_pictureData->getHeight() <= j) j = 0;
  }
  return m_pictureData->getValue(i, j);
}
