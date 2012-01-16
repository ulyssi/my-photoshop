#ifndef _CONVOLVE_OPERATION_CHOOSER_HH_
#define _CONVOLVE_OPERATION_CHOOSER_HH_

#include <QWidget>

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

public slots:

  /** Slots */
  void averageBlur();
  void gaussianBlur();
  void initialize();
  void applyOperation();
  void refresh();
  void refreshPreview();

private:

  /** Attributs */
  UserInterface* m_userInterface;
  PictureModifier* m_pictureModifier;
  ConvolveOperation* m_convolveOperation;
  Matrix<double>* m_kernel;

};

#endif
