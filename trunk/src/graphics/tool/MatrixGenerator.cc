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
  m_singleStep(1.0),
  m_layout(new QGridLayout()),
  m_signalMapper(new QSignalMapper())
{
  for (int i = 0; i < m_width; i++)
    for (int j = 0; j < m_height; j++) {
      QDoubleSpinBox* spinBox = new QDoubleSpinBox();
      spinBox->setValue(m_min);
      spinBox->setRange(m_min, m_max);
      spinBox->setSingleStep(m_singleStep);
       
      m_signalMapper->setMapping((QObject*)spinBox, (QObject*)new QPoint(i, j));
      connect(spinBox, SIGNAL(valueChanged(double)), m_signalMapper, SLOT(map()));

      m_layout->addWidget(spinBox, i, j);
    }
  connect(m_signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(valueChanged(QObject*)));
  setLayout(m_layout);
}

MatrixGenerator::~MatrixGenerator() {}


/** Accesseurs */
int MatrixGenerator::width() { return m_width; }

int MatrixGenerator::height() { return m_height; }

double MatrixGenerator::value(int i, int j) {
  return ((QDoubleSpinBox*)m_layout->itemAtPosition(i, j)->widget())->value();
}


/** Mutateurs */
void MatrixGenerator::setSingleStep(double singleStep) {
  m_singleStep = singleStep;
  for (int i = 0; i < m_width; i++)
    for (int j = 0; j < m_height; j++)
      ((QDoubleSpinBox*)m_layout->itemAtPosition(i, j)->widget())->setSingleStep(m_singleStep);
}

void MatrixGenerator::setMatrix(Matrix<double>* matrix) {
  setSize(matrix->getWidth(), matrix->getHeight());
  disconnect(m_signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(valueChanged(QObject*)));
  for (int i = 0; i < m_width; i++)
    for (int j = 0; j < m_height; j++)
      ((QDoubleSpinBox*)m_layout->itemAtPosition(i, j)->widget())->setValue(matrix->getValue(i, j));
  connect(m_signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(valueChanged(QObject*)));
}


/** Slots */
void MatrixGenerator::setMinimum(double min) { 
  m_min = min; 
  for (int i = 0; i < m_width; i++)
    for (int j = 0; j < m_height; j++)
      ((QDoubleSpinBox*)m_layout->itemAtPosition(i, j)->widget())->setMinimum(m_min);
}

void MatrixGenerator::setMaximum(double max) {
  m_max = max; 
  for (int i = 0; i < m_width; i++)
    for (int j = 0; j < m_height; j++)
      ((QDoubleSpinBox*)m_layout->itemAtPosition(i, j)->widget())->setMaximum(m_max);
}

void MatrixGenerator::setRange(double min, double max) {
  m_min = min;
  m_max = max;
  for (int i = 0; i < m_width; i++)
    for (int j = 0; j < m_height; j++)
      ((QDoubleSpinBox*)m_layout->itemAtPosition(i, j)->widget())->setRange(m_min, m_max);
}

void MatrixGenerator::setWidth(int width) {
  disconnect(m_signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(valueChanged(QObject*)));
  if (width < m_width) {
    int decal = (m_width - width) / 2;
    for (int i = decal; i < m_width; i++)
      for (int j = 0; j < m_height; j++) {
        QDoubleSpinBox* source = ((QDoubleSpinBox*)m_layout->itemAtPosition(i, j)->widget());
        QDoubleSpinBox* target = ((QDoubleSpinBox*)m_layout->itemAtPosition(i - decal, j)->widget());
        target->setValue(source->value());
      }

    for (int i = width; i < m_width; i++)
      for (int j = 0; j < m_height; j++) {
        QWidget* widget = m_layout->itemAtPosition(i, j)->widget();
        m_layout->removeItem(m_layout->itemAtPosition(i, j));
        delete m_layout->itemAtPosition(i, j);
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
	spinBox->setSingleStep(m_singleStep);
        
        m_signalMapper->setMapping((QObject*)spinBox, (QObject*)new QPoint(i, j));
        connect(spinBox, SIGNAL(valueChanged(double)), m_signalMapper, SLOT(map()));
        
        m_layout->addWidget(spinBox, i, j);
      }

    int decal = (width - m_width) / 2;
    for (int i = m_width-1; i >= 0; i--)
      for (int j = 0; j < m_height; j++) {
        QDoubleSpinBox* source = ((QDoubleSpinBox*)m_layout->itemAtPosition(i, j)->widget());
        QDoubleSpinBox* target = ((QDoubleSpinBox*)m_layout->itemAtPosition(i + decal, j)->widget());
        target->setValue(source->value());
        source->setValue(m_min);
      }

    m_width = width;
    emit(widthChanged(m_width));
  }
  connect(m_signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(valueChanged(QObject*)));
}


