#ifndef _USERINTERFACE_HH_
#define _USERINTERFACE_HH_

#include <QMainWindow>
#include <QTabWidget>

class ActionMaker;
class MenuMaker;
class PictureManager;

class UserInterface : public QMainWindow { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  UserInterface();
  ~UserInterface();

  /** Accesseurs */
  ActionMaker* getActionMaker() const;
                 
private:

  /** Attributs */
  ActionMaker* m_actionMaker;
  MenuMaker* m_menuMaker;
  PictureManager* m_pictureManager;
  QTabWidget* m_tabWidget;
};

#endif
