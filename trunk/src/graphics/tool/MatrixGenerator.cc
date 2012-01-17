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
  
  QVBoxLayout* layout = new QVBoxLayout;
  layout->addWidget(createMatrixBox());
  layout->addWidget(createDimensionBox());
  layout->addLayout(createControlsLayout());
  layout->addStretch();
  resize(0, 0);

  setLayout(layout);
  if (QDialog::Accepted == exec()) return m_matrix;
  else return matrix;
}


/** Slots */
void MatrixGenerator::resizeMatrix() {
  int width = m_matrix->getWidth(), height = m_matrix->getHeight();

  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++) {
      QWidget* widget = m_matrixLayout->itemAtPosition(i, j)->widget();
      m_matrixLayout->removeItem(m_matrixLayout->itemAtPosition(i, j));
      delete m_matrixLayout->itemAtPosition(i, j);
      delete widget;
    }
  
  if (width != m_spinBoxWidth->value()) width = m_spinBoxWidth->value();
  if (height != m_spinBoxHeight->value()) height = m_spinBoxHeight->value();
      
  Matrix<double>* tmp = new Matrix<double>(width, height);
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++) {
      int i2 = i - (width + m_matrix->getWidth())/2 - 1;
      int j2 = j - (height + m_matrix->getHeight())/2 - 1;
      if (0 <= i2 && i2 < m_matrix->getWidth() && 0 <= j2 && j2 < m_matrix->getHeight())
        tmp->setValue(i, j, m_matrix->getValue(i2, j2));
      else tmp->setValue(i, j, 0);
    }
  delete m_matrix;
  m_matrix = tmp;

  for (int i = 0; i < m_matrix->getWidth(); i++)
    for (int j = 0; j < m_matrix->getHeight(); j++) {
      QSpinBox* spinBox = new QSpinBox();
      spinBox->setValue(m_matrix->getValue(i, j));
      m_matrixLayout->addWidget(spinBox, i, j);
    }

  resize(0, 0);
}


/** Methodes internes */
QGroupBox* MatrixGenerator::createDimensionBox() {
  QGroupBox* groupBox = new QGroupBox();
  QHBoxLayout* layout = new QHBoxLayout();
  
  layout->addStretch();
  {
    QLabel* label = new QLabel("Width");
    m_spinBoxWidth = new QSpinBox();
    m_spinBoxWidth->setMinimum(1);
    m_spinBoxWidth->setValue(m_matrix->getWidth());
    m_spinBoxWidth->setSingleStep(2);
    connect(m_spinBoxWidth, SIGNAL(valueChanged(int)), this, SLOT(resizeMatrix()));
    
    layout->addWidget(label);
    layout->addWidget(m_spinBoxWidth);
  }

  {
    QLabel* label = new QLabel("Height");
    m_spinBoxHeight = new QSpinBox();
    m_spinBoxHeight->setMinimum(1);
    m_spinBoxHeight->setValue(m_matrix->getHeight());
    m_spinBoxHeight->setSingleStep(2);
    connect(m_spinBoxHeight, SIGNAL(valueChanged(int)), this, SLOT(resizeMatrix()));

    layout->addWidget(label);
    layout->addWidget(m_spinBoxHeight);
  }
  layout->addStretch();

  groupBox->setLayout(layout);
  return groupBox;
}

QGroupBox* MatrixGenerator::createMatrixBox() {
  QGroupBox*  groupBox = new QGroupBox(tr("Matrix"));  
  m_matrixLayout = new QGridLayout;

  for (int i = 0; i < m_matrix->getWidth(); i++)
    for (int j = 0; j < m_matrix->getHeight(); j++) {
      QSpinBox* spinBox = new QSpinBox();
      spinBox->setValue(m_matrix->getValue(i, j));
      m_matrixLayout->addWidget(spinBox, i, j);
    }

  groupBox->setLayout(m_matrixLayout);
  return groupBox;
}

QHBoxLayout* MatrixGenerator::createControlsLayout() {
  QHBoxLayout* layout = new QHBoxLayout;
  
  QPushButton* pushButtonCancel = new QPushButton(tr("Cancel"));
  QPushButton* pushButtonAccept = new QPushButton(tr("Accept"));

  connect(pushButtonCancel, SIGNAL(clicked()), this, SLOT(reject()));
  connect(pushButtonAccept, SIGNAL(clicked()), this, SLOT(accept()));

  layout->addStretch();
  layout->addWidget(pushButtonCancel);
  layout->addWidget(pushButtonAccept);
  layout->addStretch();

  return layout;
}
