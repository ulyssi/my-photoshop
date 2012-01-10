#include "PictureButton.hh"

#include "PictureModifier.hh"


/*Constructeur et destructeur */
PictureButton::PictureButton(PictureModifier *pictureModifier) :
  PictureViewer(pictureModifier),
  m_pictureModifier(pictureModifier)
{
  setIcon(QPixmap::fromImage((const QImage&)(*(m_pictureModifier->getImage()))));
  setCheckable(true);
  //setFlat(true);
  setIconSize(QSize(128,128));
  
}

PictureButton::~PictureButton() {}

