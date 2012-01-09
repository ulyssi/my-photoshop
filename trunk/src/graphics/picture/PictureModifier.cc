#include "PictureModifier.hh"

#include "UserInterface.hh"
#include "TracingManager.hh"
#include "PictureViewer.hh"

#include "../model/Picture.hh"

/** Constructeurs et destructeur */
PictureModifier::PictureModifier(Picture* picture, UserInterface* userInterface) :
  TabPanel(userInterface),
  m_picture(picture),
  m_pictureViewer(new PictureViewer(picture)),
  m_tracingManager(new TracingManager(this))
{
  setTabName(m_picture->getName());
  setWidget(m_pictureViewer);
}

PictureModifier::~PictureModifier() {
  delete m_tracingManager;
}


/** Accesseurs */
Picture* PictureModifier::getPicture() const { return m_picture; }

TracingManager* PictureModifier::getTracingManager() const { return m_tracingManager; }


/** Methodes */
std::vector<Picture*> PictureModifier::getSelectedPicture() {
  return std::vector<Picture*>(3);
}

void PictureModifier::refresh() {}
