#include "MTabWidget.hh"

MTabWidget::MTabWidget ( QWidget * parent ){
  setParent(parent);
  QObject::connect(this,SIGNAL(currentChanged(int)),this,SLOT(myItemChangeSlot(int)));
  QTabBar *p_tabBar = tabBar();
  p_tabBar->setMovable(true);
  p_tabBar->setTabsClosable(true);
  connect(p_tabBar,SIGNAL(tabCloseRequested(int)),parent,SLOT(close(int))); 
}

MTabWidget::~MTabWidget (){
  
}


QTabBar* MTabWidget::tabBar(){
  return QTabWidget::tabBar();
}
  
void MTabWidget::myItemChangeSlot(int index){
  this->tabBar()->setTabTextColor(index,Qt::blue);
  for(int i = 0;i<this->tabBar()->count();i++)
    {  
      if(i != index)	
	this->tabBar()->setTabTextColor(i,Qt::black);
    }
}

void MTabWidget::fermerOnglet(int i){
  removeTab(i);
  
  if (currentIndex()==i)
    if(i!=0)
      setCurrentIndex(i--);
}
