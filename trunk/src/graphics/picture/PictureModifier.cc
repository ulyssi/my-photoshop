#include "PictureModifier.hh"

#include "UserInterface.hh"
#include "TracingManager.hh"
#include "HistogramModifier.hh"
#include "PictureViewer.hh"
#include "Picture.hh"
#include "Matrix.hh"

/** Constructeurs et destructeur */
PictureModifier::PictureModifier(Picture* picture, UserInterface* userInterface) :
  TabPanel(userInterface),
  m_picture(picture)
{
  m_image = new QImage(m_picture->getWidth(), m_picture->getHeight(), QImage::Format_ARGB32);
  
  m_pictureViewer = new PictureViewer(this);
  m_tracingManager = new TracingManager(this);
  m_histogramModifier = new HistogramModifier(this);

  setTabName(m_picture->getName());
  setWidget(m_pictureViewer);

  refresh();
}

PictureModifier::~PictureModifier() {
  delete m_tracingManager;
}


/** Accesseurs */
QImage* PictureModifier::getImage() { return m_image; }

Picture* PictureModifier::getPicture() { return m_picture; }

TracingManager* PictureModifier::getTracingManager() { return m_tracingManager; }

HistogramModifier* PictureModifier::getHistogramModifier() { return m_histogramModifier; }


/** Mutateurs */
void PictureModifier::setTracingManager(TracingManager* tracingManager) {
  m_tracingManager = tracingManager;
  if (m_tracingManager != NULL) {
    m_tracingManager->setPictureModifier(this);
    m_tracingManager->refresh();
  }
}

void PictureModifier::setHistogramModifier(HistogramModifier* histogramModifier) {
  m_histogramModifier = histogramModifier;
  if (m_histogramModifier != NULL) {
    m_histogramModifier->setPictureModifier(this);
    m_histogramModifier->refresh();
  }
}


/** Methodes */
Picture* PictureModifier::getSelectedPicture() { return getPicture(); }

void PictureModifier::refresh() {
  // /!\ penser a gerer le redimensionnement possible de l'image (Segmentation Fault)
  Matrix<unsigned int>* pictureData = m_picture->getData();
  if(pictureData->getWidth()!=m_image->width()||pictureData->getHeight()!=m_image->height()){
    delete m_image;
    m_image=new QImage(pictureData->getWidth(),pictureData->getHeight(),QImage::Format_ARGB32);
  }
  for (int i = 0; i < pictureData->getWidth(); i++)
    for (int j = 0; j < pictureData->getHeight(); j++)
      m_image->setPixel(i, j, (uint)pictureData->getValue(i, j));
  m_pictureViewer->refresh();
  m_histogramModifier->refresh();
  // m_tracingManager->refresh();
}
