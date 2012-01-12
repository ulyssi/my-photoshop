#include "AffineTransformationOperation.hh"

#include "Picture.hh"


/** Constructeurs et destructeur */
AffineTransformationOperation::AffineTransformationOperation(Picture* picture, Operation* operation) :
  Operation(operation),
  m_operation(operation),
  m_picture(picture),
  m_pictureData(NULL),
  m_previewData(NULL)
{}

AffineTransformationOperation::~AffineTransformationOperation() {
  if (m_previewData != NULL) delete m_previewData;
  if (m_pictureData != NULL) delete m_pictureData;
}


/** Accesseurs */
Picture* AffineTransformationOperation::getPicture() { return m_picture; }

PixelMod::Type AffineTransformationOperation::getInputType() { return PixelMod::COLOR; }

PixelMod::Type AffineTransformationOperation::getOutputType() { 
  // if (m_operation != NULL) return m_operation->getOutType();
  return PixelMod::COLOR; 
}


/** Methodes */
Matrix<unsigned int>* AffineTransformationOperation::preview(double scaleFactor, double angle) {
  // if (m_operation != NULL) m_pictureData = m_operation->preview();
  return m_picture->getData(); 
}

Picture* AffineTransformationOperation::apply(double, double) { return m_picture; }
