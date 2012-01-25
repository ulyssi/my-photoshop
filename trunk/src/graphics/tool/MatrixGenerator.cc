#include "MatrixGenerator.hh"

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QLabel>


/** Constructeurs et destructeur */
MatrixGenerator::MatrixGenerator(int width, int height) :
  m_width(width),
  m_height(height),
  m_min(0.0),
  m_max(1.0),
  m_layout(new QGridLayout()),
  m_signalMapper(new QSignalMapper())
{
  for (int i = 0; i < m_width; i++)
    for (int j = 0; j < m_height; j++) {
      QDoubleSpinBox* spinBox = new QDoubleSpinBox();
      spinBox->setValue(m_min);
      spinBox->setRange(m_min, m_max);
      
      m_signalMapper->setMapping((QObject*)spinBox, (QObject*)new QPoint(i, j));
      connect(spinBox, SIGNAL(valueChanged(double)), m_signalMapper, SLOT(map()));

      m_layout->addWidget(spinBox, j, i);
    }
  connect(m_signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(valueChanged(QObject*)));
  setLayout(m_layout);
}

MatrixGenerator::~MatrixGenerator() {}


/** Accesseurs */
int MatrixGenerator::width() { return m_width; }

int MatrixGenerator::height() { return m_height; }

double MatrixGenerator::value(int i, int j) {
  return ((QDoubleSpinBox*)m_layout->itemAtPosition(j, i)->widget())->value();
}


/** Mutateurs */
void MatrixGenerator::setSingleStep(double singleStep) {
  for (int i = 0; i < m_width; i++)
    for (int j = 0; j < m_height; j++)
      ((QDoubleSpinBox*)m_layout->itemAtPosition(j, i)->widget())->setSingleStep(singleStep);
}

void MatrixGenerator::setMatrix(Matrix<double>* matrix) {
  setSize(matrix->getWidth(), matrix->getHeight());
  disconnect(m_signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(valueChanged(QObject*)));
  for (int i = 0; i < m_width; i++)
    for (int j = 0; j < m_height; j++)
      ((QDoubleSpinBox*)m_layout->itemAtPosition(j, i)->widget())->setValue(matrix->getValue(i, j));
  connect(m_signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(valueChanged(QObject*)));
}


/** Slots */
void MatrixGenerator::setMinimum(double min) { 
  m_min = min; 
  for (int i = 0; i < m_width; i++)
    for (int j = 0; j < m_height; j++)
      ((QDoubleSpinBox*)m_layout->itemAtPosition(j, i)->widget())->setMinimum(m_min);
}

void MatrixGenerator::setMaximum(double max) {
  m_max = max; 
  for (int i = 0; i < m_width; i++)
    for (int j = 0; j < m_height; j++)
      ((QDoubleSpinBox*)m_layout->itemAtPosition(j, i)->widget())->setMaximum(m_max);
}

void MatrixGenerator::setRange(double min, double max) {
  m_min = min;
  m_max = max;
  for (int i = 0; i < m_width; i++)
    for (int j = 0; j < m_height; j++)
      ((QDoubleSpinBox*)m_layout->itemAtPosition(j, i)->widget())->setRange(m_min, m_max);
}

void MatrixGenerator::setWidth(int width) {
  disconnect(m_signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(valueChanged(QObject*)));
  if (width < m_width) {
    int decal = (m_width - width) / 2;
    for (int i = decal; i < m_width; i++)
      for (int j = 0; j < m_height; j++) {
        QDoubleSpinBox* source = ((QDoubleSpinBox*)m_layout->itemAtPosition(j, i)->widget());
        QDoubleSpinBox* target = ((QDoubleSpinBox*)m_layout->itemAtPosition(j, i - decal)->widget());
        target->setValue(source->value());
      }

    for (int i = width; i < m_width; i++)
      for (int j = 0; j < m_height; j++) {
        QWidget* widget = m_layout->itemAtPosition(j, i)->widget();
        m_layout->removeItem(m_layout->itemAtPosition(j, i));
        delete m_layout->itemAtPosition(j, i);
        delete widget;
      }

    m_width = width;
    emit(widthChanged(m_width));
  }
  else if (m_width < width) {
    for (int i = m_width; i < width; i++)
      for (int j = 0; j < m_height; j++) {
        QDoubleSpinBox* spinBox = new QDoubleSpinBox();
        spinBox->setValue(m_min);
        spinBox->setRange(m_min, m_max);
        
        m_signalMapper->setMapping((QObject*)spinBox, (QObject*)new QPoint(i, j));
        connect(spinBox, SIGNAL(valueChanged(double)), m_signalMapper, SLOT(map()));
        
        m_layout->addWidget(spinBox, j, i);
      }

    int decal = (width - m_width) / 2;
    for (int i = m_width-1; i >= 0; i--)
      for (int j = 0; j < m_height; j++) {
        QDoubleSpinBox* source = ((QDoubleSpinBox*)m_layout->itemAtPosition(j, i)->widget());
        QDoubleSpinBox* target = ((QDoubleSpinBox*)m_layout->itemAtPosition(j, i + decal)->widget());
        target->setValue(source->value());
        source->setValue(m_min);
      }

    m_width = width;
    emit(widthChanged(m_width));
  }
  connect(m_signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(valueChanged(QObject*)));
}

