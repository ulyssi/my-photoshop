#include "TracingManager.hh"
#include <QString>
#include "PictureModifier.hh"
#include "MergeOperation.hh"
#include <iostream>
#include <vector>
#include <QFileDialog>
#include <QLineEdit>
#include "Tracing.hh"
#include "Picture.hh"


/** Constructeurs et destructeur */
TracingManager::TracingManager(PictureModifier* pictureModifier) :
  m_pictureModifier(pictureModifier),
  m_lastIndex(0),
  m_indexOfHead(-1)
{
  setAccessibleName(tr("Tracing"));
  m_vLayout=new QVBoxLayout();
  m_grid=new QGridLayout();
  m_signalManagers=new std::vector<SignalManager *>();

  buildButtons(); 
  buildHead(0); 
  m_grid->setOriginCorner(Qt::BottomLeftCorner); 
  m_vLayout->addLayout((QLayout *)m_grid);
  setLayout(m_vLayout);
  m_selected=new std::vector<int>();
  
}

TracingManager::~TracingManager() {}


/** Mutateurs */
void TracingManager::setPictureModifier(PictureModifier* pictureModifier) {
  m_pictureModifier = pictureModifier; 
  refresh();
}


/** Predicats */
bool TracingManager::isEnabled() { return m_pictureModifier != NULL; }


/** Methodes */


void TracingManager::refresh() {
  std::cout<<"refreshing tracings 0 "<<m_lastIndex <<std::endl;
 
  if (m_pictureModifier != NULL) {
    Picture * cPicture=m_pictureModifier->getPicture();
    if(cPicture!=NULL){
      std::vector <Tracing *> list=cPicture->getTracingList();
      deleteHead();

      std::cout<<"refreshing tracings 2 "<<std::endl;
      int id;
      for(id=m_lastIndex;id<list.size();id++){
	buildLine(list[id],id);
      }
      m_lastIndex=id;
     
    }
    std::cout<<"refreshing tracings 3 "<<m_lastIndex <<std::endl;
    buildHead(m_lastIndex);
    
    
  }
}

/*the following methodes are used to build and connect the buttons of the manager*/
void TracingManager::buildHead(int index){ 
  std::cout<<"building head"<<std::endl;
  if(m_indexOfHead==-1){
    QLabel *tracing=new QLabel(tr("tracing"));
    QLabel *visible=new QLabel(tr("visible"));
    QLabel *selected=new QLabel(tr("selected"));
    QLabel *alpha=new QLabel(tr("alpha"));
  
    m_grid->addWidget(tracing,index,0);
    m_grid->addWidget(visible,index,1);
    m_grid->addWidget(selected,index,2);
    m_grid->addWidget(alpha,index,3);
    std::cout<<"done building head"<<std::endl;
    m_indexOfHead=index;
  }
}

void TracingManager::deleteHead(){
  if(m_indexOfHead!=-1){
    if(m_lastIndex<m_signalManagers->size())
      m_signalManagers->erase(m_signalManagers->begin()+m_lastIndex,m_signalManagers->end());
    for(int i=m_lastIndex;i<=m_indexOfHead;i++)
    for(int j=0;j<4;j++){
      QWidget* widget = m_grid->itemAtPosition(i, j)->widget();
      m_grid->removeItem(m_grid->itemAtPosition(i, j));
      delete m_grid->itemAtPosition(i, j);
      delete widget;
    }
    m_indexOfHead=-1;
  }
}

void TracingManager::buildLine(Tracing *cTracing,int line){

  SignalManager *sm=new SignalManager(cTracing,m_pictureModifier,this);
  if(m_signalManagers->size()==0)
    m_signalManagers->reserve(1);
  m_signalManagers->push_back(sm);
  int num=cTracing->getIndex();
  QLabel * label;
  if(cTracing->getName()==NULL)
    label=new QLabel((QString("Tracing")+QString(QString::number(num))));
  else
    label=new QLabel(cTracing->getName());
  QCheckBox * select=new QCheckBox(QString(""));
  QCheckBox * visible=new QCheckBox(QString(""));
  visible->setCheckState (Qt::Checked);
  QSpinBox*  alpha=new QSpinBox();
  
  initSpin(alpha);
  m_grid->addWidget(label,line,0);
  m_grid->addWidget(visible,line,1);
  m_grid->addWidget(select,line,2);
  m_grid->addWidget(alpha,line,3);
  
  connect(alpha,SIGNAL(valueChanged ( int)),sm, SLOT(setAlpha(int))); 
  connect(visible,SIGNAL(stateChanged ( int)),sm, SLOT(setVisible(int))); 
  connect(select,SIGNAL(stateChanged ( int)),sm, SLOT(setSelected(int))); 
  
}

