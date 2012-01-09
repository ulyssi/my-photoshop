#ifndef _PICTURE_VIEWER_HH_
#define _PICTURE_VIEWER_HH_

#include <QLabel>

class PictureModifier;

class PictureViewer : public QLabel { Q_OBJECT

public:
  
  /** Constructeurs et destructeurs */
  PictureViewer(PictureModifier*);
  ~PictureViewer();
               
private:

  /** Methodes internes */
  void scaleImage(double factor);

  /** Attributs */
  double m_scaleFactor;
  
};

#endif
