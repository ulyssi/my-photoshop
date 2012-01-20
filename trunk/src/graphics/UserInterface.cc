#include "UserInterface.hh"

#include "TabWidget.hh"
#include "Picture.hh"
#include "PictureManager.hh"



/** Constructeurs et Destructeurs */
UserInterface::UserInterface(QApplication* qapplication,QClipboard* clipboard) :
  m_QApplication(qapplication)
{ m_clipboard = clipboard;
  
  m_pictureManager = new PictureManager(this);
  m_viewTabWidget = createTabWidget();
  createActions();
  createMenuBar();
  createToolBars();
  createToolBoxDocks();
  setCentralWidget((QTabWidget*)m_viewTabWidget);
  setWindowTitle(tr("MyPhotoShop"));
  resize(1024, 768);
  update();
}
    
UserInterface::~UserInterface() {
  delete m_pictureManager;
}


/** Methodes */
void UserInterface::update() {
  updateActions();
  updateToolBoxDocks();
}


/** Methodes internes */
TabWidget* UserInterface::createTabWidget() {
  TabWidget* tabWidget = new TabWidget(this);
  tabWidget->addTab((TabPanel*)m_pictureManager);
  return tabWidget;
}
  
QDockWidget* UserInterface::createDockWidget(QWidget* widget) {
  QDockWidget* dockWidget = new QDockWidget(widget->accessibleName());
  dockWidget->setWidget(widget);
  return dockWidget;
}
