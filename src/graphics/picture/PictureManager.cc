#include "PictureManager.hh"
#include "UserInterface.hh"
#include "PictureButton.hh"
#include "PictureModifier.hh"


/** Constructeurs et destructeur */
PictureManager::PictureManager(UserInterface* userInterface) :
  TabPanel(userInterface),
  m_listPictureButton()
{
  setTabName(new QString("Thumbnail"));
}

PictureManager::~PictureManager() {}


/** Methodes */
std::vector<Picture*> PictureManager::getSelectedPicture() {}

void PictureManager::addPictureModifier(PictureModifier* pictureModifier) {
  m_listPictureButton.append(new PictureButton(pictureModifier));
}

void PictureManager::refresh() {}
