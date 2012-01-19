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


double PictureViewer::zoomIn() { 
  double scale=m_scale+m_scaleFactor;
  if((m_qImage.width()*m_scaleFactor)<100000
     &&(m_qImage.height()*m_scaleFactor)<10000)
    m_scale=scale;
  return m_scaleFactor;
} 

double PictureViewer::zoomOut() { 
  double scale=m_scale-m_scaleFactor;
  if((m_qImage.width()*m_scaleFactor)>10 && 
     (m_qImage.height()*m_scaleFactor)>10)
    m_scale=scale;
  return -m_scaleFactor;
}

double PictureViewer::normalSize(){
  double t_scale=m_scale;
  m_scale=1.0;
  return 1.0/t_scale;
}
double PictureViewer::fitToWindow(QSize size){
  refreshData();
  refresh();
  // std::cout<<"mscale2 "<<m_qImage.width()<<std::endl;
  float scaleW=(float)((float)m_qImage.width()/((float)size.width()));
  float scaleH=(float)((float)m_qImage.height()/((float)size.height())); 
  //std::cout<<scaleW<<std::endl;
  //std::cout<<scaleH<<std::endl;
  if(scaleH>scaleW)
    m_scale = 1/scaleH;
  else 
    m_scale =1 /scaleW;
  std::cout<<m_scale<<std::endl;
  return m_scale;
}


void PictureViewer::refresh() {
  refreshData();
  scaleImage(m_scale);

}


void PictureViewer::refreshData(){
  m_qImage=m_pictureModifier->getImage()->scaled(m_pictureModifier->getImage()->width(),m_pictureModifier->getImage()->height());
  resize(m_pictureModifier->getImage()->width(),m_pictureModifier->getImage()->height());
}

