#ifndef _USER_INTERFACE_HH_
#define _USER_INTERFACE_HH_

#include <QMainWindow>
#include <QTabWidget>
#include <QDockWidget>

class ActionMaker;
class MenuMaker;
class ToolBarMaker;
class ToolMaker;
class PictureManager;

class UserInterface : public QMainWindow { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  UserInterface();
  ~UserInterface();

public slots:
  
  /** Slots */
  void open();
  void save();
  void exit();

  void undo();
  void redo();

  void zoomIn();
  void zoomOut();
  void normalSize();
  void fitToWindow();

  void blackAndWhite();
  void rescale();

  void about();
      
private:

  /** Methodes internes */
  QTabWidget* createTabWidget();
  QDockWidget* createDockWidget(QWidget* widget);

  /** Attributs */
  ActionMaker* m_actionMaker;
  MenuMaker* m_menuMaker;
  ToolBarMaker* m_toolBarMaker;
  ToolMaker* m_toolMaker;
  PictureManager* m_pictureManager;
  QTabWidget* m_viewTabWidget;
  

};

#endif
