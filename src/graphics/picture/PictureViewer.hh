#ifndef _PICTURE_VIEWER_HH_
#define _PICTURE_VIEWER_HH_

#include <QLabel>
#include <QImage>

class PictureModifier;

class PictureViewer : public QLabel{ Q_OBJECT

public:
  /** Constructeurs et destructeurs */
  PictureViewer(PictureModifier*);
  ~PictureViewer();
               
  /** Methodes */

  void zoomIn();
  void refresh();
  void refreshData();
  PictureModifier*  getPictureModifier();
private:

  /** Methodes internes */
  /** Attributs */
  double m_scaleFactor;
  PictureModifier* m_pictureModifier;
  QImage m_qImage;
  QImage* m_realqImage;
  bool tmp;
};

#endif
