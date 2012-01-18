#include "TracingManager.hh"
#include <QString>
#include "PictureModifier.hh"
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
  
  m_header=new QLabel(QString("Tracing        |       visible         |      ancre  "));    
  m_vLayout=new QVBoxLayout();
  m_vLayout->addWidget(m_header);
  setLayout(m_vLayout);
  m_foot=new QPushButton(tr("+"));
  connect(m_foot, SIGNAL(clicked()), this, SLOT(openTracing()));
  m_vLayout->addWidget(m_foot);
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
void TracingManager::openTracing(){
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

void TracingManager::refresh() {
  std::cout<<"refreshing tracing "<<std::endl;
  if (m_pictureModifier != NULL) {
    Picture * cPicture=m_pictureModifier->getPicture();
    if(cPicture!=NULL){
      std::vector <Tracing *> list=cPicture->getTracingList();
      QHBoxLayout *line;
      QLabel *label;
      QCheckBox *ancre;
      QCheckBox *visible;
      QSpinBox *alpha;
      int id;
      SignalManager *sm;
      for(id=m_lastIndex;id<list.size();id++){
	sm=new SignalManager(list[id],m_pictureModifier);
	line =new QHBoxLayout();
	int num=list[id]->getIndex();
	label=new QLabel((QString("Tracing")+QString(QString::number(num))));
	ancre=new QCheckBox(QString(""));
	visible=new QCheckBox(QString(""));
	alpha=new QSpinBox();
	initSpin(alpha);
	line->addWidget(label);
	line->addWidget(visible);
	line->addWidget(ancre);
	line->addWidget(alpha);
	
	m_vLayout->addLayout(line);
       
	connect(alpha,SIGNAL(valueChanged(int)),sm, SLOT(setAlpha(int))); 
      }
      m_lastIndex=id;
      
    }
  }
  
  std::cout<<"done refreshing"<<std::endl;
}



void TracingManager::initSpin(QSpinBox *al){
  
  al->setSuffix(QString("/255"));
  al->setMinimum(0);
  al->setMaximum(255);
  al->setSingleStep(3);
  al->setValue(255);
  
}

SignalManager::SignalManager(Tracing *cTracing,PictureModifier *pictureMod){
  m_tracing=cTracing;
  m_pictureMod=pictureMod;
}

SignalManager::~SignalManager(){

}
void SignalManager::setAlpha(int i){
  std::cout<< "aww yyeeeaaaahhhh   "<< i<<std::endl;
  m_tracing->setAlpha(double(i)/255.0);
  m_pictureMod->getPicture()->refresh();
  m_pictureMod->refresh();

}


