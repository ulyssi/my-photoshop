#include "ConvolveOperationChooser.hh"

#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QSlider>

#include "ConvolveOperation.hh"
#include "UserInterface.hh"
#include "PictureModifier.hh"
#include "Previewer.hh"
#include "Picture.hh"
#include "MatrixGenerator.hh"


/** Constructeurs et destructeur */
ConvolveOperationChooser::ConvolveOperationChooser(UserInterface* userInterface) :
  m_userInterface(userInterface),
  m_pictureModifier(NULL),
  m_kernel(ConvolveOperation::createIdentityKernel()),
  m_identityKernelString(tr("Identity")),
  m_averageBlurKernelString(tr("Average Blur")),
  m_gaussianBlurKernelString(tr("Gaussian Blur")),
  m_edgeDetectionKernelString(tr("Edge Detection")),
  m_leftEdgeStrengtheningKernelString(tr("Left Edge Strengthening")),
  m_repulsingKernelString(tr("Repulsing")),
  m_customizeKernelString(tr("Customize"))
{
  setAccessibleName(tr("ConvolveOp"));
    
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(createKernelGroupBox());
  layout->addWidget(createMatrixModifier());
  layout->addLayout(createSettingsGroupBox());
  layout->addLayout(createControlsLayout());
  layout->addStretch();

  connect(this, SIGNAL(dataChanged()), this, SLOT(refreshPreview()));

  resetOperation();
  setLayout(layout);
}

ConvolveOperationChooser::~ConvolveOperationChooser() {}


/** Mutateurs */
void ConvolveOperationChooser::setPictureModifier(PictureModifier* pictureModifier) {
  m_pictureModifier = pictureModifier;
}


/** Methodes */
void ConvolveOperationChooser::refresh() { 
  refreshPreview();
}


/** Slots */
void ConvolveOperationChooser::setKernelValue(int i, int j, double value) {
  m_kernel->setValue(i, j, value);
  disconnect(this, SIGNAL(dataChanged()), this, SLOT(refreshPreview()));
  m_kernelComboBox->setCurrentIndex(m_kernelComboBox->count()-1);
  connect(this, SIGNAL(dataChanged()), this, SLOT(refreshPreview()));
  emit(dataChanged());
}

void ConvolveOperationChooser::kernelComboBoxChanged(int index) {
  QString text = m_kernelComboBox->itemText(index);

  if (text == m_identityKernelString) m_kernel = ConvolveOperation::createIdentityKernel();
  else if (text == m_averageBlurKernelString) m_kernel = ConvolveOperation::createAverageBlurKernel();
  else if (text == m_gaussianBlurKernelString) m_kernel = ConvolveOperation::createGaussianBlurKernel();
  else if (text == m_edgeDetectionKernelString) m_kernel = ConvolveOperation::createEdgeDetectionKernel();
  else if (text == m_leftEdgeStrengtheningKernelString) m_kernel = ConvolveOperation::createLeftEdgeStrengtheningKernel();
  else if (text == m_repulsingKernelString) m_kernel = ConvolveOperation::createRepulsingKernel();

  disconnect(m_matrixModifier, SIGNAL(valueChanged(int, int, double)), this, SLOT(setKernelValue(int, int, double)));
  for (int i = 0; i < m_kernel->getWidth(); i++)
    for (int j = 0; j < m_kernel->getHeight(); j++) 
      m_matrixModifier->setValue(i, j, m_kernel->getValue(i, j));
  connect(m_matrixModifier, SIGNAL(valueChanged(int, int, double)), this, SLOT(setKernelValue(int, int, double)));
  emit(dataChanged());
}

void ConvolveOperationChooser::resetOperation() {
  disconnect(this, SIGNAL(dataChanged()), this, SLOT(refreshPreview()));
  m_kernelComboBox->setCurrentIndex(0);
  m_buttonCanalRed->setChecked(true);
  m_buttonCanalGreen->setChecked(true);
  m_buttonCanalBlue->setChecked(true);
  m_buttonCanalAlpha->setChecked(false);
  connect(this, SIGNAL(dataChanged()), this, SLOT(refreshPreview()));
  emit(dataChanged());
}

void ConvolveOperationChooser::refreshPreview() {
  Previewer* previewer = m_userInterface->getPreviewer();
  if (m_pictureModifier != NULL) {
    ConvolveOperation* op = new ConvolveOperation(m_pictureModifier->getPicture());
    op->setRed(m_buttonCanalRed->isChecked());
    op->setGreen(m_buttonCanalGreen->isChecked());
    op->setBlue(m_buttonCanalBlue->isChecked());
    op->setAlpha(m_buttonCanalAlpha->isChecked());
    op->setKernel(m_kernel);
    previewer->setData(op->updatePreview());
  }
}

