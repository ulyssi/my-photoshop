#include "PictureModifier.hh"

#include "UserInterface.hh"
#include "ImageViewer.hh"
#include "TracingManager.hh"

#include "../model/Picture.hh"

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
Picture* PictureModifier::getPicture() const { return m_picture; }

ImageViewer* PictureModifier::getImageViewer() const { return m_imageViewer; }

TracingManager* PictureModifier::getTracingManager() const { return m_tracingManager; }

