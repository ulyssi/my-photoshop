#include "TracingManager.hh"

/** Constructeurs et destructeur */
TracingManager::TracingManager(PictureModifier* pictureModifier) :
  m_pictureModifier(pictureModifier)
{}

TracingManager::~TracingManager() {}

/** Accesseurs */
PictureModifier* getPictureModifier() const {
  return m_pictureModifier;
}
