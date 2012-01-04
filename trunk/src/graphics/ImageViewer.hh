#include <QScrollArea>
#include <QLabel>
#include <QAction>

class ImageViewer : public QScrollArea { Q_OBJECT

public:
  
  /** Constructeurs et destructeurs */
  ImageViewer();
  ~ImageViewer();
               
private:

  /** Methodes internes */
  void scaleImage(double factor);

  /** Attributs */
  double m_scaleFactor;
  QLabel *m_imageLabel;
};
