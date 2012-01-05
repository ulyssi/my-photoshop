#include "UserInterface.hh"

#include <QToolBar>
#include "ToolMaker.hh"
#include "PictureManager.hh"
#include "../model/Picture.hh"
//#include "PtabWidget.hh"


/** Constructeurs et Destructeurs */
UserInterface::UserInterface() :
  m_toolMaker(new ToolMaker()),
  m_pictureManager(new PictureManager(this)),
  m_viewTabWidget(createTabWidget())
{
  createActions();
  createMenuBar();
  createToolBar();

  addDockWidget(Qt::LeftDockWidgetArea, createDockWidget((QWidget*)(m_toolMaker->getDefaultColorChooser())));
  addDockWidget(Qt::LeftDockWidgetArea, createDockWidget((QWidget*)(m_toolMaker->getDefaultOperationChooser())));

  setCentralWidget(m_viewTabWidget);
  setWindowTitle(tr("MyPhotoShop"));
  resize(1024, 768);
}
    
UserInterface::~UserInterface() {
  delete m_pictureManager;
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
