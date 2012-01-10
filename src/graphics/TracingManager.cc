#include "TracingManager.hh"

#include "PictureModifier.hh"



/** Constructeurs et destructeur */
TracingManager::TracingManager(PictureModifier* pictureModifier) :
  m_pictureModifier(pictureModifier)
{}

TracingManager::~TracingManager() {}


/** Accesseurs */
PictureModifier* TracingManager::getPictureModifier() { return m_pictureModifier; }


/** Mutateurs */
void TracingManager::setPictureModifier(PictureModifier* pictureModifier) { m_pictureModifier = pictureModifier; }


/** Methodes */
void TracingManager::refresh() {}
