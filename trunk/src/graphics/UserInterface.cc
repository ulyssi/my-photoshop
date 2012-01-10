#include "UserInterface.hh"

#include "TabWidget.hh"
#include "ToolMaker.hh"
#include "Picture.hh"
#include "PictureManager.hh"



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
  /*addDockWidget(Qt::LeftDockWidgetArea, createDockWidget((QWidget*)(m_toolMaker->getDefaultHistogramModifier())));
  */addDockWidget(Qt::LeftDockWidgetArea, createDockWidget((QWidget*)(m_toolMaker->getDefaultOperationChooser())));

  setCentralWidget((QTabWidget*)m_viewTabWidget);
  setWindowTitle(tr("MyPhotoShop"));
  resize(1024, 768);

  updateActions();
}
    
UserInterface::~UserInterface() {
  delete m_pictureManager;
}


/** Methodes internes */
TabWidget* UserInterface::createTabWidget() {
  TabWidget* tabWidget = new TabWidget(this);
  // tabWidget->addTab((QWidget*)m_pictureManager,m_pictureManager->getTabName());
  tabWidget->addTab((TabPanel*)m_pictureManager);
  return tabWidget;
}
  
QDockWidget* UserInterface::createDockWidget(QWidget* widget) {
  QDockWidget* dockWidget = new QDockWidget();
  dockWidget->setWidget(widget);
  return dockWidget;
}
