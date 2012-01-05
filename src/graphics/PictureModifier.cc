#include "PictureModifier.hh"

#include "UserInterface.hh"
#include "PictureArea.hh"
#include "TracingManager.hh"

#include "Picture.hh"

/** Constructeurs et destructeur */
PictureModifier::PictureModifier(Picture* picture, UserInterface* userInterface) :
  m_userInterface(userInterface),
  m_picture(picture),
  m_pictureArea(new PictureArea(this)),
  m_tracingManager(new TracingManager(this))
{}

PictureModifier::~PictureModifier() {
  delete m_pictureArea;
  delete m_tracingManager;
}

/** Accesseurs */
Picture* PictureModifier::getPicture() const { return m_picture; }

PictureArea* PictureModifier::getPictureArea() const { return m_pictureArea; }

TracingManager* PictureModifier::getTracingManager() const { return m_tracingManager; }

