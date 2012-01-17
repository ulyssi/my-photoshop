#ifndef _CONVOLVE_OPERATION_CHOOSER_HH_
#define _CONVOLVE_OPERATION_CHOOSER_HH_

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QSlider>
#include <QCheckBox>
#include <QRadioButton>

#include "Matrix.hh"

class UserInterface;
class ConvolveOperation;
class PictureModifier;


class ConvolveOperationChooser : public QWidget { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  ConvolveOperationChooser(UserInterface*);
  ~ConvolveOperationChooser();

  /** Mutateurs */
  void setPictureModifier(PictureModifier*);

  /** Methodes */
  void refresh();
		
public slots:

  /** Slots */
  void modifyBlur();
  void modifyDetection();
  void resetOperation();
  void refreshPreview();
  void applyOperation();

private:

  /** Methodes internes */
  QGroupBox* createBlurGroupBox();
  QGroupBox* createDetectionGroupBox();
  QGroupBox* createCanalsGroupBox();
  QHBoxLayout* createControlsLayout();
  void resetBlurOperation();
  void resetDetectionOperation();

  /** Attributs */
  UserInterface* m_userInterface;
  PictureModifier* m_pictureModifier;
  ConvolveOperation* m_convolveOperation;
  Matrix<double>* m_kernel;
  QRadioButton *m_buttonNoneBlur, *m_buttonAverageBlur, *m_buttonGaussianBlur;
  QSlider *m_sliderBlurLevel;
  QRadioButton *m_buttonNoneDetection, *m_buttonEdgeDetection, *m_buttonLeftEdgeStrengthening, *m_buttonRepulsing;
  QCheckBox *m_buttonCanalRed, *m_buttonCanalGreen, *m_buttonCanalBlue, *m_buttonCanalAlpha;

};

#endif
