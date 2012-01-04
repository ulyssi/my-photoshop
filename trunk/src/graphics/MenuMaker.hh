#ifndef _MENUMAKER_HH_
#define _MENUMAKER_HH_

#include <QMenu>

class MenuMaker {

public:

  /** Constructeurs et destructeur */
  MenuMaker(UserInterface*);
  ~MenuMaker();

  /** Accesseurs */
  QMenu* getFileMenu();
  QMenu* getEditMenu();
  QMenu* getViewMenu();
  QMenu* getOperationMenu();
  QMenu* getHelpMenu();

private:

  /** Methodes internes */
  void createFileMenu();
  void createEditMenu();
  void createViewMenu();
  void createOperationMenu();
  void createHelpMenu();

  /** Attributs */
  QMenu* m_fileMenu;
  QMenu* m_editMenu;
  QMenu* m_viewMenu;
  QMenu* m_operationMenu;
  QMenu* m_helpMenu;

};

#endif
