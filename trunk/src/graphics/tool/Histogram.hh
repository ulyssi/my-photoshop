#ifndef _HISTOGRAM_HH_
#define _HISTOGRAM_HH_

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QRadioButton>
#include <QComboBox>

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
  void refreshData(bool = true);

public slots:
  
  /** Slots */
  void refreshComboBoxLayer();
  void refreshImage();
  
private:
  
  /** Attributs */
  PictureModifier* m_pictureModifier;
  QRadioButton* m_radioButtonRGB;
  QRadioButton* m_radioButtonYUV;
  QComboBox* m_comboBoxLayer;
  QLabel* m_histogramLabel;
  QImage* m_histogramImage;
  int m_histogramData[3][256];

};

#endif
