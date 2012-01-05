#ifndef _TOOLBAR_MAKER_HH_
#define _TOOLBAR_MAKER_HH_

#include <QToolBar>

class UserInterface;
class ActionMaker;


class ToolBarMaker {

public:

  /** Constructeurs et destructeur */
  ToolBarMaker(ActionMaker*, UserInterface*);
  ~ToolBarMaker();

  /** Accesseurs */
  QToolBar* getFileToolBar() const;
  QToolBar* getEditToolBar() const;
  QToolBar* getViewToolBar() const;
  QToolBar* getHelpToolBar() const;
  QToolBar* getOperationToolBar() const;

private:

  /** Methodes internes */
  QToolBar* createFileToolBar(ActionMaker*, UserInterface*);
  QToolBar* createEditToolBar(ActionMaker*, UserInterface*);
  QToolBar* createViewToolBar(ActionMaker*, UserInterface*);
  QToolBar* createHelpToolBar(ActionMaker*, UserInterface*);
  QToolBar* createOperationToolBar(ActionMaker*, UserInterface*);

  /** Attributs */
  QToolBar* m_fileToolBar;
  QToolBar* m_editToolBar;
  QToolBar* m_viewToolBar;
  QToolBar* m_helpToolBar;
  QToolBar* m_operationToolBar;

};

#endif
