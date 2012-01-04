#ifndef _PICTUREMANAGER_HH_ 
#define _PICTUREMANAGER_HH_

#include <QScrollArea>
#include <QList> 
#include "UserInterface.hh"
#include "PictureButton.hh"
#include "PictureModifier.hh"

class PictureManager : public QScrollArea { Q_OBJECT 

public : 
  
  /** Constructeurs et destructeur */
  PictureManager(UserInterface*);
  ~PictureManager(); 
  
  /*Methodes publiques */
  void addPictureModifier(PictureModifier*);
  
private : 
  /** Methodes internes */
  
  /** Attributs */
  UserInterface *m_userInterface; 
  QList <PictureButton > m_listPictureButton; 
  
};
#endif
