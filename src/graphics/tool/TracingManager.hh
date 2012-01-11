#ifndef _TRACING_MANAGER_HH_
#define _TRACING_MANAGER_HH_

#include <QListWidget>

class PictureModifier;

class TracingManager : public QListWidget { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  TracingManager(PictureModifier* = NULL);
  ~TracingManager();

  /** Mutateurs */
  void setPictureModifier(PictureModifier*);

  /** Predicats */
  bool isEnabled();
  
  /** Methodes */
  void refresh();
  
private:

  /** Attributs */
  PictureModifier* m_pictureModifier;

};

#endif
