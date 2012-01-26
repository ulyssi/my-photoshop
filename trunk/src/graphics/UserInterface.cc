#include "UserInterface.hh"

#include "TabWidget.hh"
#include "Picture.hh"
#include "PictureManager.hh"



/** Constructeurs et Destructeurs */
UserInterface::UserInterface(QApplication* qapplication,QClipboard* clipboard) :
  m_QApplication(qapplication){ 
  m_clipboard = clipboard;
  createActions();
  m_pictureManager = new PictureManager(this);
  m_viewTabWidget = createTabWidget();
  createToolBoxDocks();
  createMenuBar();
  createToolBars();
  setCentralWidget((QTabWidget*)m_viewTabWidget);
  setWindowTitle(tr("MyPhotoShop"));
  resize(1024, 768);
  update();
  this->statusBar()->showMessage("ready");
  
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
  QObject::connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(resetEditionTool(int)));
  return tabWidget;
}
  
QDockWidget* UserInterface::createDockWidget(QWidget* widget) {
  QDockWidget* dockWidget = new QDockWidget(widget->accessibleName());
  dockWidget->setWidget(widget);
  return dockWidget;
}



void UserInterface::print(QString string){
  statusBar()->showMessage(string, 10000);
}
