#include "UserInterface.hh"

#include <QToolBar>

#include "ActionMaker.hh"
#include "ToolBarMaker.hh"
#include "ToolMaker.hh"
#include "PictureManager.hh"
#include "Picture.hh"


/** Constructeurs et Destructeurs */
UserInterface::UserInterface() :
  m_actionMaker(new ActionMaker(this)),
  m_toolBarMaker(new ToolBarMaker(m_actionMaker, this)),
  m_toolMaker(new ToolMaker()),
  m_pictureManager(new PictureManager(this)),
  m_viewTabWidget(createTabWidget())
{
  createMenuBar();
  
  addToolBar(Qt::TopToolBarArea, m_toolBarMaker->getFileToolBar());
  addToolBar(Qt::TopToolBarArea, m_toolBarMaker->getEditToolBar());
  addToolBar(Qt::TopToolBarArea, m_toolBarMaker->getViewToolBar());
  addToolBar(Qt::TopToolBarArea, m_toolBarMaker->getOperationToolBar());
  addToolBar(Qt::TopToolBarArea, m_toolBarMaker->getHelpToolBar());

  addDockWidget(Qt::LeftDockWidgetArea, createDockWidget((QWidget*)(m_toolMaker->getDefaultColorChooser())));
  addDockWidget(Qt::LeftDockWidgetArea, createDockWidget((QWidget*)(m_toolMaker->getDefaultOperationChooser())));

  setCentralWidget(m_viewTabWidget);
  setWindowTitle(tr("MyPhotoShop"));
  resize(1024, 768);
  
  m_actionMaker->updateActions();
}

UserInterface::~UserInterface() {
  delete m_pictureManager;
  delete m_toolBarMaker;
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
