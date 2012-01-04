#ifndef _ACTION_MAKER_HH_
#define _ACTION_MAKER_HH_

#include <QAction>

class UserInterface;


class ActionMaker {

public:
  
  /** Constructeurs et destructeur */
  ActionMaker(UserInterface*);
  ~ActionMaker();

  /** Accesseurs */
  QAction* getOpenAction() const;
  QAction* getSaveAction() const;
  QAction* getExitAction() const;

  QAction* getUndoAction() const;
  QAction* getRedoAction() const;

  QAction* getZoomInAction() const;
  QAction* getZoomOutAction() const;
  QAction* getNormalSizeAction() const;
  QAction* getFitToWindowAction() const;

  QAction* getBlackAndWhiteAction() const;
  QAction* getRescaleAction() const;

  QAction* getAboutAction() const;
  QAction* getAboutQtAction() const;

  /** Methodes */
  void updateActions();

private:

  /** Methodes internes */
  void createFileAction(UserInterface*);
  void createEditAction(UserInterface*);
  void createViewAction(UserInterface*);
  void createHelpAction(UserInterface*);
  void createOperationAction(UserInterface*);

  /** Attributs */
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
