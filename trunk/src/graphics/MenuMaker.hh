#ifndef _MENUMAKER_HH_
#define _MENUMAKER_HH_

#include <QMenu>

class UserInterface;
class ActionMaker;


class MenuMaker {

public:

  /** Constructeurs et destructeur */
  MenuMaker(ActionMaker*, UserInterface*);
  ~MenuMaker();

  /** Accesseurs */
  QMenu* getFileMenu() const;
  QMenu* getEditMenu() const;
  QMenu* getViewMenu() const;
  QMenu* getHelpMenu() const;
  QMenu* getOperationMenu() const;

private:

  /** Methodes internes */
  QMenu* createFileMenu(ActionMaker*, UserInterface*);
  QMenu* createEditMenu(ActionMaker*, UserInterface*);
  QMenu* createViewMenu(ActionMaker*, UserInterface*);
  QMenu* createHelpMenu(ActionMaker*, UserInterface*);
  QMenu* createOperationMenu(ActionMaker*, UserInterface*);

  /** Attributs */
  QMenu* m_fileMenu;
  QMenu* m_editMenu;
  QMenu* m_viewMenu;
  QMenu* m_helpMenu;
  QMenu* m_operationMenu;

};

#endif
