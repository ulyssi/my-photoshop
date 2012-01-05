#ifndef _USER_INTERFACE_HH_
#define _USER_INTERFACE_HH_

#include <QMainWindow>
#include <QTabWidget>
#include <QDockWidget>
#include <QMenu>

class ActionMaker;
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
  void createMenuBar();
  QTabWidget* createTabWidget();
  QDockWidget* createDockWidget(QWidget* widget);

  QMenu* createFileMenu();
  QMenu* createEditMenu();
  QMenu* createViewMenu();
  QMenu* createHelpMenu();
  QMenu* createOperationMenu();


  /** Attributs */
  ActionMaker* m_actionMaker;
  ToolBarMaker* m_toolBarMaker;
  ToolMaker* m_toolMaker;
  PictureManager* m_pictureManager;
  QTabWidget* m_viewTabWidget;

  QMenu* m_fileMenu;
  QMenu* m_editMenu;
  QMenu* m_viewMenu;
  QMenu* m_helpMenu;
  QMenu* m_operationMenu;
  
};

#endif
