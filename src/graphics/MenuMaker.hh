#ifndef _MENUMAKER_HH_
#define _MENUMAKER_HH_

#include <QObject>
#include <QMenu>

class UserInterface;
class ActionMaker;

class MenuMaker : public QObject {

public:

  /** Constructeurs et destructeur */
  MenuMaker(UserInterface*);
  ~MenuMaker();

  /** Accesseurs */
  QMenu* getFileMenu() const;
  QMenu* getEditMenu() const;
  QMenu* getViewMenu() const;
  QMenu* getOperationMenu() const;
  QMenu* getHelpMenu() const;

private:

  /** Accesseurs internes */
  ActionMaker* getActionMaker() const;

  /** Methodes internes */
  void createFileMenu();
  void createEditMenu();
  void createViewMenu();
  void createOperationMenu();
  void createHelpMenu();

  /** Attributs */
  UserInterface* m_userInterface;

  QMenu* m_fileMenu;
  QMenu* m_editMenu;
  QMenu* m_viewMenu;
  QMenu* m_operationMenu;
  QMenu* m_helpMenu;

};

#endif
