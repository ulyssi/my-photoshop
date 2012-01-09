#ifndef _TRACING_MANAGER_HH_
#define _TRACING_MANAGER_HH_

#include <QListWidget>

class PictureModifier;

class TracingManager : public QListWidget { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  TracingManager(PictureModifier*);
  ~TracingManager();

  /** Accesseurs */
  PictureModifier* getPictureModifier();
  
private:

  /** Attributs */
  PictureModifier* m_pictureModifier;

};

#endif