void MatrixGenerator::setHeight(int height) {
  disconnect(m_signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(valueChanged(QObject*)));
  if (height < m_height) {
    int decal = (m_height - height) / 2;
    for (int j = decal; j < m_height; j++)
      for (int i = 0; i < m_width; i++) {
        QDoubleSpinBox* source = ((QDoubleSpinBox*)m_layout->itemAtPosition(j, i)->widget());
        QDoubleSpinBox* target = ((QDoubleSpinBox*)m_layout->itemAtPosition(j - decal, i)->widget());
        target->setValue(source->value());
      }

    for (int j = height; j < m_height; j++)
      for (int i = 0; i < m_width; i++) {
        QWidget* widget = m_layout->itemAtPosition(j, i)->widget();
        m_layout->removeItem(m_layout->itemAtPosition(j, i));
        delete m_layout->itemAtPosition(j, i);
        delete widget;
      }

    m_height = height;
    emit(heightChanged(m_height));
  }
  else if (m_height < height) {
    for (int j = m_height; j < height; j++)
      for (int i = 0; i < m_width; i++) {
        QDoubleSpinBox* spinBox = new QDoubleSpinBox();
        spinBox->setValue(m_min);
        spinBox->setRange(m_min, m_max);
        
        m_signalMapper->setMapping((QObject*)spinBox, (QObject*)new QPoint(i, j));
        connect(spinBox, SIGNAL(valueChanged(double)), m_signalMapper, SLOT(map()));
        
        m_layout->addWidget(spinBox, j, i);
      }

    int decal = (height - m_height) / 2;
    for (int j = m_height-1; j >= 0; j--)
      for (int i = 0; i < m_width; i++) {
        QDoubleSpinBox* source = ((QDoubleSpinBox*)m_layout->itemAtPosition(j, i)->widget());
        QDoubleSpinBox* target = ((QDoubleSpinBox*)m_layout->itemAtPosition(j + decal, i)->widget());
        target->setValue(source->value());
        source->setValue(m_min);
      }

    m_height = height;
    emit(heightChanged(m_height));
  }
  connect(m_signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(valueChanged(QObject*)));
}

void MatrixGenerator::setSize(int width, int height) {
  setWidth(width);
  setHeight(height);
}

void MatrixGenerator::setValue(int i, int j, double value) {
  ((QDoubleSpinBox*)m_layout->itemAtPosition(j, i)->widget())->setValue(value);
}


/** Methodes */
// Matrix<double>* MatrixGenerator::createMatrix() {
//   QDialog* dialog = new QDialog;

//   QHBoxLayout* controlsLayout = new QHBoxLayout;
  
//   QPushButton* pushButtonCancel = new QPushButton(tr("Cancel"));
//   QPushButton* pushButtonAccept = new QPushButton(tr("Accept"));

//   connect(pushButtonCancel, SIGNAL(clicked()), dialog, SLOT(reject()));
//   connect(pushButtonAccept, SIGNAL(clicked()), dialog, SLOT(accept()));

//   controlsLayout->addStretch();
//   controlsLayout->addWidget(pushButtonCancel);
//   controlsLayout->addWidget(pushButtonAccept);
//   controlsLayout->addStretch();

//   QVBoxLayout* layout = new QVBoxLayout;
//   layout->addWidget(this);
//   layout->addLayout(controlsLayout);

//   dialog->setLayout(layout);
//   dialog->resize(0, 0);
  
//   if (QDialog::Accepted == dialog->exec()) return m_matrix;
//   return NULL;
// }


/** Slots */
void MatrixGenerator::valueChanged(QObject* point) {
  int x = ((QPoint*)point)->x(), y = ((QPoint*)point)->y();
  emit(valueChanged(x, y, ((QDoubleSpinBox*)m_layout->itemAtPosition(x, y)->widget())->value()));
}

