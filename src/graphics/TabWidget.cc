#include "TabWidget.hh"
#include <QTabBar>
#include <QListIterator>
#include "TabPanel.hh"
#include "util/MPushButton.hh"
#include "../model/Picture.hh"
#include "picture/PictureManager.hh"
#include "UserInterface.hh"



/** Constructeurs et destructeur */
TabWidget::TabWidget(UserInterface* userInterface) :
  QTabWidget(userInterface),
  m_userInterface(userInterface)
{
  insertTab(0, new QWidget(), "");
  tabBar()->setTabButton(0, QTabBar::RightSide, (QWidget*)createNewTabButton());
  QObject::connect(this, SIGNAL(currentChanged(int)), this, SLOT(selectTab(int)));
}

TabWidget::~TabWidget() {}


/** Accesseurs */
TabPanel* TabWidget::getTabPanel() {
  m_mutex.lock();
  QWidget* t_widget=widget(currentIndex());
  m_mutex.unlock();
  return (TabPanel*)t_widget;
}


/** Methodes */
int TabWidget::addTab(TabPanel* tabPanel) {
  int index = insertTab(count()-1, tabPanel, tabPanel->getTabName());
  if (index == 0){
    setCurrentIndex(index);
  }
  else tabBar()->setTabButton(index, QTabBar::RightSide, (QWidget*)createCloseButton());

  return index;
}


/** Slots */
void TabWidget::selectTab(int index) {
  if (index > 0  && index >= tabBar()->count()-1)
    setCurrentIndex(index-1);
  else {
    this->tabBar()->setTabTextColor(index, Qt::blue);
    for(int i = 0; i < tabBar()->count(); i++)
      if (i != index)
        tabBar()->setTabTextColor(i, Qt::black);
  }
  if (tabBar()->count() > 2) { getTabPanel()->notifyCurrent(); }
}

void TabWidget::closeTab(int index) {
  int t_index=0;
  int r=-1;
  m_mutex.lock();
  for (int j = 0; j < m_listpushbutton.size(); j++){
    t_index=m_listpushbutton.at(j)->getIndex();
    if (t_index > index ){
      m_listpushbutton.at(j)->setIndex(t_index-1);
    }
    if(t_index==index)
      r=j;
  }
  if (r!=-1) m_listpushbutton.removeAt(r);
  m_mutex.unlock();
  if (index != 0 && index != count()) {
    m_userInterface->close(widget(index-1));
    removeTab(index-1);
    setCurrentIndex(0);
  }
}


/** Methodes internes */
QPushButton* TabWidget::createNewTabButton() {
  QPushButton* newTabButton = new QPushButton();
  newTabButton->setFixedWidth(16);
  newTabButton->setFixedHeight(16);
  newTabButton->setIcon(QIcon("Icon/Open.png"));
  newTabButton->setFlat(true);
  QObject::connect(newTabButton, SIGNAL(clicked()), m_userInterface, SLOT(open()));
  return newTabButton;
}

QPushButton* TabWidget::createCloseButton() {
  m_mutex.lock();
  MPushButton* t_icon = new MPushButton(count()-1);
  t_icon->setIcon(QIcon("Icon/CloseTab.png"));
  t_icon->setFlat(true);
  t_icon->setFixedWidth(16);
  t_icon->setFixedHeight(16);
  QObject::connect(t_icon, SIGNAL(clickedButton(int)), this, SLOT(closeTab(int)));
  m_listpushbutton.append(t_icon);
  m_mutex.unlock();
  return (QPushButton*)t_icon;
}
