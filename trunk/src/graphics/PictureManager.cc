#include "PictureManager.hh"

PictureManager::PictureManager(UserInterface*)
m_userInterface(UserInterface)
{
  m_listPictureButton = new QList();  
}

PictureManager::~PictureManager() {
  delete m_listPictureButton;

}

PictureManager::addPictureModifier(PictureModifier * pictureModifier ) {
  PictureButton t_pictureButton = new PictureButton(PictureModifier); 
  m_listPictureButton.append(t_pictureButton);
  
}
