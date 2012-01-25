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
  layout->addWidget(createSettingsGroupBox());
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
void ColorConvertOperationChooser::minThresholdUpdate(int minThreshold) {
  if (m_spinBoxMaxThresholdRed->value() < m_spinBoxMinThresholdRed->value()) {
    disconnect(m_spinBoxMaxThresholdRed, SIGNAL(valueChanged(int)), this, SLOT(maxThresholdUpdate(int)));
    m_spinBoxMaxThresholdRed->setValue(m_spinBoxMinThresholdRed->value());
    connect(m_spinBoxMaxThresholdRed, SIGNAL(valueChanged(int)), this, SLOT(maxThresholdUpdate(int)));
  }

  if (m_spinBoxMaxThresholdGreen->value() < m_spinBoxMinThresholdGreen->value()) {
    disconnect(m_spinBoxMaxThresholdGreen, SIGNAL(valueChanged(int)), this, SLOT(maxThresholdUpdate(int)));
    m_spinBoxMaxThresholdGreen->setValue(m_spinBoxMinThresholdGreen->value());
    connect(m_spinBoxMaxThresholdGreen, SIGNAL(valueChanged(int)), this, SLOT(maxThresholdUpdate(int)));
  }

  if (m_spinBoxMaxThresholdBlue->value() < m_spinBoxMinThresholdBlue->value()) {
    disconnect(m_spinBoxMaxThresholdBlue, SIGNAL(valueChanged(int)), this, SLOT(maxThresholdUpdate(int)));
    m_spinBoxMaxThresholdBlue->setValue(m_spinBoxMinThresholdBlue->value());
    connect(m_spinBoxMaxThresholdBlue, SIGNAL(valueChanged(int)), this, SLOT(maxThresholdUpdate(int)));
  }
  
  emit(dataChanged());
}

void ColorConvertOperationChooser::maxThresholdUpdate(int maxThreshold) {
  if (m_spinBoxMaxThresholdRed->value() < m_spinBoxMinThresholdRed->value()) {
    disconnect(m_spinBoxMinThresholdRed, SIGNAL(valueChanged(int)), this, SLOT(minThresholdUpdate(int)));
    m_spinBoxMinThresholdRed->setValue(m_spinBoxMaxThresholdRed->value());
    connect(m_spinBoxMinThresholdRed, SIGNAL(valueChanged(int)), this, SLOT(minThresholdUpdate(int)));
  }

  if (m_spinBoxMaxThresholdGreen->value() < m_spinBoxMinThresholdGreen->value()) {
    disconnect(m_spinBoxMinThresholdGreen, SIGNAL(valueChanged(int)), this, SLOT(minThresholdUpdate(int)));
    m_spinBoxMinThresholdGreen->setValue(m_spinBoxMaxThresholdGreen->value());
    connect(m_spinBoxMinThresholdGreen, SIGNAL(valueChanged(int)), this, SLOT(minThresholdUpdate(int)));
  }

  if (m_spinBoxMaxThresholdBlue->value() < m_spinBoxMinThresholdBlue->value()) {
    disconnect(m_spinBoxMinThresholdBlue, SIGNAL(valueChanged(int)), this, SLOT(minThresholdUpdate(int)));
    m_spinBoxMinThresholdBlue->setValue(m_spinBoxMaxThresholdBlue->value());
    connect(m_spinBoxMinThresholdBlue, SIGNAL(valueChanged(int)), this, SLOT(minThresholdUpdate(int)));
  }
  emit(dataChanged());
}

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
  disconnect(m_spinBoxMinThresholdRed, SIGNAL(valueChanged(int)), this, SLOT(minThresholdUpdate(int)));
  disconnect(m_spinBoxMinThresholdGreen, SIGNAL(valueChanged(int)), this, SLOT(minThresholdUpdate(int)));
  disconnect(m_spinBoxMinThresholdBlue, SIGNAL(valueChanged(int)), this, SLOT(minThresholdUpdate(int)));

  disconnect(m_spinBoxMaxThresholdRed, SIGNAL(valueChanged(int)), this, SLOT(maxThresholdUpdate(int)));
  disconnect(m_spinBoxMaxThresholdGreen, SIGNAL(valueChanged(int)), this, SLOT(maxThresholdUpdate(int)));
  disconnect(m_spinBoxMaxThresholdBlue, SIGNAL(valueChanged(int)), this, SLOT(maxThresholdUpdate(int)));

  m_kernelComboBox->setCurrentIndex(0);
  m_spinBoxMaxThresholdRed->setValue(PixelMod::maxValue);
  m_spinBoxMaxThresholdGreen->setValue(PixelMod::maxValue);
  m_spinBoxMaxThresholdBlue->setValue(PixelMod::maxValue);

  m_spinBoxMinThresholdRed->setValue(PixelMod::minValue);
  m_spinBoxMinThresholdGreen->setValue(PixelMod::minValue);
  m_spinBoxMinThresholdBlue->setValue(PixelMod::minValue);

  connect(m_spinBoxMaxThresholdRed, SIGNAL(valueChanged(int)), this, SLOT(maxThresholdUpdate(int)));
  connect(m_spinBoxMaxThresholdGreen, SIGNAL(valueChanged(int)), this, SLOT(maxThresholdUpdate(int)));
  connect(m_spinBoxMaxThresholdBlue, SIGNAL(valueChanged(int)), this, SLOT(maxThresholdUpdate(int)));

  connect(m_spinBoxMinThresholdRed, SIGNAL(valueChanged(int)), this, SLOT(minThresholdUpdate(int)));
  connect(m_spinBoxMinThresholdGreen, SIGNAL(valueChanged(int)), this, SLOT(minThresholdUpdate(int)));
  connect(m_spinBoxMinThresholdBlue, SIGNAL(valueChanged(int)), this, SLOT(minThresholdUpdate(int)));

  connect(this, SIGNAL(dataChanged()), this, SLOT(refreshPreview()));
  emit(dataChanged());
}