// void MatrixGenerator::refresh() {}

// void MatrixGenerator::modifyMatrix() {
//   for (int i = 0; i < m_matrix->getWidth(); i++)
//     for (int j = 0; j < m_matrix->getHeight(); j++) {
//       QDoubleSpinBox* spinBox = (QDoubleSpinBox*)m_matrixLayout->itemAtPosition(i, j)->widget();
//       m_matrix->setValue(i, j, (double)spinBox->value());
//     }
// }

// void MatrixGenerator::resizeMatrix() {
//   clear();
  
//   int width = m_matrix->getWidth(), height = m_matrix->getHeight();

//   if (width != m_spinBoxWidth->value()) width = m_spinBoxWidth->value();
//   if (height != m_spinBoxHeight->value()) height = m_spinBoxHeight->value();
      
//   Matrix<double>* tmp = new Matrix<double>(width, height);
//   for (int i = 0; i < width; i++)
//     for (int j = 0; j < height; j++) {
//       int i2 = i - (width - 1)/2 + (m_matrix->getWidth() - 1)/2;
//       int j2 = j - (height - 1)/2 + (m_matrix->getHeight() - 1)/2;
//       if (0 <= i2 && i2 < m_matrix->getWidth() && 0 <= j2 && j2 < m_matrix->getHeight())
//         tmp->setValue(i, j, m_matrix->getValue(i2, j2));
//       else tmp->setValue(i, j, 0);
//     }
//   delete m_matrix;
//   m_matrix = tmp;

//   for (int i = 0; i < m_matrix->getWidth(); i++)
//     for (int j = 0; j < m_matrix->getHeight(); j++) {
//       QDoubleSpinBox* spinBox = new QDoubleSpinBox();
//       spinBox->setValue(m_matrix->getValue(i, j));
//       spinBox->setRange(m_min, m_max);
//       connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(modifyMatrix()));
//       m_matrixLayout->addWidget(spinBox, i, j);
//     }

//   resize(0, 0);
// }


/** Methodes internes */
// QGroupBox* MatrixGenerator::createDimensionBox() {
//   QGroupBox* groupBox = new QGroupBox();
//   QHBoxLayout* layout = new QHBoxLayout();
  
//   layout->addStretch();
//   {
//     QLabel* label = new QLabel("Width");
//     m_spinBoxWidth = new QSpinBox();
//     m_spinBoxWidth->setMinimum(1);
//     m_spinBoxWidth->setValue(m_matrix->getWidth());
//     m_spinBoxWidth->setSingleStep(2);
//     connect(m_spinBoxWidth, SIGNAL(valueChanged(int)), this, SLOT(resizeMatrix()));
    
//     layout->addWidget(label);
//     layout->addWidget(m_spinBoxWidth);
//   }

//   {
//     QLabel* label = new QLabel("Height");
//     m_spinBoxHeight = new QSpinBox();
//     m_spinBoxHeight->setMinimum(1);
//     m_spinBoxHeight->setValue(m_matrix->getHeight());
//     m_spinBoxHeight->setSingleStep(2);
//     connect(m_spinBoxHeight, SIGNAL(valueChanged(int)), this, SLOT(resizeMatrix()));

//     layout->addWidget(label);
//     layout->addWidget(m_spinBoxHeight);
//   }
//   layout->addStretch();

//   groupBox->setLayout(layout);
//   return groupBox;
// }

// QGroupBox* MatrixGenerator::createMatrixBox() {
//   QGroupBox*  groupBox = new QGroupBox(tr("Matrix"));  
//   m_matrixLayout = new QGridLayout;

//   initialize();

//   groupBox->setLayout(m_matrixLayout);
//   return groupBox;
// }

// void MatrixGenerator::initialize() {
//   if (m_spinBoxWidth != NULL) m_spinBoxWidth->setValue(m_matrix->getWidth());
//   if (m_spinBoxHeight != NULL) m_spinBoxHeight->setValue(m_matrix->getHeight());

// }

// void MatrixGenerator::clear() {
//   int width = m_matrix->getWidth(), height = m_matrix->getHeight();

//   for (int i = 0; i < width; i++)
//     for (int j = 0; j < height; j++) {
//       QWidget* widget = m_matrixLayout->itemAtPosition(i, j)->widget();
//       m_matrixLayout->removeItem(m_matrixLayout->itemAtPosition(i, j));
//       delete m_matrixLayout->itemAtPosition(i, j);
//       delete widget;
//     }
// }
