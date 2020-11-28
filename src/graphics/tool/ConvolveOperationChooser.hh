#ifndef _CONVOLVE_OPERATION_CHOOSER_HH_
#define _CONVOLVE_OPERATION_CHOOSER_HH_

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>
#include <QString>

#include "../../model/Matrix.hh"

class UserInterface;
class ConvolveOperation;
class PictureModifier;
class MatrixGenerator;


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
  void kernelUpdate();
  void setKernelValue(int, int, double);

  void resetOperation();
  void refreshPreview();
  void applyOperation();

private:

  /** Methodes internes */
  QComboBox* createKernelGroupBox();
  MatrixGenerator* createMatrixModifier();
  QGroupBox* createCanalsGroupBox();
  QGroupBox* createSizeGroupBox();
  QHBoxLayout* createSettingsGroupBox();
  QHBoxLayout* createControlsLayout();

private slots:

  /** Slots internes */

signals:

  /** Signaux internes */
  void dataChanged();

private:

  /** Attributs */
  UserInterface* m_userInterface;
  PictureModifier* m_pictureModifier;
  ConvolveOperation* m_convolveOperation;

  Matrix<double>* m_kernel;
  MatrixGenerator* m_matrixModifier;

  QComboBox* m_kernelComboBox;
  QString m_identityKernelString;
  QString m_averageBlurKernelString;
  QString m_gaussianBlurKernelString;
  QString m_increaseContrastKernelString;
  QString m_sharpnessKernelString;
  QString m_unsharpKernelString;
  QString m_stampingKernelString;
  QString m_repulsingKernelString;
  QString m_laplacianKernelString;
  QString m_laplacianBisKernelString;
  QString m_laplacianOfGaussianKernelString;
  QString m_gradientXKernelString;
  QString m_gradientYKernelString;
  QString m_sobelXKernelString;
  QString m_sobelYKernelString;
  QString m_northEdgeStrengtheningKernelString;
  QString m_southEdgeStrengtheningKernelString;
  QString m_eastEdgeStrengtheningKernelString;
  QString m_westEdgeStrengtheningKernelString;
  QString m_lineDetectionHorizontalKernelString;
  QString m_lineDetectionVerticalKernelString;
  QString m_lineDetectionNorthEastKernelString;
  QString m_lineDetectionSouthEastKernelString;
  QString m_customizeKernelString;

  QComboBox* m_edgeControlComboBox;
  QString m_extendControlString;
  QString m_cropControlString;
  QString m_wrapControlString;

  QComboBox* m_operatorComboBox;
  QString m_timesOperatorString;
  QString m_medianOperatorString;
  QString m_maxOperatorString;
  QString m_minOperatorString;

  QSpinBox *m_spinBoxWidth, *m_spinBoxHeight;
  QCheckBox *m_buttonCanalRed, *m_buttonCanalGreen, *m_buttonCanalBlue, *m_buttonCanalAlpha;

};

#endif
