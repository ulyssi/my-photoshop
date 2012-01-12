#include "PictureModifier.hh"

#include "UserInterface.hh"
#include "TracingManager.hh"
#include "PictureViewer.hh"
#include "Histogram.hh"
#include "Picture.hh"
#include "Matrix.hh"
#include "AffineOperationChooser.hh"


/** Constructeurs et destructeur */
PictureModifier::PictureModifier(Picture* picture, UserInterface* userInterface) :
  TabPanel(userInterface),
  m_picture(picture),
  m_image(new QImage(m_picture->getWidth(), m_picture->getHeight(), QImage::Format_ARGB32))
{
  m_pictureViewer = new PictureViewer(this);

  setTabName(m_picture->getName());
  refresh();
}

PictureModifier::~PictureModifier() {}


/** Accesseurs */
QImage* PictureModifier::getImage() { return m_image; }
Picture* PictureModifier::getPicture() { return m_picture; }


/** Mutateurs */
void PictureModifier::notifyCurrent() {
  getUserInterface()->getAffineOperationChooser()->setPictureModifier(this);
  getUserInterface()->getHistogram()->setPictureModifier(this);
  getUserInterface()->getTracingManager()->setPictureModifier(this);
  getUserInterface()->update();
}


/** Methodes */
Picture* PictureModifier::getSelectedPicture() { return getPicture(); }

void PictureModifier::refresh() {
  // /!\ penser a gerer le redimensionnement possible de l'image (Segmentation Fault)
  Matrix<unsigned int>* pictureData = m_picture->getData();
  if (pictureData->getWidth() != m_image->width() || pictureData->getHeight() != m_image->height()) {
    delete m_image;
    m_image = new QImage(pictureData->getWidth(), pictureData->getHeight(), QImage::Format_ARGB32);
  }
  for (int i = 0; i < pictureData->getWidth(); i++)
    for (int j = 0; j < pictureData->getHeight(); j++)
      m_image->setPixel(i, j, (uint)pictureData->getValue(i, j));
  m_pictureViewer->refresh();
  setWidget(m_pictureViewer);
  
  getUserInterface()->getHistogram()->refresh();
  getUserInterface()->getTracingManager()->refresh();
}
