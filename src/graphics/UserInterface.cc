#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include "UserInterface.hh"
#include "ActionMaker.hh"
#include "MenuMaker.hh"
#include "ToolBarMaker.hh"
#include "ToolMaker.hh"
#include "PictureManager.hh"
#include "PictureModifier.hh"
#include "Picture.hh"


/** Constructeurs et Destructeurs */
UserInterface::UserInterface() :
  m_actionMaker(new ActionMaker(this)),
  m_menuMaker(new MenuMaker(m_actionMaker, this)),
  m_toolBarMaker(new ToolBarMaker(m_actionMaker, this)),
  m_toolMaker(new ToolMaker()),
  m_pictureManager(new PictureManager(this)),
  m_viewTabWidget(createTabWidget())
{
  menuBar()->addMenu(m_menuMaker->getFileMenu());
  menuBar()->addMenu(m_menuMaker->getEditMenu());
  menuBar()->addMenu(m_menuMaker->getViewMenu());
  menuBar()->addMenu(m_menuMaker->getOperationMenu());
  menuBar()->addMenu(m_menuMaker->getHelpMenu());

  addDockWidget(Qt::LeftDockWidgetArea, createDockWidget((QWidget*)(m_toolMaker->getDefaultColorChooser())));
  addDockWidget(Qt::LeftDockWidgetArea, createDockWidget((QWidget*)(m_toolMaker->getDefaultOperationChooser())));
  setCentralWidget(m_viewTabWidget);
  setWindowTitle(tr("MyPhotoShop"));
  resize(500, 400);
  
  m_actionMaker->updateActions();
}

UserInterface::~UserInterface() {
  delete m_pictureManager;
  delete m_menuMaker;
  //delete m_toolBarMaker;
  delete m_actionMaker;
}




/** Methodes internes */
QTabWidget* UserInterface::createTabWidget() {
  QTabWidget* tabWidget = new QTabWidget(this);
  tabWidget->addTab(m_pictureManager, m_pictureManager->getTabName());
  return tabWidget;
}

QDockWidget* UserInterface::createDockWidget(QWidget* widget) {
  QDockWidget* dockWidget = new QDockWidget();
  dockWidget->setWidget(widget);
  return dockWidget;
}
