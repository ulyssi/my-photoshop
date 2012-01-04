#ifndef _USERINTERFACE_HH_
#define _USERINTERFACE_HH_

#include <QMainWindow>
#include <QApplication>
#include <QTabWidget>

#include "ActionMaker.hh"
#include "MenuMaker.hh"
#include "PictureManager.hh"

class UserInterface : public QMainWindow { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  UserInterface();
  ~UserInterface();
                 
private:

  /** Attributs */
  ActionMaker* m_actionMaker;
  MenuMaker* m_menuMaker;
  PictureManager* m_pictureManager;
  QTabWidget* m_tabWidget;
};

#endif
