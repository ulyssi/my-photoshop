#include "PictureManager.hh"
#include "UserInterface.hh"
#include "PictureButton.hh"
#include "PictureModifier.hh"
#include "Picture.hh"
#include "math.h"
#include <iostream>
/** Constructeurs et destructeur */


PictureManager::PictureManager(UserInterface* userInterface) :
  TabPanel(userInterface){
  setTabName(QString("Thumbnail"));
  m_buttonGroup=new QButtonGroup();
  m_buttonGroup->setExclusive(false);
  m_QWidget =new QWidget();
  m_layout= new QGridLayout();
  m_layout->setAlignment(Qt::AlignCenter);
  m_layout->setSpacing(10);
  m_QWidget->setLayout(m_layout);
  setWidget(m_QWidget);
}

PictureManager::~PictureManager() {
}
/** Methodes */
Picture* PictureManager::getSelectedPicture() { 
  return ((PictureButton *)m_buttonGroup->buttons().first())->getPicture();
}

void PictureManager::addPictureModifier(PictureModifier* pictureModifier) {
  PictureButton* t_pictureButton=new PictureButton(pictureModifier);
  m_buttonGroup->addButton((QAbstractButton*)t_pictureButton);
  refresh();
}

void PictureManager::removePictureModifier(PictureModifier* picturemodifier){ 
  int r;
  for (int i =0 ; i<m_buttonGroup->buttons().size();i++){
    if(((PictureButton*)m_buttonGroup->buttons().at(i))->getPicture()==picturemodifier->getPicture()){
      r=i;
    }
  }
  m_layout->removeWidget(m_buttonGroup->buttons().at(r));
  m_buttonGroup->buttons().at(r)->hide();
  m_QWidget->repaint(0,0,-1,-1);
  m_buttonGroup->removeButton(m_buttonGroup->buttons().at(r));
  refresh();
}


void PictureManager::refresh() {
  if (parentWidget()!=NULL&&m_buttonGroup->buttons().size()!=0){
    int t_width =parentWidget()->size().width();
    QSize* b_size =((PictureButton*)m_buttonGroup->buttons().first())->geticonSize();
    m_nbCol=floor((t_width-m_layout->spacing())/(b_size->width()+m_layout->spacing())+0.5);    
    m_nbLig=ceil(float(m_buttonGroup->buttons().size())/float(m_nbCol));
    if (m_nbCol<=1) m_nbCol=2;
    if (m_nbLig<=1) m_nbLig=2;
    m_QWidget->resize(t_width-20,m_nbLig*b_size->height()+m_layout->spacing()*(m_nbLig*2));
    for (int i =0 ; i<m_buttonGroup->buttons().size();i++)
      m_layout->removeWidget((QPushButton*)m_buttonGroup->buttons().at(i));
    int l=0,c=0;
    for (int i  =0 ; i<m_buttonGroup->buttons().size();i++){
      m_layout->addWidget((QPushButton*)m_buttonGroup->buttons().at(i),l,c);
      c++;
      if(c==m_nbCol){
	c=0;
     	l++;
      }
    }
   
   
  }
  
}

/** Override public method from QWidget **/
void PictureManager::resizeEvent(QResizeEvent* event){
  
  refresh();
}
