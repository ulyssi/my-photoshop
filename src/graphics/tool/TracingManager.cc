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
#include "PictureArea.hh"

/** Constructeurs et destructeur */
TracingManager::TracingManager(PictureModifier* pictureModifier) :
  m_pictureModifier(pictureModifier),
  m_lastIndex(0),
  m_tobeSet(0),
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
void TracingManager::paste(){
  ////std::cout<<"attempting to paste"<<std::endl;
  Picture * pic=m_pictureModifier->getPicture();
  QImage tmp= m_pictureModifier->getClipBoard()->image();
  
  Tracing * cTracing=new Tracing(tmp.width(),tmp.height(),20,20);
  for (int i = 0; i < cTracing->getWidth(); i++)
    for (int j = 0; j < cTracing->getHeight(); j++)
      cTracing->setValue(i, j, (unsigned int)tmp.pixel(i, j));
  pic->addTracing(cTracing);
  pic->refresh();
  m_pictureModifier->refresh();
}

void TracingManager::move(int x,int y){
  
  Tracing* cTracing;
  Picture * pic=m_pictureModifier->getPicture();
  std::vector<int>::iterator it=m_selected->begin();
  std::vector<Tracing*> tracings=pic->getTracingList();
  while(it<m_selected->end()){
    cTracing=tracings[(*it)];
    cTracing->setOffX(cTracing->getOffX()+x);
    cTracing->setOffY(cTracing->getOffY()+y);
    it++;
  }
  pic->normaliseOffs(tracings);
  (m_pictureModifier->getPicture())->refresh();
  m_pictureModifier->refreshData();
  (m_pictureModifier->getPictureArea())->refresh();
}

void TracingManager::refresh() {
  //std::cout<<"refreshing tracings "<<m_lastIndex <<std::endl;
  m_selected->clear();
  m_signalManagers->clear();
  if (m_pictureModifier != NULL) {
    Picture * cPicture=m_pictureModifier->getPicture();
    //std::cout<<"refreshing tracings tag1"<<std::endl;
    if(cPicture!=NULL){
      std::vector <Tracing *> list=cPicture->getTracingList();
      
      deleteHead();

       //std::cout<<"refreshing tracings tag2 "<<std::endl;
      int id;
      for(id=0;id<list.size();id++){
	buildLine(list[id],id);
      }
      m_lastIndex=id;
    }
    ////std::cout<<"refreshing tracings 3 "<<m_lastIndex <<std::endl;
    buildHead(m_lastIndex);
  }
  //std::cout<<"done refresh"<<std::endl;
}

/*the following methodes are used to build and connect the buttons of the manager*/


void TracingManager::paintEvent(QPaintEvent * /* event */)
{
 
}






void TracingManager::buildHead(int index){ 
  // std::cout<<"building head"<<std::endl;

    QLabel *tracing=new QLabel(tr("tracing"));
    QLabel *visible=new QLabel(tr("visible"));
    QLabel *selected=new QLabel(tr("selected"));
    QLabel *alpha=new QLabel(tr("alpha"));
    //Maybe Useless
    tracing->setContentsMargins( (const QMargins & )QMargins(1,1,1,1));
    m_grid->addWidget(tracing,index,0);
    m_grid->addWidget(visible,index,1);
    m_grid->addWidget(selected,index,2);
    m_grid->addWidget(alpha,index,3);
    //std::cout<<"done building head"<<std::endl;
   

}

