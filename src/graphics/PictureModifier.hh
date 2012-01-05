#ifndef _PICTURE_MODIFIER_HH_
#define _PICTURE_MODIFIER_HH_

class Picture;
class UserInterface;
class PictureViewer;
class TracingManager;

class PictureModifier {

public :
  
  /** Constructeurs et destructeur */
  PictureModifier(Picture*, UserInterface*); 
  ~PictureModifier(); 
  
  /** Accesseurs */
  Picture* getPicture() const;
  PictureViewer* getPictureViewer() const;
  TracingManager* getTracingManager() const;

private :

  /** Attributs */
  UserInterface* m_userInterface;
  Picture* m_picture;
  PictureViewer* m_pictureViewer;
  TracingManager* m_tracingManager;

};

#endif
