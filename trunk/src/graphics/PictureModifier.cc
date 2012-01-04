#include "PictureModifier.hh"

/** Constructeurs et destructeur */
PictureModifier::PictureModifier(Picture* picture, UserInterface* userInterface) :
  m_userInterface(userInterface),
  m_picture(picture),
  m_imageViewer(new ImageViewer(picture)),
  m_tracingManager(new TracingManager(this))
{}

PictureModifier::~PictureModifier() {
  delete m_imageViewer;
  delete m_tracingManager;
}

/** Accesseurs */
ImageViewer* PictureModifier::getImageViewer() const { return m_imageViewer; }

TracingManager* PictureModifier::getTracingManager() const { return m_tracingManager; }

