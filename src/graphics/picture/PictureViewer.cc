#include "PictureViewer.hh"
#include "PictureModifier.hh"


PictureViewer::PictureViewer(PictureModifier* pictureModifier) :
  m_pictureModifier(pictureModifier){ 
  refreshData();
  refresh();
  m_scaleFactor=1.0;
}

PictureViewer::~PictureViewer() {}

/** Methodes */
void PictureViewer::scaleImage(double scaleFactor){
  m_qImage=m_qImage.scaled((int)m_qImage.width()*scaleFactor,(int)m_qImage.height()*scaleFactor);
  resize(m_qImage.width(), m_qImage.height());
  setPixmap(QPixmap::fromImage((const QImage&)(m_qImage)));
    
}


void PictureViewer::zoomIn() { 
  int scaleFactor=m_scaleFactor+0.25;
  if(m_qImage.width()*scaleFactor>30&&m_qImage.width()*scaleFactor<4000&&m_qImage.height()*scaleFactor<4000&&m_qImage.height()*scaleFactor>30)
     m_scaleFactor=scaleFactor;
}

void PictureViewer::zoomOut() { 
  int scaleFactor=m_scaleFactor-0.25;
  if(m_qImage.width()*scaleFactor>30 && m_qImage.width()*scaleFactor<4000
     &&m_qImage.height()*scaleFactor<4000 && m_qImage.height()*scaleFactor>30)
    m_scaleFactor=scaleFactor;
}


void PictureViewer::refresh() {
  refreshData();
  scaleImage(m_scaleFactor);
}


void PictureViewer::refreshData(){
  m_qImage=m_pictureModifier->getImage()->scaled(m_pictureModifier->getImage()->width(),m_pictureModifier->getImage()->height());
  resize(m_pictureModifier->getImage()->width(),m_pictureModifier->getImage()->height());
}

