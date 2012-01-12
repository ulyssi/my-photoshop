#ifndef _HISTOGRAM_HH_
#define _HISTOGRAM_HH_

#include <QWidget>
#include <QLabel>
#include <QImage>

class PictureModifier;

class Histogram : public QWidget { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  Histogram(PictureModifier* = NULL);
  ~Histogram();

  /** Mutateurs */
  void setPictureModifier(PictureModifier*);
  
  /** Predicats */
  bool isEnabled();

  /** Methodes */
  void refresh();
  
private:
  
  /** Attributs */
  PictureModifier* m_pictureModifier;
  QLabel* m_histogramLabel;

  QImage* m_histogramMulti;
  QImage* m_histogramRed;
  QImage* m_histogramGreen;
  QImage* m_histogramBlue;
  
  int m_histogramRedD[256];
  int m_histogramGreenD[256];
  int m_histogramBlueD[256];
  
};

#endif
