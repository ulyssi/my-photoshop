#include "TracingManager.hh"

#include "PictureModifier.hh"

/** Constructeurs et destructeur */
TracingManager::TracingManager(PictureModifier* pictureModifier) :
  m_pictureModifier(pictureModifier)
{}

TracingManager::~TracingManager() {}

/** Accesseurs */
PictureModifier* TracingManager::getPictureModifier() const {
  return m_pictureModifier;
}