void ColorConvertOperationChooser::refreshPreview() {
  Previewer* previewer = m_userInterface->getPreviewer();
  if (m_pictureModifier != NULL) {
    ColorConvertOperation* op = new ColorConvertOperation(m_pictureModifier->getPicture());
    op->setSeuilMin(PixelMod::RED, m_spinBoxMinThresholdRed->value());
    op->setSeuilMax(PixelMod::RED, m_spinBoxMaxThresholdRed->value());

    op->setSeuilMin(PixelMod::GREEN, m_spinBoxMinThresholdGreen->value());
    op->setSeuilMax(PixelMod::GREEN, m_spinBoxMaxThresholdGreen->value());

    op->setSeuilMin(PixelMod::BLUE, m_spinBoxMinThresholdBlue->value());
    op->setSeuilMax(PixelMod::BLUE, m_spinBoxMaxThresholdBlue->value());
    op->setKernel(m_kernel);
    previewer->setData(op->updatePreview());
  }
}

void ColorConvertOperationChooser::applyOperation() {
  if (m_pictureModifier != NULL) {
    Picture* picture = m_pictureModifier->getPicture();
    ColorConvertOperation* op = new ColorConvertOperation(m_pictureModifier->getPicture());
    op->setSeuilMin(PixelMod::RED, m_spinBoxMinThresholdRed->value());
    op->setSeuilMax(PixelMod::RED, m_spinBoxMaxThresholdRed->value());

    op->setSeuilMin(PixelMod::GREEN, m_spinBoxMinThresholdGreen->value());
    op->setSeuilMax(PixelMod::GREEN, m_spinBoxMaxThresholdGreen->value());

    op->setSeuilMin(PixelMod::BLUE, m_spinBoxMinThresholdBlue->value());
    op->setSeuilMax(PixelMod::BLUE, m_spinBoxMaxThresholdBlue->value());
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
  m_matrixGenerator->setRange(-99.99, 99.99);
  m_matrixGenerator->setSingleStep(0.01);

  for (int i = 0; i < m_kernel->getWidth(); i++)
    for (int j = 0; j < m_kernel->getHeight(); j++) 
      m_matrixGenerator->setValue(i, j, m_kernel->getValue(i, j));

  connect(m_matrixGenerator, SIGNAL(valueChanged(int, int, double)), this, SLOT(setKernelValue(int, int, double)));

  return m_matrixGenerator;
}

QGroupBox* ColorConvertOperationChooser::createSettingsGroupBox() {
  QGroupBox* groupBox = new QGroupBox(tr("Settings"));
  QGridLayout* layout = new QGridLayout();

  // m_spinBoxMinThreshold = new QSpinBox();
  // m_spinBoxMinThreshold->setRange(0, 255);
  // m_spinBoxMinThreshold->setValue(0);
  // m_spinBoxMinThreshold->setSingleStep(1);

  // m_spinBoxMaxThreshold = new QSpinBox();
  // m_spinBoxMaxThreshold->setRange(0, 255);
  // m_spinBoxMaxThreshold->setValue(255);
  // m_spinBoxMaxThreshold->setSingleStep(1);

  m_spinBoxMinThresholdRed = new QSpinBox();
  m_spinBoxMinThresholdRed->setRange(0, 255);
  m_spinBoxMinThresholdRed->setValue(0);
  m_spinBoxMinThresholdRed->setSingleStep(1);

  m_spinBoxMaxThresholdRed = new QSpinBox();
  m_spinBoxMaxThresholdRed->setRange(0, 255);
  m_spinBoxMaxThresholdRed->setValue(255);
  m_spinBoxMaxThresholdRed->setSingleStep(1);

  m_spinBoxMinThresholdGreen = new QSpinBox();
  m_spinBoxMinThresholdGreen->setRange(0, 255);
  m_spinBoxMinThresholdGreen->setValue(0);
  m_spinBoxMinThresholdGreen->setSingleStep(1);

  m_spinBoxMaxThresholdGreen = new QSpinBox();
  m_spinBoxMaxThresholdGreen->setRange(0, 255);
  m_spinBoxMaxThresholdGreen->setValue(255);
  m_spinBoxMaxThresholdGreen->setSingleStep(1);

  m_spinBoxMinThresholdBlue = new QSpinBox();
  m_spinBoxMinThresholdBlue->setRange(0, 255);
  m_spinBoxMinThresholdBlue->setValue(0);
  m_spinBoxMinThresholdBlue->setSingleStep(1);

  m_spinBoxMaxThresholdBlue = new QSpinBox();
  m_spinBoxMaxThresholdBlue->setRange(0, 255);
  m_spinBoxMaxThresholdBlue->setValue(255);
  m_spinBoxMaxThresholdBlue->setSingleStep(1);

  // connect(m_spinBoxMinThreshold, SIGNAL(valueChanged(int)), this, SLOT(minThresholdUpdate(int)));
  // connect(m_spinBoxMaxThreshold, SIGNAL(valueChanged(int)), this, SLOT(maxThresholdUpdate(int)));
  connect(m_spinBoxMinThresholdRed, SIGNAL(valueChanged(int)), this, SLOT(minThresholdUpdate(int)));
  connect(m_spinBoxMaxThresholdRed, SIGNAL(valueChanged(int)), this, SLOT(maxThresholdUpdate(int)));
  connect(m_spinBoxMinThresholdGreen, SIGNAL(valueChanged(int)), this, SLOT(minThresholdUpdate(int)));
  connect(m_spinBoxMaxThresholdGreen, SIGNAL(valueChanged(int)), this, SLOT(maxThresholdUpdate(int)));
  connect(m_spinBoxMinThresholdBlue, SIGNAL(valueChanged(int)), this, SLOT(minThresholdUpdate(int)));
  connect(m_spinBoxMaxThresholdBlue, SIGNAL(valueChanged(int)), this, SLOT(maxThresholdUpdate(int)));

  // layout->addWidget(new QLabel(tr("Threshold")), 0, 0);
  // layout->addWidget(m_spinBoxMinThreshold, 0, 1);
  // layout->addWidget(m_spinBoxMaxThreshold, 0, 2);

  layout->addWidget(new QLabel(tr("Threshold Red")), 1, 0);
  layout->addWidget(m_spinBoxMinThresholdRed, 1, 1);
  layout->addWidget(m_spinBoxMaxThresholdRed, 1, 2);

  layout->addWidget(new QLabel(tr("Threshold Green")), 2, 0);
  layout->addWidget(m_spinBoxMinThresholdGreen, 2, 1);
  layout->addWidget(m_spinBoxMaxThresholdGreen, 2, 2);

  layout->addWidget(new QLabel(tr("Threshold Blue")), 3, 0);
  layout->addWidget(m_spinBoxMinThresholdBlue, 3, 1);
  layout->addWidget(m_spinBoxMaxThresholdBlue, 3, 2);

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