void TracingManager::buildButtons(){
  m_foot=new QHBoxLayout();
  QPushButton* add=new QPushButton(tr("add"));
  QPushButton* merge=new QPushButton(tr("merge"));
  QPushButton* up=new QPushButton(tr("down"));
  QPushButton* down=new QPushButton(tr("up"));
  QPushButton* remove=new QPushButton(tr("remove"));
  QPushButton* rename=new QPushButton(tr("rename"));
  m_foot->addWidget(add);
  m_foot->addWidget(remove);
  m_foot->addWidget(merge);
  m_foot->addWidget(down);
  m_foot->addWidget(up);
  m_foot->addWidget(rename);
  m_vLayout->addLayout(m_foot);
  
  connect(add, SIGNAL(clicked()), this, SLOT(add()));		   
  connect(merge, SIGNAL(clicked()), this, SLOT(merge()));		   
  connect(up, SIGNAL(clicked()), this, SLOT(up()));		     
  connect(down, SIGNAL(clicked()), this, SLOT(down()));		 
  connect(remove, SIGNAL(clicked()), this, SLOT(remove()));
  connect(rename,SIGNAL(clicked()),this,SLOT(rename()));
  
}


void TracingManager::initSpin(QSpinBox *al){
  
  al->setSuffix(QString("/255"));
  al->setMinimum(0);
  al->setMaximum(255);
  al->setSingleStep(3);
  al->setValue(255);
  
}


/**the following methodes are used to manage the selected tracings*/
void TracingManager::addSelected(int i){
  std::vector<int>::iterator it;
  if(!m_selected->empty()){
    
    it=m_selected->begin();
    while(i>(*it)&&it<m_selected->end()){
      it++;
    }
    if(it<m_selected->end())
      m_selected->insert(it,i);
    else
      m_selected->push_back(i);
  }
  else{
    m_selected->reserve(1);
    m_selected->push_back(i);
  }
}

void TracingManager::removeSelected(int i){
  std::vector<int>::iterator it;
  it=m_selected->begin();
  while(i!=(*it)&&it<m_selected->end()){
    it++;
  }
  m_selected->erase(it);

}



/** Methode SLOT*/

/****************************************************/
/*opens and add an image to tracing list of picture */
/****************************************************/
void TracingManager::add(){
  QFileDialog *t_fileDialog = new QFileDialog(this, windowFlags());
  t_fileDialog->setViewMode(QFileDialog::List);
  t_fileDialog->setNameFilter(tr("Images Files(*.jpg *.png *.pnn *.jpeg);; All Files (*)"));
  t_fileDialog->setFileMode(QFileDialog::ExistingFiles);
  
  QStringList fileNames;
  if (t_fileDialog->exec()) fileNames = t_fileDialog->selectedFiles();
  t_fileDialog->setNameFilterDetailsVisible(true);
  QListIterator <QString> t_listIterator (fileNames);
  Picture * pic=m_pictureModifier->getPicture();
  while (t_listIterator.hasNext()){
    QImage tmp=QImage(t_listIterator.next()); 
    Tracing * cTracing=new Tracing(tmp.width(),tmp.height(),20,20);
    for (int i = 0; i < cTracing->getWidth(); i++)
      for (int j = 0; j < cTracing->getHeight(); j++)
	cTracing->setValue(i, j, (unsigned int)tmp.pixel(i, j));
    pic->addTracing(cTracing);
  }
  pic->refresh();
  m_pictureModifier->refresh();
  
  
}

/**********************************************/
/*shifts the list of selected tracings upwards*/
/**********************************************/

void TracingManager::up(){
  std::cout<<"up is as yet unimplemented"<<std::endl;
}


/************************************************/
/*shifts the list of selected tracings downwards*/
/************************************************/

void TracingManager::down(){
  std::cout<<"down is as yet unimplemented"<<std::endl;
}

/************************************************************/
/*merges the list of selected tracings into a single tracing*/
/************************************************************/

