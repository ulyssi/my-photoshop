#include <QPushButton>
#include <QWidget>
#include "MTabWidget.hh"
#include "MPushButton.hh"
#include <iostream>
#include <QListIterator>

MTabWidget::MTabWidget ( QWidget * parent ):
  m_listpushbutton(){
  setParent(parent);
  QObject::connect(this,SIGNAL(currentChanged(int)),this,SLOT(myItemChangeSlot(int)));
  createAddTab();
 
}

MTabWidget::~MTabWidget (){}

int MTabWidget::addTab ( QWidget * page, const QString & label ){
   int i = insertTab(count()-1,page,label);
   if (i!=0)
     tabBar()->setTabButton(i, QTabBar::RightSide,(QWidget*)createCloseButton());
   return i;
}

int MTabWidget::addTab ( QWidget * page, const QIcon & icon, const QString & label ){
  return insertTab(count()-1,page,icon,label);
}

void MTabWidget::fermerOnglet(int i){
  if (i!=1&&i!=count()){ 
    removeTab(i-1);
  } 
  for (int j = 0; j < m_listpushbutton.size(); ++j) {
    if (m_listpushbutton.at(j)->getIndex()>i&&m_listpushbutton.at(j)->getIndex()<=count())
      m_listpushbutton.at(j)->setIndex(m_listpushbutton.at(j)->getIndex()-1);
  }
}
QTabBar* MTabWidget::tabBar(){
  return QTabWidget::tabBar();
}

void MTabWidget::createAddTab(){
  QPushButton* m_pushButton = new QPushButton(); 
  m_pushButton->setFixedWidth(20);
  m_pushButton->setFixedHeight(20);
  m_pushButton->setIcon(QIcon::fromTheme("document-open"));
  m_pushButton->setFlat(true);
  insertTab(0,new QWidget(),"");
  tabBar()->setTabButton(0, QTabBar::LeftSide,((QWidget*)(m_pushButton)));
  QObject::connect(m_pushButton,SIGNAL(clicked()),parentWidget(),SLOT(open()));
}
  
void MTabWidget::myItemChangeSlot(int index){
  this->tabBar()->setTabTextColor(index,Qt::blue);
  for(int i = 0;i<this->tabBar()->count();i++){  
    if(i != index)	
      this->tabBar()->setTabTextColor(i,Qt::black);
  }
}

QPushButton* MTabWidget::createCloseButton(){
  MPushButton* t_icon =new MPushButton(count()-1);
  t_icon->setIcon(QIcon::fromTheme("window-close"));
  t_icon->setFlat(true);
  t_icon->setFixedWidth(20);
  t_icon->setFixedHeight(20);
  QObject::connect(t_icon,SIGNAL(clickedButton(int)),this,SLOT(fermerOnglet(int)));
  m_listpushbutton.append(t_icon);
  return (QPushButton*)t_icon;
}

