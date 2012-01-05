#include "PictureModifier.hh"

#include "UserInterface.hh"
#include "PictureViewer.hh"
#include "TracingManager.hh"

#include "Picture.hh"

/** Constructeurs et destructeur */
PictureModifier::PictureModifier(Picture* picture, UserInterface* userInterface) :
  m_userInterface(userInterface),
  m_picture(picture),
  m_pictureViewer(new PictureViewer(picture)),
  m_tracingManager(new TracingManager(this))
{}

PictureModifier::~PictureModifier() {
  delete m_pictureViewer;
  delete m_tracingManager;
}

/** Accesseurs */
Picture* PictureModifier::getPicture() const { return m_picture; }

PictureViewer* PictureModifier::getPictureViewer() const { return m_pictureViewer; }

TracingManager* PictureModifier::getTracingManager() const { return m_tracingManager; }

