#ifndef _MATRIX_GENERATOR_HH_
#define _MATRIX_GENERATOR_HH_

#include <QPoint>
#include <QWidget>
#include <QGridLayout>
#include <QSignalMapper>

#include "Matrix.hh"


class MatrixGenerator : public QWidget { Q_OBJECT

public:
  
  /** Constructeurs et destructeur */
  MatrixGenerator(int, int);
  ~MatrixGenerator();

  /** Mutateurs */
  void setSingleStep(double);
  void setMatrix(Matrix<double>*);

  /** Accesseurs */
  int width();
  int height();
  double value(int, int);

public slots:

  /** Slots */
  void setMinimum(double);
  void setMaximum(double);
  void setRange(double, double);

  void setWidth(int);
  void setHeight(int);
  void setSize(int, int);

  void setValue(int, int, double);

signals:
  
  /** Signaux */
  void valueChanged(int, int, double);
  void widthChanged(int);
  void heightChanged(int);
  
private:

  /** Methodes internes */

private slots:
  
  /** Signaux internes */
  void valueChanged(QObject*);
  
private:

  /** Attributs */
  int m_width, m_height;
  double m_min, m_max, m_singleStep, m_pageStep;
  QGridLayout* m_layout;
  QSignalMapper* m_signalMapper;

};

#endif
