#ifndef _PICTURE_MODIFIER_HH_
#define _PICTURE_MODIFIER_HH_

#include "TabPanel.hh"
#include <QImage>

class Picture;
class PictureViewer;
class UserInterface;

class PictureModifier : public TabPanel {

public :
  
  /** Constructeurs et destructeur */
  PictureModifier(Picture*, UserInterface*); 
  ~PictureModifier();
  
  /** Accesseurs */
  QImage* getImage();
  Picture* getPicture();
  
  /** Methodes */
  Picture* getSelectedPicture();
  void notifyCurrent();
  void refresh();

private :

  /** Attributs */
  Picture* m_picture;
  QImage* m_image;
  PictureViewer* m_pictureViewer;
  
};

#endif
