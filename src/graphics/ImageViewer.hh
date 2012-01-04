#ifndef _IMAGE_VIEWER_HH_
#define _IMAGE_VIEWER_HH_

#include <QScrollArea>
#include <QLabel>

class Picture;

class ImageViewer : public QScrollArea { Q_OBJECT

public:
  
  /** Constructeurs et destructeurs */
  ImageViewer(Picture*);
  ~ImageViewer();
               
private:

  /** Methodes internes */
  void scaleImage(double factor);

  /** Attributs */
  double m_scaleFactor;
  QLabel* m_imageLabel;

};

#endif
