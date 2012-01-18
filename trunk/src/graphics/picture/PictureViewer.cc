#include "PictureViewer.hh"
#include "PictureModifier.hh"


PictureViewer::PictureViewer(PictureModifier* pictureModifier) :
  m_pictureModifier(pictureModifier)
{ 
  m_scale=1.0;
  m_scaleFactor=0.25;
  refreshData();
  refresh();
} 

PictureViewer::~PictureViewer() {}

/** Methodes */
void PictureViewer::scaleImage(double scale){
  m_qImage=m_qImage.scaled((int)m_qImage.width()*scale,(int)m_qImage.height()*scale);
  resize(m_qImage.width(), m_qImage.height());
  setPixmap(QPixmap::fromImage((const QImage&)(m_qImage)));
    
}


void PictureViewer::zoomIn() { 
  double scale=m_scale+m_scaleFactor;
  if((m_qImage.width()*m_scaleFactor)<100000
     &&(m_qImage.height()*m_scaleFactor)<10000)
    m_scale=scale;
  
} 

void PictureViewer::zoomOut() { 
  double scale=m_scale-m_scaleFactor;
  if((m_qImage.width()*m_scaleFactor)>30 && 
     (m_qImage.height()*m_scaleFactor)>30)
    m_scale=scale;
}

void PictureViewer::normalSize(){
  m_scale=1.0;
}
void PictureViewer::fitToWindow(QSize size){
  std::cout<<"mscale2 "<<m_qImage.width()<<std::endl;
  //  float scale =(float)((float)m_qImage.width()/((float)size.width()));
  //std::cout<<scale<<std::endl;
  //m_scale = 1/scale;
  std::cout<<m_scale<<std::endl;
}


void PictureViewer::refresh() {
  refreshData();
  scaleImage(m_scale);
}


void PictureViewer::refreshData(){
  m_qImage=m_pictureModifier->getImage()->scaled(m_pictureModifier->getImage()->width(),m_pictureModifier->getImage()->height());
  resize(m_pictureModifier->getImage()->width(),m_pictureModifier->getImage()->height());
}

