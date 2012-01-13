#ifndef _AFFINE_OPERATION_CHOOSER_HH_
#define _AFFINE_OPERATION_CHOOSER_HH_

#include <QWidget>
#include <QMutex>

class UserInterface;
class PictureModifier;
class Previewer;


class AffineOperationChooser : public QWidget { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  AffineOperationChooser(UserInterface* = NULL);
  ~AffineOperationChooser();

  /** Mutateurs */
  void setPictureModifier(PictureModifier*);

  /** Methodes */
  void affinePreview();
					   
public slots:

  /** Slots */
  void refresh();
  void setValueScaleX(int);
  void setValueScaleY(int);
  void setValueRotation(int);
  void applyOperation();

private:

  /** Attributs */
  UserInterface* m_userInterface;
  QSlider* m_scaleSliderX;
  QSlider* m_scaleSliderY;
  QSlider* m_rotationSlider;
  double m_scaleX, m_scaleY, m_alpha;
  PictureModifier* m_pictureModifier;
  Previewer* m_previewer;
  QMutex* m_running;

};

#endif
