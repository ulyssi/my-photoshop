#ifndef _PICTUREMODIFIER_HH_
#define _PICTUREMODIFIER_HH_

class Picture;
class UserInterface;
class ImageViewer;
class TracingManager;

class PictureModifier  {

public :
  
  /** Constructeurs et destructeur */
  PictureModifier(Picture*, UserInterface*); 
  ~PictureModifier(); 
  
  /** Accesseurs */
  Picture* getPicture() const;
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
