#include "PictureModifier.hh"

#include "UserInterface.hh"
#include "TracingManager.hh"
#include "PictureViewer.hh"
#include "Picture.hh"
#include "Matrix.hh"

/** Constructeurs et destructeur */
PictureModifier::PictureModifier(Picture* picture, UserInterface* userInterface) :
  TabPanel(userInterface),
  m_picture(picture)
{
  m_image = new QImage(m_picture->getWidth(), m_picture->getHeight(), QImage::Format_ARGB32);
  refresh();
  
  m_pictureViewer = new PictureViewer(this);
  m_tracingManager = new TracingManager(this);

  setTabName(m_picture->getName());
  setWidget(m_pictureViewer);
}

PictureModifier::~PictureModifier() {
  delete m_tracingManager;
}


/** Accesseurs */
QImage* PictureModifier::getImage() { return m_image; }

Picture* PictureModifier::getPicture() { return m_picture; }

TracingManager* PictureModifier::getTracingManager() { return m_tracingManager; }


/** Methodes */
Picture* PictureModifier::getSelectedPicture() { getPicture(); }

void PictureModifier::refresh() {
  // /!\ penser a gerer le redimensionnement possible de l'image (Segmentation Fault)
  Matrix<unsigned int>* pictureData = m_picture->getData();
  for (int i = 0; i < pictureData->getWidth(); i++)
    for (int j = 0; j < pictureData->getHeight(); j++)
      m_image->setPixel(i, j, (uint)pictureData->getValue(i, j));
}
