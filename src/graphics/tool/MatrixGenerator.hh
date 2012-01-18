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
  MatrixGenerator(Matrix<double>*, bool = true);
  ~MatrixGenerator();

  /** Methodes */
  Matrix<double>* createMatrix();

public slots:

  /** Slots */
  void modifyMatrix();
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
