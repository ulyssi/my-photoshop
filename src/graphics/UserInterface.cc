#include "UserInterface.hh"

#include <QToolBar>
#include "ToolMaker.hh"
#include "PictureManager.hh"
#include "Picture.hh"
#include "MTabWidget.hh"
#include <QTabWidget>



/** Constructeurs et Destructeurs */
UserInterface::UserInterface(QApplication* qapplication) :
  m_QApplication(qapplication),
  m_toolMaker(new ToolMaker())
{
  m_pictureManager = new PictureManager(this);
  m_viewTabWidget = createTabWidget();


  createActions();
  createMenuBar();
  createToolBar();

  addDockWidget(Qt::LeftDockWidgetArea, createDockWidget((QWidget*)(m_toolMaker->getDefaultColorChooser())));
  addDockWidget(Qt::LeftDockWidgetArea, createDockWidget((QWidget*)(m_toolMaker->getDefaultOperationChooser())));

  setCentralWidget((QTabWidget*)m_viewTabWidget);
  setWindowTitle(tr("MyPhotoShop"));
  resize(1024, 768);
  

}
    
UserInterface::~UserInterface() {
  delete m_pictureManager;
}


/** Methodes internes */
MTabWidget* UserInterface::createTabWidget() {
  MTabWidget* tabWidget = new MTabWidget(this);
  tabWidget->addTab((QWidget*)m_pictureManager,m_pictureManager->getTabName());
  return tabWidget;
}
  
QDockWidget* UserInterface::createDockWidget(QWidget* widget) {
  QDockWidget* dockWidget = new QDockWidget();
  dockWidget->setWidget(widget);
  return dockWidget;
}
