#ifndef _PICTURE_VIEWER_HH_
#define _PICTURE_VIEWER_HH_

#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QSize>
#include <iostream>
class PictureModifier;

class PictureViewer : public QLabel{ Q_OBJECT

public:
  /** Constructeurs et destructeurs */
  PictureViewer(PictureModifier*);
  ~PictureViewer();
               
  /** Methodes */
  void scaleImage(double);
  void refresh();
  void refreshData();
  QImage getImage();
  void zoomIn();
  double getScale();
  double getWidthTranslation();
  double getHeightTranslation();
  double zoomOut();
  double normalSize();
  double fitToWindow(QSize);
  PictureModifier*  getPictureModifier();
private:

  /** Methodes internes */
  /** Attributs */
  double m_width_translation;
  double m_height_translation; 
  double m_scaleFactor;
  double m_scale;
  PictureModifier* m_pictureModifier;
  QImage m_qImage;
   
};

#endif
