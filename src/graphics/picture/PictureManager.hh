#ifndef _PICTUREMANAGER_HH_ 
#define _PICTUREMANAGER_HH_

#include "TabPanel.hh"
#include <QList>
#include <QButtonGroup>
#include <QGridLayout>
#include <QResizeEvent>

class UserInterface;
class PictureButton;
class PictureModifier;

class PictureManager : public TabPanel  {

public : 
  
  /** Constructeurs et destructeur */
  PictureManager(UserInterface*);
  ~PictureManager(); 
  
  /** Methodes */
  Picture* getSelectedPicture();
  void addPictureModifier(PictureModifier*);
  void removePictureModifier(PictureModifier*);
  void refresh();
  
  
private : 
  
  /** Attributs */
  int m_nbCol;
  int m_nbLig;
  QWidget *m_QWidget;
  QGridLayout *m_layout;
  QList<PictureButton*> m_listPictureButton; 
  QButtonGroup *m_buttonGroup;
  /** Override Methodes from QWidget**/
  void 	resizeEvent ( QResizeEvent * event);
};

#endif