void TracingManager::deleteHead(){
  //std::cout<<"deleting head"<<std::endl;
  
  for(int i=0;i<=m_lastIndex;i++)
    for(int j=0;j<4;j++){
      QWidget* widget = m_grid->itemAtPosition(i, j)->widget();
      widget->setEnabled(false);
      widget->setVisible(false);
      m_grid->removeItem(m_grid->itemAtPosition(i, j));
    }
  m_lastIndex=0;
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
  if(cTracing->isVisible())
    visible->setCheckState (Qt::Checked);
  QSpinBox*  alpha=new QSpinBox();
  if(cTracing->isSelected()){
    select->setCheckState (Qt::Checked);
    if(m_selected->empty())
      m_selected->reserve(1);
    m_selected->push_back(line);
  }


  alpha->setSuffix(QString("/255"));
  alpha->setMinimum(0);
  alpha->setMaximum(255);
  alpha->setSingleStep(3);
  alpha->setValue((int)(cTracing->getAlpha()*255.0+0.5));
  alpha->setEnabled(cTracing->isVisible());
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
  m_add=new QPushButton(tr(""));
  m_merge=new QPushButton(tr(""));
  m_up=new QPushButton(tr(""));
  m_down=new QPushButton(tr(""));
  m_remove=new QPushButton(tr(""));
  m_rename=new QPushButton(tr(""));
  m_add->setIcon((const QIcon &)QIcon("Icon/Add.png"));
  m_merge->setIcon((const QIcon &)QIcon("Icon/Merge.png"));
  m_up->setIcon((const QIcon &)QIcon("Icon/Up.png"));
  m_down->setIcon((const QIcon &)QIcon("Icon/Down.png"));
  m_remove->setIcon((const QIcon &)QIcon("Icon/Remove.png"));
  m_rename->setIcon((const QIcon &)QIcon("Icon/Rename.png"));
  m_foot->addWidget(m_add);
  m_foot->addWidget(m_remove);
  m_foot->addWidget(m_merge);
  m_foot->addWidget(m_down);
  m_foot->addWidget(m_up);
  m_foot->addWidget(m_rename);
  m_vLayout->addLayout(m_foot);
  
  connect(m_add, SIGNAL(clicked()), this, SLOT(add()));		   
  connect(m_merge, SIGNAL(clicked()), this, SLOT(merge()));		   
  connect(m_up, SIGNAL(clicked()), this, SLOT(up()));		     
  connect(m_down, SIGNAL(clicked()), this, SLOT(down()));		 
  connect(m_remove, SIGNAL(clicked()), this, SLOT(remove()));
  connect(m_rename,SIGNAL(clicked()),this,SLOT(rename()));
  
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
  if(it<m_selected->end())
    m_selected->erase(it);

}

bool TracingManager::isSelected(int id){
 
  std::vector<int>::iterator it;
  it=m_selected->begin();
 
  while(it<m_selected->end()&&id!=(*it)){
    it++;
  }
 
  return it<m_selected->end();
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
  Picture *pic= m_pictureModifier->getPicture();
  int prev=(pic->getTracingList()).size();
  std::vector<int>::reverse_iterator it=m_selected->rbegin();
  while(it<m_selected->rend()){
    if((*it)+1!=prev)
      pic->swapTracing((*it),(*it)+1);
    else
      prev=(*it);
    it++;
  }
  
  /*maj list selection*/
  prev=(pic->getTracingList()).size();
  for(int i=0;i<m_selected->size();i++){
    if(m_selected->at(i)+1!=prev)
      m_selected->at(i)++;
    else
      prev=m_selected->at(i);
  }
  
 
  pic->refresh();
  m_pictureModifier->refresh();
}


/************************************************/
/*shifts the list of selected tracings downwards*/
/************************************************/

void TracingManager::down(){
  Picture *pic= m_pictureModifier->getPicture();
  int prev =-1;
  std::vector<int>::iterator it=m_selected->begin();
  while(it<m_selected->end()){
    if((*it)-1!=prev)
      pic->swapTracing((*it),(*it)-1);
    else
      prev=(*it);
    it++;
  }
  for(int i=m_selected->size()-1;i>=0;i--){
    if(m_selected->at(i)-1!=prev)
      m_selected->at(i)--;
    else
      prev=m_selected->at(i);
  }
 
  pic->refresh();
  m_pictureModifier->refresh();
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
    int *offs=pic->getminOffs(toBeMerged);
     
    int offX=offs[0];
    int offY=offs[1];
    delete offs;
    pic->normaliseOffs(toBeMerged);
    std::vector<int>::reverse_iterator r_it=m_selected->rbegin();
    while(r_it<m_selected->rend()){
      pic->removeTracing((*r_it));
      r_it++;
    }
    
    pic->insertTracing(new Tracing(merged,offX,offY,1.0),rslt_id);
    delete mo;
    delete merged; 
    
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
    pic->normaliseOffs(pic->getTracingList());
    pic->refresh();
    m_pictureModifier->refresh();
  }
}

