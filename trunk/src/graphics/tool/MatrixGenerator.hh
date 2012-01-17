#ifndef _MATRIX_GENERATOR_HH_
#define _MATRIX_GENERATOR_HH_

#include <QDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSpinBox>

#include "Matrix.hh"


class MatrixGenerator : public QDialog { Q_OBJECT

public:
  
  /** Constructeurs et destructeur */
  MatrixGenerator();
  ~MatrixGenerator();

  /** Methodes */
  Matrix<double>* modify(Matrix<double>* matrix);

public slots:

  /** Slots */
  void resizeMatrix();
  
private:

  /** Methodes internes */
  QGroupBox* createDimensionBox();
  QGroupBox* createMatrixBox();
  QHBoxLayout* createControlsLayout();
  
  /** Attributs */
  Matrix<double>* m_matrix;
  QSpinBox *m_spinBoxWidth, *m_spinBoxHeight;
  QGridLayout* m_matrixLayout;

};

#endif
