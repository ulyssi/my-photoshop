#include "PictureButton.hh"
#include "PictureModifier.hh"
#include "../../model/Picture.hh"
#include "../UserInterface.hh"
#include <QFileInfo>
/*Constructeur et destructeur */

PictureButton::PictureButton(PictureModifier *pictureModifier,UserInterface* userinterface) :
  m_pictureModifier(pictureModifier)
{ m_userInterface = userinterface;
  setIcon(QPixmap::fromImage((const QImage&)(*(m_pictureModifier->getImage()))));
  setCheckable(true);
  m_size= new QSize(128,128);
  setIconSize(*m_size);
  setCheckable(true);
  QObject::connect((QAbstractButton*)this,SIGNAL(pressed()),this, SLOT(clicked()));


}

PictureButton::~PictureButton() {}

QSize* PictureButton::geticonSize(){return m_size;}

void PictureButton::seticonSize(int width , int height){
  setIconSize(QSize(width,height));
}

Picture* PictureButton::getPicture(){
  return m_pictureModifier->getPicture();
}

#include <iostream>
void PictureButton::clicked(){
  QString string;
  QString num;
  QFileInfo* m_file = new QFileInfo(m_pictureModifier->getPicture()->getPath());
  string = QString("Picture informations: width : ");
  num.setNum(m_pictureModifier->getImage()->width());
  string +=num;
  string +=QString("  height :");
  num.setNum(m_pictureModifier->getImage()->height());
  string +=num;
  string +=QString(" size : ");
  num.setNum(m_file->size());
  string +=num;
  string +=QString(" bytes  ~");
   num.setNum((double)((float)m_file->size()/1000.0),'f',2);
  string +=num;
  string +=QString(" Mb");
  m_userInterface->print(string);
}
