#ifndef _USER_INTERFACE_HH_
#define _USER_INTERFACE_HH_

#include <QMainWindow>
#include <QTabWidget>
#include <QDockWidget>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QApplication>

#include "Matrix.hh"

class ToolMaker;
class PictureManager;
class MTabWidget;

class UserInterface : public QMainWindow { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  UserInterface(QApplication *);
  ~UserInterface();

  /** Methodes */

public :
  void close(QWidget*);
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

  void binary();
  void greyScale();
  void rescale();

  void colorConvertOperation(Matrix<double>* application = NULL);
  void convolveOperation(Matrix<double>* filter = NULL);

  void about();
      
private:

  /** Methodes internes */
  void createActions();
  void createMenuBar();
  void createToolBar();
  MTabWidget* createTabWidget();
  QDockWidget* createDockWidget(QWidget* widget);

  QMenu* createFileMenu();
  QMenu* createEditMenu();
  QMenu* createViewMenu();
  QMenu* createHelpMenu();
  QMenu* createOperationMenu();
  
  QToolBar* createFileToolBar();
  QToolBar* createEditToolBar();
  QToolBar* createViewToolBar();
  QToolBar* createHelpToolBar();
  QToolBar* createOperationToolBar();

  void updateActions();
  void createFileAction();
  void createEditAction();
  void createViewAction();
  void createHelpAction();
  void createOperationAction();

  /** Attributs */
  QApplication* m_QApplication;
  ToolMaker* m_toolMaker;
  PictureManager* m_pictureManager;
  MTabWidget* m_viewTabWidget;

  QMenu* m_fileMenu;
  QMenu* m_editMenu;
  QMenu* m_viewMenu;
  QMenu* m_helpMenu;
  QMenu* m_operationMenu;

  QToolBar* m_fileToolBar;
  QToolBar* m_editToolBar;
  QToolBar* m_viewToolBar;
  QToolBar* m_helpToolBar;
  QToolBar* m_operationToolBar;

  QAction* m_openAct;
  QAction* m_saveAct;
  QAction* m_exitAct;

  QAction* m_undoAct;
  QAction* m_redoAct;

  QAction* m_zoomInAct;
  QAction* m_zoomOutAct;
  QAction* m_normalSizeAct;
  QAction* m_fitToWindowAct;

  QAction* m_blackAndWhiteAct;
  QAction* m_rescaleAct;

  QAction* m_aboutAct;
  QAction* m_aboutQtAct;

};

#endif
