#ifndef _TAB_PANEL_HH_
#define _TAB_PANEL_HH_

#include <QScrollArea>
#include <QString>

class UserInterface;
class Picture;

class TabPanel : public QScrollArea { Q_OBJECT

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
  virtual Picture* getSelectedPicture() = 0;
  virtual void notifyCurrent();
  virtual void refresh() = 0;
  virtual void zoomIn();
  virtual void zoomOut();  
  virtual void normalSize();
  virtual void fitToWindow();
  virtual void copy();
  virtual void paste();
  virtual void cut();
  virtual bool enableSelection();
  virtual void disableSelection();
  virtual bool enableMove();
  virtual void disableMove();
private : 
  
  /** Attributs */
  UserInterface* m_userInterface; 
  QString m_tabName;
  
};

#endif
