#include "MTabWidget.hh"


MTabWidget::MTabWidget ( QWidget * parent ){
  setParent(parent);
  QObject::connect(this,SIGNAL(currentChanged(int)),this,SLOT(myItemChangeSlot(int)));
}
MTabWidget::~MTabWidget (){

}

QTabBar* MTabWidget::tabBar(){
  return QTabWidget::tabBar();
}
  
void MTabWidget::myItemChangeSlot(int index)
{
  this->tabBar()->setTabTextColor(index,Qt::blue);
  for(int i = 0;i<this->tabBar()->count();i++)
    {  
      if(i != index)	
	this->tabBar()->setTabTextColor(i,Qt::black);
    }
}
