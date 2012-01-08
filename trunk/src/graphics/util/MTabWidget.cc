#include <QPushButton>
#include <QWidget>
#include "MTabWidget.hh"
#include <iostream>

MTabWidget::MTabWidget ( QWidget * parent ){
  setParent(parent);
  QObject::connect(this,SIGNAL(currentChanged(int)),this,SLOT(myItemChangeSlot(int)));
  QTabBar *p_tabBar = tabBar();
  p_tabBar->setMovable(true);
  createAddTab();
}

MTabWidget::~MTabWidget (){

}
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
  removeTab(i);
  
  if (currentIndex()==i)
    if(i!=0)
      setCurrentIndex(i--);
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
  int i =insertTab(0,new QWidget(),"");
  tabBar()->setTabButton(0, QTabBar::LeftSide,((QWidget*)(m_pushButton)));
}
  
void MTabWidget::myItemChangeSlot(int index){
  this->tabBar()->setTabTextColor(index,Qt::blue);
  for(int i = 0;i<this->tabBar()->count();i++)
    {  
      if(i != index)	
	this->tabBar()->setTabTextColor(i,Qt::black);
    }
}

QPushButton* MTabWidget::createCloseButton(){
  QPushButton* t_icon =new QPushButton();
  t_icon->setIcon(QIcon::fromTheme("window-close"));
  t_icon->setFlat(true);
  t_icon->setFixedWidth(20);
  t_icon->setFixedHeight(20);
  return t_icon;
}

//connect(p_tabBar,SIGNAL(tabCloseRequested(int)),parent,SLOT(close(int))); 
