#ifndef _TAB_WIDGET_HH_
#define _TAB_WIDGET_HH_

#include <QTabWidget>
#include <QWidget>
#include <QPushButton>
#include <QList>

class MPushButton;
class UserInterface;
class TabPanel;

class TabWidget : public QTabWidget { Q_OBJECT

public :

  /** Constructeurs et destructeur */
  TabWidget(UserInterface* userInterface);
  ~TabWidget();

  /** Accesseurs */
  TabPanel* getTabPanel();
  
  /** Methode */
  int addTab(TabPanel*);
		       
  		   
public slots :
  
  /** Slots */
  void closeTab(int);
  void selectTab(int);

private :

  /** Methodes internes */
  QPushButton* createNewTabButton();
  QPushButton* createCloseButton();

  /** Attributs */
  UserInterface* m_userInterface;
  QList<MPushButton*> m_listpushbutton;

};

#endif
