#include "PictureManager.hh"

#include "UserInterface.hh"
#include "PictureButton.hh"
#include "PictureModifier.hh"

PictureManager::PictureManager(UserInterface* userInterface) :
  m_userInterface(userInterface),
  m_listPictureButton()
{}

PictureManager::~PictureManager() {}

void PictureManager::addPictureModifier(PictureModifier* pictureModifier) {
  m_listPictureButton.append(new PictureButton(pictureModifier));
}
