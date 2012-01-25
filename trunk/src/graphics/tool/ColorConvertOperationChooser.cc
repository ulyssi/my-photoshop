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
  m_kernel(ColorConvertOperation::createIdentityKernel()),
  m_identityString(tr("Identity")),
  m_greyScaleString(tr("Grey Scale")),
  m_sepiaString(tr("Sepia"))
{
  setAccessibleName(tr("ColorConvertOp"));

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(createKernelGroupBox());
  layout->addWidget(createMatrixModifier());
  layout->addLayout(createControlsLayout());
  layout->addStretch();

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
void ColorConvertOperationChooser::setKernelValue(int i, int j, double value) {
  m_kernel->setValue(i, j, value);
}

void ColorConvertOperationChooser::kernelComboBoxChanged(int index) {
  QString text = m_kernelComboBox->itemText(index);
  if (text == m_identityString) m_kernel = ColorConvertOperation::createIdentityKernel();
  else if (text == m_greyScaleString) m_kernel = ColorConvertOperation::createGreyScaleKernel();
  else if (text == m_sepiaString) m_kernel = ColorConvertOperation::createSepiaKernel();

  disconnect(m_matrixGenerator, SIGNAL(valueChanged(int, int, double)), this, SLOT(setKernelValue(int, int, double)));
  for (int i = 0; i < m_kernel->getWidth(); i++)
    for (int j = 0; j < m_kernel->getHeight(); j++) 
      m_matrixGenerator->setValue(i, j, m_kernel->getValue(i, j));
  connect(m_matrixGenerator, SIGNAL(valueChanged(int, int, double)), this, SLOT(setKernelValue(int, int, double)));
}

void ColorConvertOperationChooser::resetOperation() {
  m_kernelComboBox->setCurrentIndex(0);
}

void ColorConvertOperationChooser::refreshPreview() {}

void ColorConvertOperationChooser::applyOperation() {}


/** Methodes internes */
QComboBox* ColorConvertOperationChooser::createKernelGroupBox() {
  m_kernelComboBox = new QComboBox();
  m_kernelComboBox->addItem(m_identityString);
  m_kernelComboBox->addItem(m_greyScaleString);
  m_kernelComboBox->addItem(m_sepiaString);
  connect(m_kernelComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(kernelComboBoxChanged(int)));
  return m_kernelComboBox;
}

MatrixGenerator* ColorConvertOperationChooser::createMatrixModifier() {
  m_matrixGenerator = new MatrixGenerator(m_kernel->getWidth(), m_kernel->getHeight());

  for (int i = 0; i < m_kernel->getWidth(); i++)
    for (int j = 0; j < m_kernel->getHeight(); j++) 
      m_matrixGenerator->setValue(i, j, m_kernel->getValue(i, j));

  connect(m_matrixGenerator, SIGNAL(valueChanged(int, int, double)), this, SLOT(setKernelValue(int, int, double)));

  return m_matrixGenerator;
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
