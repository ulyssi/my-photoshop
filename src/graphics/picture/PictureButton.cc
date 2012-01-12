#include "PictureButton.hh"
#include "PictureModifier.hh"
#include "Picture.hh"
/*Constructeur et destructeur */

PictureButton::PictureButton(PictureModifier *pictureModifier) :
  PictureViewer(pictureModifier),
  m_pictureModifier(pictureModifier)
{  setIcon(QPixmap::fromImage((const QImage&)(*(m_pictureModifier->getImage()))));
  setCheckable(true);
  m_size= new QSize(128,128);
  setIconSize(*m_size);
  setCheckable(true);
}

PictureButton::~PictureButton() {}

QSize* PictureButton::geticonSize(){return m_size;}
 
void PictureButton::seticonSize(int width , int height){
  setIconSize(QSize(width,height));
}

Picture* PictureButton::getPicture(){
  return m_pictureModifier->getPicture();
}

