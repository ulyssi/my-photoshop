#ifndef _PICTUREBUTTON_
#define _PICTUREBUTTON_

#include "ImageViewer.hh" 
#include "PictureModifier.hh"

class PictureButton : public ImageViewer { Q_OBJECT

public : 
  PictureButton(PictureModifier * ); 
  ~PictureButton(); 
private: 
  
};

#endif
