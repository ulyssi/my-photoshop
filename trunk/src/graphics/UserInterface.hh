#include <QMainWindow>
#include <QApplication>
#include <QTabWidget>
#include <QAction>
#include <QMenu>

#include "ImageViewer.hh"

class UserInterface : public QMainWindow { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  UserInterface();
  ~UserInterface();
                 
private slots:

  /** Slots */
  void open();
  void save();
  void undo();
  void redo();
  void zoomIn();
  void zoomOut();
  void normalSize();
  void fitToWindow();
  void blackAndWhite();
  void rescale();
  void about();
  void exit();
  
private:

  /** Methodes internes */
  void createActions();
  void createMenus();
  void updateActions();

  /** Attributs */
  QTabWidget* m_tabWidget;

  QMenu* m_fileMenu;
  QMenu* m_editMenu;
  QMenu* m_operationMenu;
  QMenu* m_helpMenu;

  ImageViewer* m_imageViewer;

  QAction* m_openAct;
  QAction* m_saveAct;
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
  QAction* m_exitAct;
};