// void MatrixGenerator::setWidth(int width) {
//   disconnect(m_signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(valueChanged(QObject*)));
//   if (width < m_width) {
//     int decal = (m_width - width) / 2;
//     for (int i = decal; i < m_width; i++)
//       for (int j = 0; j < m_height; j++) {
//         QDoubleSpinBox* source = ((QDoubleSpinBox*)m_layout->itemAtPosition(i, j)->widget());
//         QDoubleSpinBox* target = ((QDoubleSpinBox*)m_layout->itemAtPosition(i - decal, j)->widget());
//         target->setValue(source->value());
//       }

//     for (int i = width; i < m_width; i++)
//       for (int j = 0; j < m_height; j++) {
//         QWidget* widget = m_layout->itemAtPosition(i, j)->widget();
//         m_layout->removeItem(m_layout->itemAtPosition(i, j));
//         delete m_layout->itemAtPosition(i, j);
//         delete widget;
//       }

//     m_width = width;
//     emit(widthChanged(m_width));
//   }
//   else if (m_width < width) {
//     for (int i = m_width; i < width; i++)
//       for (int j = 0; j < m_height; j++) {
//         QDoubleSpinBox* spinBox = new QDoubleSpinBox();
//         spinBox->setValue(m_min);
//         spinBox->setRange(m_min, m_max);
// 	spinBox->setSingleStep(m_singleStep);
        
//         m_signalMapper->setMapping((QObject*)spinBox, (QObject*)new QPoint(i, j));
//         connect(spinBox, SIGNAL(valueChanged(double)), m_signalMapper, SLOT(map()));
        
//         m_layout->addWidget(spinBox, i, j);
//       }

//     int decal = (width - m_width) / 2;
//     for (int i = m_width-1; i >= 0; i--)
//       for (int j = 0; j < m_height; j++) {
//         QDoubleSpinBox* source = ((QDoubleSpinBox*)m_layout->itemAtPosition(i, j)->widget());
//         QDoubleSpinBox* target = ((QDoubleSpinBox*)m_layout->itemAtPosition(i + decal, j)->widget());
//         target->setValue(source->value());
//         source->setValue(m_min);
//       }

//     m_width = width;
//     emit(widthChanged(m_width));
//   }
//   connect(m_signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(valueChanged(QObject*)));
// }

void MatrixGenerator::setHeight(int height) {
  disconnect(m_signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(valueChanged(QObject*)));
  if (height < m_height) {
    int decal = (m_height - height) / 2;
    for (int j = decal; j < m_height; j++)
      for (int i = 0; i < m_width; i++) {
        QDoubleSpinBox* source = ((QDoubleSpinBox*)m_layout->itemAtPosition(i, j)->widget());
        QDoubleSpinBox* target = ((QDoubleSpinBox*)m_layout->itemAtPosition(i, j - decal)->widget());
        target->setValue(source->value());
      }

    for (int j = height; j < m_height; j++)
      for (int i = 0; i < m_width; i++) {
        QWidget* widget = m_layout->itemAtPosition(i, j)->widget();
        m_layout->removeItem(m_layout->itemAtPosition(i, j));
        delete m_layout->itemAtPosition(i, j);
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
	spinBox->setSingleStep(m_singleStep);
	        
        m_signalMapper->setMapping((QObject*)spinBox, (QObject*)new QPoint(i, j));
        connect(spinBox, SIGNAL(valueChanged(double)), m_signalMapper, SLOT(map()));
        
        m_layout->addWidget(spinBox, i, j);
      }

    int decal = (height - m_height) / 2;
    for (int j = m_height-1; j >= 0; j--)
      for (int i = 0; i < m_width; i++) {
        QDoubleSpinBox* source = ((QDoubleSpinBox*)m_layout->itemAtPosition(i, j)->widget());
        QDoubleSpinBox* target = ((QDoubleSpinBox*)m_layout->itemAtPosition(i, j + decal)->widget());
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
  ((QDoubleSpinBox*)m_layout->itemAtPosition(i, j)->widget())->setValue(value);
}


/** Slots */
void MatrixGenerator::valueChanged(QObject* point) {
  int x = ((QPoint*)point)->x(), y = ((QPoint*)point)->y();
  emit(valueChanged(x, y, ((QDoubleSpinBox*)m_layout->itemAtPosition(x, y)->widget())->value()));
}
