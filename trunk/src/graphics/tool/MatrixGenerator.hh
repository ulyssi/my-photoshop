#ifndef _MATRIX_GENERATOR_HH_
#define _MATRIX_GENERATOR_HH_

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSpinBox>

#include "Matrix.hh"


class MatrixGenerator : public QWidget { Q_OBJECT

public:
  
  /** Constructeurs et destructeur */
  MatrixGenerator(Matrix<double>*, bool = true);
  ~MatrixGenerator();

  /** Mutateurs */
  void setMinimum(int);
  void setMaximum(int);
  void setRange(int, int);
  void setMatrix(Matrix<double>*);

  /** Methodes */
  Matrix<double>* createMatrix();

public slots:

  /** Slots */
  void refresh();
  void modifyMatrix();
  void resizeMatrix();
  
private:

  /** Methodes internes */
  QGroupBox* createDimensionBox();
  QGroupBox* createMatrixBox();
  void initialize();
  void clear();
  
  /** Attributs */
  int m_min, m_max;
  Matrix<double>* m_matrix;
  QSpinBox *m_spinBoxWidth, *m_spinBoxHeight;
  QGridLayout* m_matrixLayout;

};

#endif
