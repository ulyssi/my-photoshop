#include "MatrixGenerator.hh"

#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>


/** Constructeurs et destructeur */
MatrixGenerator::MatrixGenerator() {}

MatrixGenerator::~MatrixGenerator() {}


/** Methodes */
Matrix<double>* MatrixGenerator::modify(Matrix<double>* matrix) {
  if (matrix != NULL) {
    m_matrix = new Matrix<double>(matrix);
  } else {
    m_matrix = new Matrix<double>(1, 1);
    matrix->setValue(0, 0, 1.0);
  }
  show();
  
  QVBoxLayout* layout = new QVBoxLayout;
  layout->addWidget(createMatrixBox());
  layout->addWidget(createDimensionBox());
  layout->addLayout(createControlsLayout());
  layout->addStretch();
  resize(0, 0);

  setLayout(layout);
  return m_matrix;
}

Matrix<double>* MatrixGenerator::run() {
  show();
  Matrix<double>* matrix = new Matrix<double>(1, 1);
  matrix->setValue(0, 0, 1.0);
  return matrix;
}


/** Methodes internes */
QGroupBox* MatrixGenerator::createDimensionBox() {
  QGroupBox* groupBox = new QGroupBox();
  QHBoxLayout* layout = new QHBoxLayout();
  
  layout->addStretch();
  {
    QLabel* label = new QLabel("Width");
    QSpinBox* spinBox = new QSpinBox();
    spinBox->setMinimum(1);
    spinBox->setValue(m_matrix->getWidth());
    spinBox->setSingleStep(2);
    layout->addWidget(label);
    layout->addWidget(spinBox);
  }

  {
    QLabel* label = new QLabel("Height");
    QSpinBox* spinBox = new QSpinBox();
    spinBox->setMinimum(1);
    spinBox->setValue(m_matrix->getHeight());
    spinBox->setSingleStep(2);
    layout->addWidget(label);
    layout->addWidget(spinBox);
  }
  layout->addStretch();

  groupBox->setLayout(layout);
  return groupBox;
}

QGroupBox* MatrixGenerator::createMatrixBox() {
  QGroupBox* groupBox = new QGroupBox(tr("Matrix"));  
  QGridLayout* matrixLayout = new QGridLayout;
  
  {
    for (int i = 0; i < m_matrix->getWidth(); i++)
      for (int j = 0; j < m_matrix->getHeight(); j++) {
	QSpinBox* spinBox = new QSpinBox();
	spinBox->setValue(m_matrix->getValue(i, j));
	matrixLayout->addWidget(spinBox, i, j);
      }
  }

  groupBox->setLayout(matrixLayout);
  return groupBox;
}

QHBoxLayout* MatrixGenerator::createControlsLayout() {
  QHBoxLayout* layout = new QHBoxLayout;
  
  QPushButton* pushButtonCancel = new QPushButton(tr("Cancel"));
  QPushButton* pushButtonAccept = new QPushButton(tr("Accept"));

  layout->addStretch();
  layout->addWidget(pushButtonCancel);
  layout->addWidget(pushButtonAccept);
  layout->addStretch();

  return layout;
}
