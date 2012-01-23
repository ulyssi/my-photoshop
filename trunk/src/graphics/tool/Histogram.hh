#ifndef _HISTOGRAM_HH_
#define _HISTOGRAM_HH_

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QRadioButton>
#include <QComboBox>
#include <QSlider>
#include <QPushButton>

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
  void crop(int,int);
  void equalization();
  void refreshData(bool = true);
  int getChrominanceUForHistogram(int);
  int getChrominanceVForHistogram(int);

public slots:
  
  /** Slots */
  void refreshComboBoxLayer();
  void refreshImage();
  void sliderInfChanged(int);
  void sliderSupChanged(int);
  void applyHistogramCrop();
  void applyHistogramEqualization();
  void applyHistogramLinearization();
private:
  
  /** Attributs */
  int m_bInf;
  int m_bSup;
  PictureModifier* m_pictureModifier;
  QRadioButton* m_radioButtonRGB;
  QRadioButton* m_radioButtonYUV;
  QComboBox* m_comboBoxLayer;
  QSlider* m_sliderInf;
  QSlider* m_sliderSup;
  QPushButton* m_applyRescale;
  QPushButton* m_applyEqualization;
  QPushButton* m_applyLinearization;
  QLabel* m_histogramLabel;
  QImage* m_histogramImage;
  int m_histogramData[3][256];
  int m_cumulativeHistogram[3][256];

};

#endif
