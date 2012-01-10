#ifndef _PICTURE_BUTTON_
#define _PICTURE_BUTTON_

#include <QPushButton>

#include "PictureViewer.hh" 

class PictureModifier;


class PictureButton : public PictureViewer, public QPushButton {

public : 

  /** Constructeurs et destructeur */
  PictureButton(PictureModifier*); 
  ~PictureButton(); 

private: 

  /** Attributs */
  PictureModifier* m_pictureModifier;
  
};

#endif
