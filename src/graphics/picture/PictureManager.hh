#ifndef _PICTUREMANAGER_HH_ 
#define _PICTUREMANAGER_HH_

#include "TabPanel.hh"

#include <QList>

class UserInterface;
class PictureButton;
class PictureModifier;

class PictureManager : public TabPanel {

public : 
  
  /** Constructeurs et destructeur */
  PictureManager(UserInterface*);
  ~PictureManager(); 
  
  /** Methodes */
  std::vector<Picture*> getSelectedPicture();
  void addPictureModifier(PictureModifier*);
  void refresh();
 
private : 
  
  /** Attributs */
  QList<PictureButton*> m_listPictureButton; 
  
};

#endif
