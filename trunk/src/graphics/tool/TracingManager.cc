#include "TracingManager.hh"

#include <QString>
#include "PictureModifier.hh"



/** Constructeurs et destructeur */
TracingManager::TracingManager(PictureModifier* pictureModifier) :
  m_pictureModifier(pictureModifier)
{
  setAccessibleName(QString(tr("Tracing Manager")));
}

TracingManager::~TracingManager() {}


/** Mutateurs */
void TracingManager::setPictureModifier(PictureModifier* pictureModifier) {
  m_pictureModifier = pictureModifier; 
  refresh();
}


/** Predicats */
bool TracingManager::isEnabled() { return QListWidget::isEnabled() && m_pictureModifier != NULL; }


/** Methodes */
void TracingManager::refresh() {
  if (m_pictureModifier != NULL) {
  }
}
