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
  m_pictureModifier(NULL),
  m_kernel(new Matrix<double>(4, 4)),
  m_greyScaleString(tr("Grey Scale")),
  m_sepiaString(tr("Sepia"))
{
  setAccessibleName(tr("ColorConvertOp"));

  m_kernel->initialize(0.0);
  for (int i = 0; i < 4; i++) m_kernel->setValue(i, i, 1.0);
      
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(createKernelGroupBox());
  layout->addWidget(m_matrixGenerator = new MatrixGenerator(m_kernel, false));
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
void ColorConvertOperationChooser::resetOperation() {
  // m_kernel = new Matrix<double>(1, 1);
  // m_kernel->setValue(0, 0, 1.0);
}

void ColorConvertOperationChooser::kernelSelection(int index) {
  QString text = m_kernelComboBox->itemText(index);
  if (text == m_greyScaleString) m_kernel = ColorConvertOperation::createGreyScaleKernel();
  else if (text == m_sepiaString) m_kernel = ColorConvertOperation::createSepiaKernel();
  m_matrixGenerator->setMatrix(m_kernel);
}

void ColorConvertOperationChooser::refreshPreview() {}

void ColorConvertOperationChooser::applyOperation() {}


/** Methodes internes */
QGroupBox* ColorConvertOperationChooser::createKernelGroupBox() {
  QGroupBox* groupBox = new QGroupBox(tr("Kernels"));  
  QGridLayout* layout = new QGridLayout;

  m_kernelComboBox = new QComboBox;
  m_kernelComboBox->addItem(m_greyScaleString);
  m_kernelComboBox->addItem(m_sepiaString);

  connect(m_kernelComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(kernelSelection(int)));

  layout->addWidget(m_kernelComboBox);

  groupBox->setLayout(layout);
  return groupBox;
}


QHBoxLayout* ColorConvertOperationChooser::createControlsLayout() {
  QHBoxLayout* layout = new QHBoxLayout();

  QPushButton* pushButtonRefresh = new QPushButton(tr("Refresh"));
  QPushButton* pushButtonReset = new QPushButton(tr("Reset"));
  QPushButton* pushButtonApply = new QPushButton(tr("Apply"));
  
  connect(pushButtonRefresh, SIGNAL(clicked()), this, SLOT(refreshPreview()));
  connect(pushButtonReset, SIGNAL(clicked()), this, SLOT(resetOperation()));
  connect(pushButtonApply, SIGNAL(clicked()), this, SLOT(applyOperation()));

  layout->addWidget(pushButtonRefresh);
  layout->addWidget(pushButtonReset);
  layout->addWidget(pushButtonApply);
  
  return layout;
}
