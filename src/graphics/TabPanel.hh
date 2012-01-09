#ifndef _TAB_PANEL_HH_
#define _TAB_PANEL_HH_

#include <QString>
#include <vector>

class UserInterface;
class Picture;

class TabPanel {

public : 
  
  /** Constructeurs et destructeur */
  TabPanel(UserInterface*);
  ~TabPanel();
  
  /** Accesseurs */
  QString getTabName();
  UserInterface* getUserInterface();

  /** Mutateurs */
  void setTabName(QString);
  
  /** Methodes */
  virtual std::vector<Picture*> getSelectedPicture() = 0;
  virtual void refresh() = 0;

private : 
  
  /** Attributs */
  UserInterface* m_userInterface; 
  QString m_tabName;
  
};

#endif
