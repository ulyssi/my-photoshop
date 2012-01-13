#ifndef _AFFINE_OPERATION_CHOOSER_HH_
#define _AFFINE_OPERATION_CHOOSER_HH_

#include <QWidget>
#include <QLabel>
#include <QMutex>

class PictureModifier;


class AffineOperationChooser : public QWidget { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  AffineOperationChooser();
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
  
private:

  /** Attributs */
  int m_scaleX, m_scaleY, m_alpha;
  PictureModifier* m_pictureModifier;
  QLabel* m_labelPreview;
  QMutex* m_running;

};

#endif
