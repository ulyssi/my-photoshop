#ifndef _PICTUREMODIFIER_HH_
#define _PICTUREMODIFIER_HH_

#include "UserInterface.hh"
#include "ImageViewer.hh"
#include "TracingManager.hh"
#include "../model/Picture.hh"

class PictureModifier  {

public :
  
  /** Constructeurs et destructeur */
  PictureModifier(Picture*, UserInterface*); 
  ~PictureModifier(); 
  
  /** Accesseurs */
  ImageViewer* getImageViewer() const;
  TracingManager* getTracingManager() const;

private :

  /** Attributs */
  UserInterface* m_userInterface;
  Picture* m_picture;
  ImageViewer* m_imageViewer;
  TracingManager* m_tracingManager;
};

#endif
