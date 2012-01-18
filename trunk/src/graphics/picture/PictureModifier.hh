#ifndef _PICTURE_MODIFIER_HH_
#define _PICTURE_MODIFIER_HH_

#include "TabPanel.hh"
#include <QImage>

class Picture;
class PictureViewer;
class UserInterface;
class PictureArea;

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
  void refreshData();
  void refresh();
  void zoomIn();
  void zoomOut();  
  void normalSize();
  void fitToWindow();

private :

  /** Attributs */
  Picture* m_picture;
  QImage* m_image;
  PictureArea* m_pictureArea;
  
private slots:
  /** SLOTS**/
  void 	keyPressEvent ( QKeyEvent * event );
  void 	keyReleaseEvent ( QKeyEvent * event );
};

#endif