void ConvolveOperationChooser::applyOperation() {
  if (m_pictureModifier != NULL) {
    Picture* picture = m_pictureModifier->getPicture();
    ConvolveOperation* op = new ConvolveOperation(picture);
    op->setRed(m_buttonCanalRed->isChecked());
    op->setGreen(m_buttonCanalGreen->isChecked());
    op->setBlue(m_buttonCanalBlue->isChecked());
    op->setAlpha(m_buttonCanalAlpha->isChecked());
    op->setKernel(m_kernel);
    picture = op->applyOperation();
    picture->refresh();
    m_pictureModifier->refresh();
    resetOperation();
  }
}


/** Methodes internes */
QComboBox* ConvolveOperationChooser::createKernelGroupBox() {
  m_kernelComboBox = new QComboBox();
  m_kernelComboBox->addItem(m_identityKernelString);
  m_kernelComboBox->insertSeparator(m_kernelComboBox->count());
  m_kernelComboBox->addItem(m_averageBlurKernelString);
  m_kernelComboBox->addItem(m_gaussianBlurKernelString);
  m_kernelComboBox->insertSeparator(m_kernelComboBox->count());
  m_kernelComboBox->addItem(m_edgeDetectionKernelString);
  m_kernelComboBox->addItem(m_leftEdgeStrengtheningKernelString);
  m_kernelComboBox->addItem(m_repulsingKernelString);
  m_kernelComboBox->insertSeparator(m_kernelComboBox->count());
  m_kernelComboBox->addItem(m_customizeKernelString);
  connect(m_kernelComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(kernelComboBoxChanged(int)));
  return m_kernelComboBox;
}

MatrixGenerator* ConvolveOperationChooser::createMatrixModifier() {
  m_matrixModifier = new MatrixGenerator(m_kernel->getWidth(), m_kernel->getHeight());
  m_matrixModifier->setRange(-255, 255);
  for (int i = 0; i < m_kernel->getWidth(); i++)
    for (int j = 0; j < m_kernel->getHeight(); j++) 
      m_matrixModifier->setValue(i, j, m_kernel->getValue(i, j));
  connect(m_matrixModifier, SIGNAL(valueChanged(int, int, double)), this, SLOT(setKernelValue(int, int, double)));
  return m_matrixModifier;
}

QGroupBox* ConvolveOperationChooser::createCanalsGroupBox() {
  QGroupBox* groupBox = new QGroupBox(tr("Canals"));
  QVBoxLayout* layout = new QVBoxLayout();

  m_buttonCanalRed = new QCheckBox(tr("Red"));
  m_buttonCanalGreen = new QCheckBox(tr("Green"));
  m_buttonCanalBlue = new QCheckBox(tr("Blue"));
  m_buttonCanalAlpha = new QCheckBox(tr("Alpha"));

  layout->addWidget(m_buttonCanalRed);
  layout->addWidget(m_buttonCanalGreen);
  layout->addWidget(m_buttonCanalBlue);
  layout->addWidget(m_buttonCanalAlpha);
  
  groupBox->setLayout(layout);
  return groupBox;
}

QGroupBox* ConvolveOperationChooser::createSizeGroupBox() {
  QGroupBox* groupBox = new QGroupBox(tr("Size"));
  QGridLayout* layout = new QGridLayout();

  QSpinBox* spinBoxWidth = new QSpinBox();
  spinBoxWidth->setRange(1, 5);
  spinBoxWidth->setValue(m_kernel->getWidth());
  spinBoxWidth->setSingleStep(2);
  
  QSpinBox* spinBoxHeight = new QSpinBox();
  spinBoxHeight->setRange(1, 5);
  spinBoxHeight->setValue(m_kernel->getHeight());
  spinBoxHeight->setSingleStep(2);

  connect(spinBoxWidth, SIGNAL(valueChanged(int)), m_matrixModifier, SLOT(setWidth(int)));
  //   connect(m_matrixModifier, SIGNAL(widthChanged(int)), spinBoxWidth, SLOT(setValue(int)));

  connect(spinBoxHeight, SIGNAL(valueChanged(int)), m_matrixModifier, SLOT(setHeight(int)));
  //  connect(m_matrixModifier, SIGNAL(heightChanged(int)), spinBoxHeight, SLOT(setValue(int)));

  layout->addWidget(new QLabel(tr("Width")), 0, 0);
  layout->addWidget(spinBoxWidth, 0, 1);

  layout->addWidget(new QLabel(tr("Height")), 1, 0);
  layout->addWidget(spinBoxHeight, 1, 1);
  
  groupBox->setLayout(layout);
  return groupBox;
}

QHBoxLayout* ConvolveOperationChooser::createSettingsGroupBox() {
  // QGroupBox* groupBox = new QGroupBox();
  QHBoxLayout* layout = new QHBoxLayout();

  QComboBox* edgeControlComboBox = new QComboBox();

  QVBoxLayout* layoutBis = new QVBoxLayout();
  layoutBis->addWidget(createSizeGroupBox());
  layoutBis->addWidget(edgeControlComboBox);
  
  layout->addWidget(createCanalsGroupBox());
  layout->addLayout(layoutBis);
  
  return layout;
  // groupBox->setLayout(layout);
  // return groupBox;
}

QHBoxLayout* ConvolveOperationChooser::createControlsLayout() {
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
