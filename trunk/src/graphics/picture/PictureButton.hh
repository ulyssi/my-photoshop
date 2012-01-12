#ifndef _PICTURE_BUTTON_
#define _PICTURE_BUTTON_

#include <QPushButton>
#include <QSize>

#include "PictureViewer.hh" 
class PictureModifier;
class Picture;
class PictureButton : public PictureViewer, public QPushButton {
public : 

  /** Constructeurs et destructeur */
  PictureButton(PictureModifier*); 
  ~PictureButton(); 
  QSize *geticonSize();
  void seticonSize(int,int);
  Picture* getPicture();

private: 

  /** Attributs */
  QSize* m_size;
  PictureModifier* m_pictureModifier;
  
};

#endif