/********************************************************************/
/*replaces the labels asoociated with each selected tracing with a  */
/*Qline edit and adds it to the signal manager associated to that   */
/*tracing                                                           */
/********************************************************************/
void TracingManager::rename(){
  if(m_selected->size()!=0){
    for(int i=0;i<6;i++){
      (m_foot->itemAt(i))->widget()->setEnabled(false);
    
    
    }
    m_tobeSet=m_selected->size();
    //for(int i=0;) for() disable grid
    std::vector<int>::iterator it=m_selected->begin();
    while(it<m_selected->end()){
      QLineEdit *rename=new QLineEdit();
      QWidget* widget = m_grid->itemAtPosition((*it), 0)->widget();
      m_grid->removeItem(m_grid->itemAtPosition((*it), 0));
   
      delete m_grid->itemAtPosition((*it), 0);
      m_grid->addWidget(rename,(*it),0);
      delete widget;
    
    
      SignalManager*cSig= m_signalManagers->at((*it));
      //std::cout<<"renaming selected trancing "<<(*it) <<std::endl;
      connect(rename,SIGNAL(textEdited( QString)),cSig, SLOT(setName_tmp(QString)));
      connect(rename,SIGNAL(returnPressed()),cSig, SLOT(setName()));
      connect(cSig,SIGNAL(textSet(int)),this,SLOT(label_R(int)));
      it++;
    }
  
  
  }
  

}
/********************************************************************/
/*builds a Qlabel corresponding to the correct name of the tracing  */
/*                                                                  */
/********************************************************************/

void TracingManager::label_R(int id){
 
  //std::cout<<"label "<<id<<" set"<<std::endl;
  m_tobeSet--;
  Picture *pic=m_pictureModifier->getPicture();
  Tracing *cTracing=(pic->getTracingList())[id];
  //std::cout<<"label naming problem ??"<<std::endl;
  QLabel *rename=new QLabel(cTracing->getName());
  QWidget* widget = m_grid->itemAtPosition(id, 0)->widget();
  widget->setEnabled(false);
  widget->setVisible(false);
  //std::cout<<"widget removal problem ??"<<std::endl;
  m_grid->removeItem(m_grid->itemAtPosition(id, 0));
  //std::cout<<"delete1 problem ??"<<std::endl;
  //delete m_grid->itemAtPosition(id, 0);
  //std::cout<<"add problem ??"<<std::endl;
  
  m_grid->addWidget(rename,id,0);
  //std::cout<<"delete2 problem ??"<<std::endl;
  //delete widget;
  
  //std::cout<<"aparently not"<<std::endl;  
  if(m_tobeSet==0)
    for(int i=0;i<6;i++){
      (m_foot->itemAt(i))->widget()->setEnabled(true);
    } 
  //std::cout<<"aparently once more"<<std::endl; 
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
  m_pictureMod->refreshData();
  (m_pictureMod->getPictureArea())->refresh();
  
}

void SignalManager::setSelected(int i){
  if(i!=0){
    //std::cout<<"selected  "<<m_tracing->getIndex()<<std::endl;  
    m_tracing->setSelected(true);
    m_tracingManager->addSelected(m_tracing->getIndex());
  }
  else{
    //std::cout<<"unselected  "<<m_tracing->getIndex()<<std::endl;
    m_tracing->setSelected(false);
    m_tracingManager->removeSelected(m_tracing->getIndex());
  }
  
}

void SignalManager::setVisible(int i){
  if(i==0){
    m_prevV=m_tracing->getAlpha();
    m_tracing->setAlpha(0.0);
    m_tracing->setVisible(false);
    m_V=0.0;
  }
  else{
    m_tracing->setVisible(true);
    m_tracing->resetAlpha();
    m_V=1.0;
  }
  (m_pictureMod->getPicture())->refresh();
  m_pictureMod->refreshData();
  (m_pictureMod->getPictureArea())->refresh();
}

void SignalManager::setName_tmp(QString tmp){
  //std::cout<<"not so funny now is it222?"<<std::endl;
  m_name=QString(tmp);  
}

void SignalManager::setName(){
  //std::cout<<"finished editing"<<std::endl;
  m_tracing->setName(m_name);
  //std::cout<<m_name.isNull()<<std::endl;
  //std::cout<<"not so funny now is it?"<<std::endl;
  emit textSet(m_tracing->getIndex());
}



  


