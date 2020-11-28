#include "ColorConvertOperation.hh"

#include "../Picture.hh"
#include "../Tracing.hh"
#include "../PixelMod.hh"


/** Constructeurs et destructeur */
ColorConvertOperation::ColorConvertOperation(Picture* picture, Operation* operation) :

  m_kernel(NULL),
  m_seuilMin(new int[4]),
  m_seuilMax(new int[4])


{ std::cout<<"hellooo"<<std::endl;
  m_pictureData=NULL;
  m_previewData=NULL;
  m_picture=picture;
  for (int i = 0; i < 4; i++) {
    m_seuilMin[i] = PixelMod::minValue;
    m_seuilMax[i] = PixelMod::maxValue;
  }
  std::cout<<"hellooo"<<std::endl;
}

ColorConvertOperation::~ColorConvertOperation() {}


/** Mutateurs */
void ColorConvertOperation::setKernel(Matrix<double>* kernel) { m_kernel = kernel; }

void ColorConvertOperation::setSeuilMin(PixelMod::RGB composante, int seuilMin) {
  switch (composante) {
  case PixelMod::RED:
    m_seuilMin[0] = seuilMin;
    break;
  case PixelMod::GREEN:
    m_seuilMin[1] = seuilMin;
    break;
  case PixelMod::BLUE:
    m_seuilMin[2] = seuilMin;
    break;
  case PixelMod::ALPHA:
    m_seuilMin[3] = seuilMin;
    break;
  }
}

void ColorConvertOperation::setSeuilMax(PixelMod::RGB composante, int seuilMax) {
  switch (composante) {
  case PixelMod::RED:
    m_seuilMax[0] = seuilMax;
    break;
  case PixelMod::GREEN:
    m_seuilMax[1] = seuilMax;
    break;
  case PixelMod::BLUE:
    m_seuilMax[2] = seuilMax;
    break;
  case PixelMod::ALPHA:
    m_seuilMax[3] = seuilMax;
    break;
  }
}


/** Methodes */
Matrix<unsigned int>* ColorConvertOperation::updateInternalPreview() {
  //if (m_previewData != NULL) delete m_previewData;
  //m_pictureData = m_picture->getData();
  m_previewData = new Matrix<unsigned int>(m_pictureData->getWidth(), m_pictureData->getHeight());
  std::cout<<"should come here"<<std::endl;
  for (int i = 0; i < m_pictureData->getWidth(); i++)
    for (int j = 0; j < m_pictureData->getHeight(); j++) {
      int color[4] = {
	PixelMod::getRed(m_pictureData->getValue(i, j)),
	PixelMod::getGreen(m_pictureData->getValue(i, j)),
	PixelMod::getBlue(m_pictureData->getValue(i, j)),
	PixelMod::getAlpha(m_pictureData->getValue(i, j))
      };
      double result[4] = { 0, 0, 0, 0 };
      for (int k = 0; k < 4; k++) {
	result[k] = 0.0;
	for (int k2 = 0; k2 < 4; k2++) result[k] += ((double)m_kernel->getValue(k, k2)) * color[k2];
	if (result[k] < m_seuilMin[k]) result[k] = m_seuilMin[k];
	if (result[k] > m_seuilMax[k]) result[k] = m_seuilMax[k];
      }
      m_previewData->setValue(i, j, PixelMod::createRGB(PixelMod::threshold(result[0]),
							PixelMod::threshold(result[1]),
							PixelMod::threshold(result[2]),
							PixelMod::threshold(result[3])));
    }
  return m_previewData;
}

Picture* ColorConvertOperation::applyInternalOperation() {
  std::cout<<"should come here"<<std::endl;
  m_pictureData = m_picture->getData();
  m_picture->getBackground()->setData(updatePreview());
  m_picture->refresh();
  return m_picture;
}
