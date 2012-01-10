
#include "PictureManager.hh"
#include "UserInterface.hh"
#include "PictureButton.hh"
#include "PictureModifier.hh"
#include <iostream>

/** Constructeurs et destructeur */
PictureManager::PictureManager(UserInterface* userInterface) :
  TabPanel(userInterface){
  setTabName(QString("Thumbnail"));
  m_buttonGroup=new QButtonGroup();
  m_QWidget =new QWidget();
  m_layout= new QGridLayout();
  m_QWidget->resize(800,800);
  m_nbCol=4;
  
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
  for (int j =0 ; j<m_listPictureButton.size();j++)
    m_layout->removeWidget((QPushButton*)m_listPictureButton.at(j));
  for (int j =0 ; j<m_listPictureButton.size();j++){
    m_layout->addWidget((QPushButton*)m_listPictureButton.at(j),j,j);
  }
  m_QWidget->setLayout(m_layout);
  setWidget(m_QWidget);
}


