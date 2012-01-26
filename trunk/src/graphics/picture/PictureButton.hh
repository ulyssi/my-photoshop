#ifndef _PICTURE_BUTTON_
#define _PICTURE_BUTTON_

#include <QPushButton>
#include <QSize>

#include "PictureViewer.hh" 
class PictureModifier;
class Picture;
class UserInterface;
class PictureButton :  public QPushButton {
Q_OBJECT
public : 
  /** Constructeurs et destructeur */
  PictureButton(PictureModifier*,UserInterface*); 
  ~PictureButton(); 
  QSize *geticonSize();
  void seticonSize(int,int);
  Picture* getPicture();
public slots:
  void clicked(); 

private: 
  /** Attributs */
  QSize* m_size;
  PictureModifier* m_pictureModifier;
  UserInterface* m_userInterface;
};

#endif
