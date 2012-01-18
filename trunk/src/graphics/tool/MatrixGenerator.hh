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
  MatrixGenerator(Matrix<double>*, int = 0, int = 100, bool = true);
  ~MatrixGenerator();

  /** Mutateurs */
  void setMinimum(int);
  void setMaximum(int);
  void setRange(int, int);
  
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
  int m_min, m_max;
  Matrix<double>* m_matrix;
  QSpinBox *m_spinBoxWidth, *m_spinBoxHeight;
  QGridLayout* m_matrixLayout;

};

#endif
