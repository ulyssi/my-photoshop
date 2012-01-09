#ifndef _PICTURE_MODIFIER_HH_
#define _PICTURE_MODIFIER_HH_

#include "TabPanel.hh"

class Picture;
class PictureViewer;
class UserInterface;
class TracingManager;

class PictureModifier : public TabPanel {

public :
  
  /** Constructeurs et destructeur */
  PictureModifier(Picture*, UserInterface*); 
  ~PictureModifier(); 
  
  /** Accesseurs */
  Picture* getPicture() const;
  TracingManager* getTracingManager() const;

  /** Methodes */
  std::vector<Picture*> getSelectedPicture();
  void refresh();

private :

  /** Attributs */
  Picture* m_picture;
  PictureViewer* m_pictureViewer;
  TracingManager* m_tracingManager;

};

#endif