void TracingManager::merge(){
  if(m_selected->size()>1){
    Picture * pic=m_pictureModifier->getPicture();
    std::vector<int>::iterator it;
    std::vector<Tracing*> tracings=pic->getTracingList();
    std::vector<Tracing*> toBeMerged=std::vector<Tracing*>();
    toBeMerged.reserve(m_selected->size());
    for(it=m_selected->begin();it< m_selected->end();it++){
      toBeMerged.push_back(tracings[*it]);
    }
    MergeOperation * mo=new MergeOperation();
    Matrix<unsigned int> *merged=mo->doOperation(toBeMerged);
    int rslt_id=m_selected->at(0);
    int *offs=getminOffs(toBeMerged);
     
    int offX=offs[0];
    int offY=offs[1];
    delete offs;
    normaliseOffs(toBeMerged);
    std::vector<int>::reverse_iterator r_it=m_selected->rbegin();
    while(r_it<m_selected->rend()){
      pic->removeTracing((*r_it));
      r_it++;
    }
    
    pic->insertTracing(new Tracing(merged,offX,offY,1.0),rslt_id);
    delete mo;
    delete merged; 
    m_lastIndex=rslt_id; 
    m_selected->clear();
    pic->refresh();
    m_pictureModifier->refresh();
  }
}
/********************************************************************/
/*remove the list of selected tracings from the list of all tracings*/
/********************************************************************/
void TracingManager::remove(){
  
   Picture * pic=m_pictureModifier->getPicture();
   std::vector<int>::reverse_iterator it=m_selected->rbegin();
   if((pic->getTracingList()).size()>m_selected->size()){
     while(it<m_selected->rend()){
       pic->removeTracing(*it);
       it++;
     }
     
     m_selected->clear();
     m_lastIndex=0;
     pic->refresh();
     m_pictureModifier->refresh();
     normaliseOffs(pic->getTracingList());
     std::cout<<"error?5"<<std::endl;
   }
}

/********************************************************************/
/*replaces the labels asoociated with each selected tracing with a  */
/*Qline edit and adds it to the signal manager associated to that   */
/*tracing                                                           */
/********************************************************************/
void TracingManager::rename(){
  for(int i=0;i<5;i++){
    (m_foot->itemAt(i))->widget()->setEnabled(false);
  }

}
/********************************************************************/
/*builds a Qlabel corresponding to the correct name of the tracing  */
/*                                                                  */
/********************************************************************/

void TracingManager::label_R(int id){
  std::cout<<id;
  
  
}


void TracingManager::normaliseOffs(std::vector<Tracing*> tracing){
  int* offs=getminOffs(tracing);
  int offX=offs[0];
  int offY=offs[1];
  delete offs;
  std::vector<Tracing*>::iterator it;
  for(it=tracing.begin();it<tracing.end();it++){
    (*it)->setOffX((*it)->getOffX()-offX);
    (*it)->setOffY((*it)->getOffY()-offY);
  }
  
}
int * TracingManager::getminOffs(std::vector<Tracing*> tracing){
  int *rslt=new int[2];
  rslt[0]=0;
  rslt[1]=0;
  std::vector<Tracing*>::iterator it;
  for(it=tracing.begin();it<tracing.end();it++){
    if(rslt[0]<(*it)->getOffX())
      rslt[0]=(*it)->getOffX();
    if(rslt[1]<(*it)->getOffY())
      rslt[1]=(*it)->getOffY();
    
  }
  return rslt;
}



/**Signal Manager class implementation*/


SignalManager::SignalManager(Tracing *cTracing,PictureModifier *pictureMod,TracingManager * tracingManager){
  m_tracingManager=tracingManager;
  m_tracing=cTracing;
  m_pictureMod=pictureMod;
  m_V=1.0;
  m_prevV=1.0;
}

SignalManager::~SignalManager(){

}

/**SLOT */
void SignalManager::setAlpha(int i){

  m_tracing->setAlpha((m_V*double(i))/255.0);
  (m_pictureMod->getPicture())->refresh();
  m_pictureMod->refresh();

}

void SignalManager::setSelected(int i){
  if(i!=0){
    std::cout<<"selected  "<<m_tracing->getIndex()<<std::endl;   
 m_tracingManager->addSelected(m_tracing->getIndex());
  }
  else{
    std::cout<<"unselected  "<<m_tracing->getIndex()<<std::endl;
    m_tracingManager->removeSelected(m_tracing->getIndex());
  }
  
}

void SignalManager::setVisible(int i){
  if(i==0){
    m_prevV=m_tracing->getAlpha();
    m_tracing->setAlpha(0.0);
    m_V=0.0;
  }
  else{
    m_tracing->setAlpha(m_prevV);
    m_V=1.0;
  }
  (m_pictureMod->getPicture())->refresh();
  m_pictureMod->refresh();
}

void SignalManager::setName_tmp(QString tmp){
  m_name=QString(tmp);  
}

void SignalManager::setName(){
  emit textSet(m_tracing->getIndex());
}


  


