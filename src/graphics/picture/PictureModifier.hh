#ifndef _PICTURE_MODIFIER_HH_
#define _PICTURE_MODIFIER_HH_

#include "TabPanel.hh"
#include <QImage>

class Picture;
class PictureViewer;
class UserInterface;
class TracingManager;
class Histogram;

class PictureModifier : public TabPanel {

public :
  
  /** Constructeurs et destructeur */
  PictureModifier(Picture*, UserInterface*); 
  ~PictureModifier();
  
  /** Accesseurs */
  QImage* getImage();
  Picture* getPicture();
  Histogram* getHistogram();
  TracingManager* getTracingManager();
  
  /** Methodes */
  Picture* getSelectedPicture();
  void notifyCurrent();
  void refresh();

private :

  /** Attributs */
  QImage* m_image;
  Picture* m_picture;
  Histogram* m_histogram;
  PictureViewer* m_pictureViewer;
  TracingManager* m_tracingManager;
  
};

#endif
