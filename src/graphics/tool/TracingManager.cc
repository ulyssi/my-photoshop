#include "TracingManager.hh"
#include <QString>
#include "PictureModifier.hh"
#include "MergeOperation.hh"
#include <iostream>
#include <vector>
#include <QFileDialog>
#include "Tracing.hh"
#include "Picture.hh"


/** Constructeurs et destructeur */
TracingManager::TracingManager(PictureModifier* pictureModifier) :
  m_pictureModifier(pictureModifier),
  m_lastIndex(0)
{
  setAccessibleName(tr("Tracing"));
  m_vLayout=new QVBoxLayout();
  buildFoot();
  buildHead(); 
  m_vLayout->addWidget(m_header);
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

  if (m_pictureModifier != NULL) {
    Picture * cPicture=m_pictureModifier->getPicture();
    if(cPicture!=NULL){
      std::vector <Tracing *> list=cPicture->getTracingList();
      int id;
      for(id=m_lastIndex;id<list.size();id++){
	buildLine(list[id]);
      }
      m_lastIndex=id;
    }
  }
}

/*the following methodes are used to build and connect the buttons of the manager*/
void TracingManager::buildHead(){}


void TracingManager::buildLine(Tracing *cTracing){

  SignalManager *sm=new SignalManager(cTracing,m_pictureModifier,this);
  QHBoxLayout* line =new QHBoxLayout();
  int num=cTracing->getIndex();
  QLabel * label=new QLabel((QString("Tracing")+QString(QString::number(num))));
  QCheckBox * select=new QCheckBox(QString(""));
  QCheckBox * visible=new QCheckBox(QString(""));
  visible->setCheckState (Qt::Checked);
  QSpinBox*  alpha=new QSpinBox();
 
  initSpin(alpha);
  line->addWidget(label);
  line->addWidget(visible);
  line->addWidget(select);
  line->addWidget(alpha);
  m_vLayout->addLayout(line);
  connect(alpha,SIGNAL(valueChanged ( int)),sm, SLOT(setAlpha(int))); 
  connect(visible,SIGNAL(stateChanged ( int)),sm, SLOT(setVisible(int))); 
  connect(select,SIGNAL(stateChanged ( int)),sm, SLOT(setSelected(int))); 
  
}

void TracingManager::buildFoot(){
  m_foot=new QHBoxLayout();
  QPushButton* add=new QPushButton(tr("+"));
  QPushButton* merge=new QPushButton(tr("merge"));
  QPushButton* up=new QPushButton(tr("^"));
  QPushButton* down=new QPushButton(tr("v"));
  
  m_foot->addWidget(add);
  m_foot->addWidget(merge);
  m_foot->addWidget(up);
  m_foot->addWidget(down);

  m_vLayout->addLayout(m_foot);
  
  connect(add, SIGNAL(clicked()), this, SLOT(add()));				   
  connect(merge, SIGNAL(clicked()), this, SLOT(merge()));				   
  connect(up, SIGNAL(clicked()), this, SLOT(up()));				   
  connect(down, SIGNAL(clicked()), this, SLOT(down()));				   
}


void TracingManager::initSpin(QSpinBox *al){
  
  al->setSuffix(QString("/255"));
  al->setMinimum(0);
  al->setMaximum(255);
  al->setSingleStep(3);
  al->setValue(255);
  
}

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
    Tracing * cTracing=new Tracing(tmp.width(),tmp.height(),0,0);
    for (int i = 0; i < cTracing->getWidth(); i++)
      for (int j = 0; j < cTracing->getHeight(); j++)
	cTracing->setValue(i, j, (unsigned int)tmp.pixel(i, j));
    pic->addTracing(cTracing);
  }
  refresh();
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
  /*  if(!m_selected->empty){
    Picture pic;
    vector<Tracing *> toBeMerged;
    toBeMerged.reserve(m_selected->size());
    while(it<m_selected->end()){
      toBeMerged.push_back(m_tracingList[m_selected[i]]);
    }
    MergeOperation* mo=new MergeOperation();
    Tracing *Tr= mo->doOperation(toBeMerged);
    
    }*/
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
  m_pictureMod->getPicture()->refresh();
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
  m_pictureMod->getPicture()->refresh();
  m_pictureMod->refresh();
}





  


