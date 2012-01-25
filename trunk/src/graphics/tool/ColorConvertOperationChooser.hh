#ifndef _COLOR_CONVERT_OPERATION_CHOOSER_HH_
#define _COLOR_CONVERT_OPERATION_CHOOSER_HH_

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QComboBox>
#include <QString>

#include "Matrix.hh"

class UserInterface;
class ColorConvertOperation;
class PictureModifier;
class MatrixGenerator;


class ColorConvertOperationChooser : public QWidget { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  ColorConvertOperationChooser(UserInterface*);
  ~ColorConvertOperationChooser();

  /** Mutateurs */
  void setPictureModifier(PictureModifier*);

  /** Methodes */
  void refresh();

public slots:

  /** Slots */
  void kernelComboBoxChanged(int);
  void setKernelValue(int, int, double);

  void resetOperation();
  void refreshPreview();
  void applyOperation();

signals:

private:

  /** Methodes internes */
  QComboBox* createKernelGroupBox();
  QHBoxLayout* createControlsLayout();
  MatrixGenerator* createMatrixModifier();
  void resetBlurOperation();
  void resetDetectionOperation();
  
private slots:

  /** Slots internes */
  
signals:
  
  /** Signaux internes */
  void dataChanged();

private:

  /** Attributs */
  UserInterface* m_userInterface;
  PictureModifier* m_pictureModifier;
  QComboBox* m_kernelComboBox;
  Matrix<double>* m_kernel;
  ColorConvertOperation* m_colorConvertOperation;
  
  MatrixGenerator* m_matrixGenerator;
  QString m_identityKernelString;
  QString m_greyScaleKernelString;
  QString m_sepiaKernelString;
  QString m_customizeKernelString;
 
};

#endif
