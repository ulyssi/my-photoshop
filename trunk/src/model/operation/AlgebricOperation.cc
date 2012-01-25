#include "AlgebricOperation.hh"

#include "Tracing.hh"
#include "Picture.hh"


/** Constructeurs et destructeur */
AlgebricOperation::AlgebricOperation(Picture* picture, Operation* operation) :
  m_operation(operation),
  m_picture(picture),
  m_kernel(0),
  m_pictureData(0),
  m_previewData(0)
{}

AlgebricOperation::~AlgebricOperation() {}


/** Mutateurs */
void AlgebricOperation::setKernel(Matrix<double>* kernel) { m_kernel = kernel; }


/** Methodes */
Matrix<unsigned int>* AlgebricOperation::updatePreview() {
  if (m_previewData != 0) delete m_previewData;
  m_pictureData = m_picture->getData();
  m_previewData = new Matrix<unsigned int>(m_pictureData->getWidth(), m_pictureData->getHeight());
  return m_previewData;
}

Picture* AlgebricOperation::applyOperation() {
  m_pictureData = m_picture->getData();
  m_picture->getBackground()->setData(updatePreview());
  m_picture->refresh();
  return m_picture;
}


/** Methodes internes */
Matrix<unsigned int>* AlgebricOperation::binarization(Matrix<unsigned int>* data) {
  unsigned int color1 = PixelMod::createBinary(false);
  unsigned int color2 = PixelMod::createBinary(true);

  for (int k = 0; k < 5; k++) {
    


  }
  
  return data;
}
