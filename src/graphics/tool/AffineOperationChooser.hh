#ifndef _AFFINE_OPERATION_CHOOSER_HH_
#define _AFFINE_OPERATION_CHOOSER_HH_

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QSlider>
#include <QRadioButton>

class UserInterface;
class PictureModifier;


class AffineOperationChooser : public QWidget { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  AffineOperationChooser(UserInterface* = NULL);
  ~AffineOperationChooser();

  /** Mutateurs */
  void setPictureModifier(PictureModifier*);

  /** Methodes */
  void refresh();
					   
public slots:

  /** Slots */
  void setValueScaleX(int);
  void setValueScaleY(int);
  void setValueRotation(int);
  void setValueSymetrieNormal(bool);
  void setValueSymetrieX(bool);
  void setValueSymetrieY(bool);
  void setValueSymetrie(bool);
  void resetOperation();
  void refreshPreview();
  void applyOperation();
  
private:

  /** Methodes interne */
  QGroupBox* createScaleGroupBox();
  QGroupBox* createRotationGroupBox();
  QGroupBox* createSymetrieGroupBox();
  QHBoxLayout* createControlsLayout();

  /** Attributs */
  UserInterface* m_userInterface;
  QSlider *m_scaleSliderX, *m_scaleSliderY, *m_rotationSlider;
  QRadioButton *m_buttonSymetrieNormal, *m_buttonSymetrieX, *m_buttonSymetrieY, *m_buttonSymetrie;
  bool m_symetrieNormal, m_symetrieX, m_symetrieY, m_symetrie;
  double m_scaleX, m_scaleY, m_alpha;
  PictureModifier* m_pictureModifier;
  
};

#endif
