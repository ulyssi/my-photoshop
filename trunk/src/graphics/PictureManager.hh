#ifndef _PICTUREMANAGER_HH_ 
#define _PICTUREMANAGER_HH_

#include <QScrollArea>
#include <QString>
#include <QList>

class UserInterface;
class PictureButton;
class PictureModifier;

class PictureManager : public QWidget { Q_OBJECT 

public : 
  
  /** Constructeurs et destructeur */
  PictureManager(UserInterface*);
  ~PictureManager(); 
  
  /** Accesseurs */
  const QString& getTabName() const;

  /** Methodes */
  void addPictureModifier(PictureModifier*);
  
private : 
  
  /** Attributs */
  UserInterface* m_userInterface; 
  QString m_tabName;
  QList<PictureButton*> m_listPictureButton; 
  
};
#endif
