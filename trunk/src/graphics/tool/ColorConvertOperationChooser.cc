#include "ColorConvertOperationChooser.hh"

#include <QVBoxLayout>
#include <QPushButton>

#include "ColorConvertOperation.hh"
#include "UserInterface.hh"
#include "PictureModifier.hh"
#include "Previewer.hh"
#include "Picture.hh"
#include "MatrixGenerator.hh"


/** Constructeurs et destructeur */
ColorConvertOperationChooser::ColorConvertOperationChooser(UserInterface* userInterface) :
  m_userInterface(userInterface),
  m_pictureModifier(NULL)
{
  setAccessibleName(tr("ColorConvertOp"));
    
  m_kernel = new Matrix<double>(4, 4);
  m_kernel->initialize(0.0);
  for (int i = 0; i < 4; i++) m_kernel->setValue(i, i, 1.0);
    
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(createMatrixGroupBox());
  layout->addLayout(createControlsLayout());
  layout->addStretch();

  // resetOperation();
  setLayout(layout);
}

ColorConvertOperationChooser::~ColorConvertOperationChooser() {}


/** Mutateurs */
void ColorConvertOperationChooser::setPictureModifier(PictureModifier* pictureModifier) {
  m_pictureModifier = pictureModifier;
}


/** Methodes */
void ColorConvertOperationChooser::refresh() { 
  refreshPreview();
}


/** Slots */
void ColorConvertOperationChooser::modifyMatrix() {
  for (int i = 0; i < m_kernel->getWidth(); i++)
    for (int j = 0; j < m_kernel->getHeight(); j++) {
      QSpinBox* spinBox = (QSpinBox*)m_matrixLayout->itemAtPosition(i, j)->widget();
      m_kernel->setValue(i, j, (double)spinBox->value());
    }
}

void ColorConvertOperationChooser::resetOperation() {
  // m_kernel = new Matrix<double>(1, 1);
  // m_kernel->setValue(0, 0, 1.0);
}

void ColorConvertOperationChooser::refreshPreview() {}

void ColorConvertOperationChooser::applyOperation() {}


/** Methodes internes */
QGroupBox* ColorConvertOperationChooser::createMatrixGroupBox() {
  QGroupBox*  groupBox = new QGroupBox(tr("Matrix"));  
  m_matrixLayout = new QGridLayout;

  for (int i = 0; i < m_kernel->getWidth(); i++)
    for (int j = 0; j < m_kernel->getHeight(); j++) {
      QSpinBox* spinBox = new QSpinBox();
      spinBox->setValue(m_kernel->getValue(i, j));
      spinBox->setRange(-255, 255);
      connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(modifyMatrix()));
      m_matrixLayout->addWidget(spinBox, i, j);
    }

  groupBox->setLayout(m_matrixLayout);
  return groupBox;
}


QHBoxLayout* ColorConvertOperationChooser::createControlsLayout() {
  QHBoxLayout* layout = new QHBoxLayout();

  QPushButton* pushButtonRefresh = new QPushButton(tr("Refresh"));
  QPushButton* pushButtonReset = new QPushButton(tr("Reset"));
  QPushButton* pushButtonCustomized = new QPushButton(tr("Customize"));
  QPushButton* pushButtonApply = new QPushButton(tr("Apply"));
  
  connect(pushButtonRefresh, SIGNAL(clicked()), this, SLOT(refreshPreview()));
  connect(pushButtonReset, SIGNAL(clicked()), this, SLOT(resetOperation()));
  connect(pushButtonCustomized, SIGNAL(clicked()), this, SLOT(customize()));
  connect(pushButtonApply, SIGNAL(clicked()), this, SLOT(applyOperation()));

  layout->addWidget(pushButtonRefresh);
  layout->addWidget(pushButtonReset);
  layout->addWidget(pushButtonCustomized);
  layout->addWidget(pushButtonApply);
  
  return layout;
}
