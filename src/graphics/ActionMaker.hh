#ifndef _ACTIONMAKER_HH_
#define _ACTIONMAKER_HH_

#include <QAction>

#include "UserInterface.hh"

class ActionMaker {

public:
  
  /** Constructeurs et destructeur */
  ActionMaker(UserInterface*);
  ~ActionMaker();

  /** Methodes */
  void updateActions();

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
  void createFileAction();
  void createEditAction();
  void createViewAction();
  void createOperationAction();
  void createHelpAction();

  /** Attributs */
  UserInterface* m_userInterface;

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
