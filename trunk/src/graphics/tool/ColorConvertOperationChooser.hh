#ifndef _COLOR_CONVERT_OPERATION_CHOOSER_HH_
#define _COLOR_CONVERT_OPERATION_CHOOSER_HH_

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QSlider>
#include <QCheckBox>
#include <QRadioButton>

#include "Matrix.hh"

class UserInterface;
class ColorConvertOperation;
class PictureModifier;


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
  void modifyMatrix();
  void resetOperation();
  void refreshPreview();
  void applyOperation();

private:

  /** Methodes internes */
  QGroupBox* createMatrixGroupBox();
  QHBoxLayout* createControlsLayout();
  void resetBlurOperation();
  void resetDetectionOperation();
  
  /** Attributs */
  UserInterface* m_userInterface;
  PictureModifier* m_pictureModifier;
  QGridLayout* m_matrixLayout;
  ColorConvertOperation* m_colorConvertOperation;
  Matrix<double>* m_kernel;

};

#endif
