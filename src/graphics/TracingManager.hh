#ifndef _TRACINGMANAGER_HH_
#define _TRACINGMANAGER_HH_

#include <QListWidget>

class PictureModifier;

class TracingManager : public QListWidget { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  TracingManager(PictureModifier*);
  ~TracingManager();

  /** Accesseurs */
  PictureModifier* getPictureModifier() const;
  
private:

  /** Attributs */
  PictureModifier* m_pictureModifier;

};

#endif
