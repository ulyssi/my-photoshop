
#include "PictureManager.hh"
#include "UserInterface.hh"
#include "PictureButton.hh"
#include "PictureModifier.hh"
#include "math.h"
#include <iostream>


/** Constructeurs et destructeur */
PictureManager::PictureManager(UserInterface* userInterface) :
  TabPanel(userInterface){
  setTabName(QString("Thumbnail"));
  m_buttonGroup=new QButtonGroup();
  m_QWidget =new QWidget();
  m_layout= new QGridLayout();
  m_layout->setAlignment(Qt::AlignCenter);
  m_layout->setSpacing(10);
 
 
}

PictureManager::~PictureManager() {
}


/** Methodes */
Picture* PictureManager::getSelectedPicture() { return NULL;
}

void PictureManager::addPictureModifier(PictureModifier* pictureModifier) {
 
  PictureButton* t_pictureButton=new PictureButton(pictureModifier);
  m_listPictureButton.append(t_pictureButton);
  m_buttonGroup->addButton((QAbstractButton*)t_pictureButton);
  refresh();
}

void PictureManager::removePictureModifier(PictureModifier* picturemodifier){
}


void PictureManager::refresh() {
  if(m_listPictureButton.size()==1){
  int taille_fenetre =parentWidget()->size().width();
  int taille_fenetre2 =parentWidget()->size().height();
  m_nbCol=ceil(taille_fenetre/(128+10));
  m_QWidget->resize(taille_fenetre,taille_fenetre2);
  //std::cout<<(QWidget*)parentWidget()->size().width()<<std::endl;
  }
  if((m_QWidget->size()).height()<((m_listPictureButton.size()/m_nbCol))*128){
    int width=m_QWidget->size().width();
    int height=m_QWidget->height()+148+m_layout->spacing()*m_listPictureButton.size();
    m_QWidget->resize(width,height);
  }
  for (int j =0 ; j<m_listPictureButton.size();j++)
    m_layout->removeWidget((QPushButton*)m_listPictureButton.at(j));
  int i=0,k=0;
  for (int j =0 ; j<m_listPictureButton.size();j++){
    m_layout->addWidget((QPushButton*)m_listPictureButton.at(j),k,i);
    i++;
    if(i==m_nbCol){
      i=0;
      k++;
    }
  }
  m_QWidget->setLayout(m_layout);
  setWidget(m_QWidget);
}

void PictureManager::resizeEvent(QResizeEvent* event){
  int taille_fenetre =parentWidget()->size().width();
  int taille_fenetre2 =parentWidget()->size().height();
  m_nbCol=ceil(taille_fenetre/(128+10));
  m_QWidget->resize(taille_fenetre,taille_fenetre2);
  refresh();
  // std::cout<<"resize event"<<std::endl;
}
