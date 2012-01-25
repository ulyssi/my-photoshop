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
  m_identityKernelString(tr("Identity")),
  m_greyScaleKernelString(tr("Grey Scale")),
  m_sepiaKernelString(tr("Sepia")),
  m_customizeKernelString(tr("Customize"))
{
  setAccessibleName(tr("ColorConvertOp"));

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(createKernelGroupBox());
  layout->addWidget(createMatrixModifier());
  layout->addLayout(createControlsLayout());
  layout->addStretch();

  connect(this, SIGNAL(dataChanged()), this, SLOT(refreshPreview()));

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
  disconnect(this, SIGNAL(dataChanged()), this, SLOT(refreshPreview()));
  m_kernelComboBox->setCurrentIndex(m_kernelComboBox->count()-1);
  connect(this, SIGNAL(dataChanged()), this, SLOT(refreshPreview()));
  emit(dataChanged());
}

void ColorConvertOperationChooser::kernelComboBoxChanged(int index) {
  QString text = m_kernelComboBox->itemText(index);
  if (text == m_identityKernelString) m_kernel = ColorConvertOperation::createIdentityKernel();
  else if (text == m_greyScaleKernelString) m_kernel = ColorConvertOperation::createGreyScaleKernel();
  else if (text == m_sepiaKernelString) m_kernel = ColorConvertOperation::createSepiaKernel();

  disconnect(m_matrixGenerator, SIGNAL(valueChanged(int, int, double)), this, SLOT(setKernelValue(int, int, double)));
  for (int i = 0; i < m_kernel->getWidth(); i++)
    for (int j = 0; j < m_kernel->getHeight(); j++) 
      m_matrixGenerator->setValue(i, j, m_kernel->getValue(i, j));
  connect(m_matrixGenerator, SIGNAL(valueChanged(int, int, double)), this, SLOT(setKernelValue(int, int, double)));
  emit(dataChanged());
}

void ColorConvertOperationChooser::resetOperation() {
  disconnect(this, SIGNAL(dataChanged()), this, SLOT(refreshPreview()));
  m_kernelComboBox->setCurrentIndex(0);
  connect(this, SIGNAL(dataChanged()), this, SLOT(refreshPreview()));
  emit(dataChanged());
}

void ColorConvertOperationChooser::refreshPreview() {
  Previewer* previewer = m_userInterface->getPreviewer();
  if (m_pictureModifier != NULL) {
    ColorConvertOperation* op = new ColorConvertOperation(m_pictureModifier->getPicture());
    op->setKernel(m_kernel);
    previewer->setData(op->updatePreview());
  }
}

void ColorConvertOperationChooser::applyOperation() {
  if (m_pictureModifier != NULL) {
    Picture* picture = m_pictureModifier->getPicture();
    ColorConvertOperation* op = new ColorConvertOperation(m_pictureModifier->getPicture());
    op->setKernel(m_kernel);
    picture = op->applyOperation();
    picture->refresh();
    m_pictureModifier->refresh();
    resetOperation();
  }
}


/** Methodes internes */
QComboBox* ColorConvertOperationChooser::createKernelGroupBox() {
  m_kernelComboBox = new QComboBox();
  m_kernelComboBox->addItem(m_identityKernelString);
  m_kernelComboBox->insertSeparator(m_kernelComboBox->count());
  m_kernelComboBox->addItem(m_greyScaleKernelString);
  m_kernelComboBox->addItem(m_sepiaKernelString);
  m_kernelComboBox->insertSeparator(m_kernelComboBox->count());
  m_kernelComboBox->addItem(m_customizeKernelString);
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
