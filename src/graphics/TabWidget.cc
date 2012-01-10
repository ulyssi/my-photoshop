#include "TabWidget.hh"

#include <QTabBar>
#include <QListIterator>

#include "TabPanel.hh"
#include "MPushButton.hh"

#include "Picture.hh"
#include "PictureManager.hh"
#include "UserInterface.hh"


/** Constructeurs et destructeur */
TabWidget::TabWidget(UserInterface* userInterface) :
  QTabWidget(userInterface),
  m_userInterface(userInterface)
{
  insertTab(0, new QWidget(), "Open");
  tabBar()->setTabButton(0, QTabBar::LeftSide, (QWidget*)createNewTabButton());

  QObject::connect(this, SIGNAL(currentChanged(int)), this, SLOT(selectTab(int)));
}

TabWidget::~TabWidget() {}


/** Accesseurs */
TabPanel* TabWidget::getTabPanel() { return (TabPanel*)widget(currentIndex()); }


/** Methodes */
int TabWidget::addTab(TabPanel* tabPanel) {
  int index = insertTab(count()-1, tabPanel, tabPanel->getTabName());
  if (index == 0) setCurrentIndex(index);
  else tabBar()->setTabButton(index, QTabBar::RightSide, (QWidget*)createCloseButton());
  return index;
}


/** Slots */
void TabWidget::selectTab(int index) {
  if (0 < index && index >= tabBar()->count()-1) {
    setCurrentIndex(index-1);
    m_userInterface->open();
  }
  this->tabBar()->setTabTextColor(index, Qt::blue);
  for(int i = 0; i < tabBar()->count(); i++) 
    if (i != index)	tabBar()->setTabTextColor(i, Qt::black);
}

void TabWidget::closeTab(int index) {
  if (index != 1 && index != count()) { 
    removeTab(index-1);
    m_userInterface->close(widget(index-1));
  }
  for (int j = 0; j < m_listpushbutton.size(); j++)
    if (m_listpushbutton.at(j)->getIndex() > index && m_listpushbutton.at(j)->getIndex() <= count())
      m_listpushbutton.at(j)->setIndex(m_listpushbutton.at(j)->getIndex() - 1);
}


/** Methodes internes */
QPushButton* TabWidget::createNewTabButton() {
  QPushButton* newTabButton = new QPushButton(); 
  newTabButton->setFixedWidth(16);
  newTabButton->setFixedHeight(16);
  newTabButton->setIcon(QIcon::fromTheme("window-new"));
  newTabButton->setFlat(true);
  
  QObject::connect(newTabButton, SIGNAL(clicked()), m_userInterface, SLOT(open()));
  return newTabButton;
}

QPushButton* TabWidget::createCloseButton() {
  MPushButton* t_icon = new MPushButton(count()-1);
  t_icon->setIcon(QIcon::fromTheme("window-close"));
  t_icon->setFlat(true);
  t_icon->setFixedWidth(16);
  t_icon->setFixedHeight(16);

  QObject::connect(t_icon, SIGNAL(clickedButton(int)), this, SLOT(closeTab(int)));
  m_listpushbutton.append(t_icon);
  return (QPushButton*)t_icon;
}


  


