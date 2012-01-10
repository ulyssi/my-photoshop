#include "PictureManager.hh"
#include "UserInterface.hh"
#include "PictureButton.hh"
#include "PictureModifier.hh"


/** Constructeurs et destructeur */
PictureManager::PictureManager(UserInterface* userInterface) :
  TabPanel(userInterface)
{
  setTabName(QString("Thumbnail"));
  //  setWidget();
}

PictureManager::~PictureManager() {

}


/** Methodes */
Picture* PictureManager::getSelectedPicture() { return NULL; }

void PictureManager::addPictureModifier(PictureModifier* pictureModifier) {
  m_listPictureButton.append(new PictureButton(pictureModifier));
}

void PictureManager::refresh() {}
