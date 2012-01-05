#ifndef _PICTURE_MODIFIER_HH_
#define _PICTURE_MODIFIER_HH_

class Picture;
class UserInterface;
class PictureArea;
class TracingManager;

class PictureModifier {

public :
  
  /** Constructeurs et destructeur */
  PictureModifier(Picture*, UserInterface*); 
  ~PictureModifier(); 
  
  /** Accesseurs */
  Picture* getPicture() const;
  PictureArea* getPictureArea() const;
  TracingManager* getTracingManager() const;

private :

  /** Attributs */
  UserInterface* m_userInterface;
  Picture* m_picture;
  PictureArea* m_pictureArea;
  TracingManager* m_tracingManager;

};

#endif
