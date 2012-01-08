#include "PictureManager.hh"
#include "UserInterface.hh"
#include "PictureButton.hh"
#include "PictureModifier.hh"


/** Constructeurs et destructeur */
PictureManager::PictureManager(UserInterface* userInterface) :
  m_userInterface(userInterface),
  m_tabName("Thumbnails"),
  m_listPictureButton()
{}

PictureManager::~PictureManager() {}


/** Accesseurs */
const QString& PictureManager::getTabName() const {
  return m_tabName; 
}

/** Methodes */
void PictureManager::addPictureModifier(PictureModifier* pictureModifier) {
  m_listPictureButton.append(new PictureButton(pictureModifier));
}
