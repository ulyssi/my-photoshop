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
  m_customizeKernelString(tr("Customize")),
  m_extendControlString(tr("Extend")),
  m_cropControlString(tr("Crop")),
  m_wrapControlString(tr("Wrap")),
  m_timesOperatorString(tr("Times")),
  m_medianOperatorString(tr("Median")),
  m_maxOperatorString(tr("Maximum")),
  m_minOperatorString(tr("Minimum"))
{
  setAccessibleName(tr("ConvolveOp"));
    
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(createKernelGroupBox());
  layout->addLayout(createSettingsGroupBox());
  layout->addWidget(createMatrixModifier());
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
void ConvolveOperationChooser::kernelUpdate() {
  int width = (m_spinBoxWidth->value()-1)/2, height = (m_spinBoxHeight->value()-1)/2;

  QString text = m_kernelComboBox->itemText(m_kernelComboBox->currentIndex());
  if (text == m_identityKernelString) m_kernel = ConvolveOperation::createIdentityKernel(width, height);
  else if (text == m_averageBlurKernelString) m_kernel = ConvolveOperation::createAverageBlurKernel(width, height);
  else if (text == m_gaussianBlurKernelString) m_kernel = ConvolveOperation::createGaussianBlurKernel(width, height);
  else if (text == m_edgeDetectionKernelString) m_kernel = ConvolveOperation::createEdgeDetectionKernel(width, height);
  else if (text == m_leftEdgeStrengtheningKernelString) m_kernel = ConvolveOperation::createLeftEdgeStrengtheningKernel(width, height);
  else if (text == m_repulsingKernelString) m_kernel = ConvolveOperation::createRepulsingKernel(width, height);
  else m_kernel->resize(width * 2 + 1, height * 2 + 1, 0.0);

  disconnect(m_spinBoxWidth, SIGNAL(valueChanged(int)), this, SLOT(kernelUpdate()));
  disconnect(m_spinBoxHeight, SIGNAL(valueChanged(int)), this, SLOT(kernelUpdate()));
  disconnect(m_matrixModifier, SIGNAL(valueChanged(int, int, double)), this, SLOT(setKernelValue(int, int, double)));

  m_spinBoxWidth->setValue(m_kernel->getWidth());
  m_spinBoxHeight->setValue(m_kernel->getHeight());
  m_matrixModifier->setMatrix(m_kernel);
  
  connect(m_matrixModifier, SIGNAL(valueChanged(int, int, double)), this, SLOT(setKernelValue(int, int, double)));
  connect(m_spinBoxHeight, SIGNAL(valueChanged(int)), this, SLOT(kernelUpdate()));
  connect(m_spinBoxWidth, SIGNAL(valueChanged(int)), this, SLOT(kernelUpdate()));
  emit(dataChanged());
}

void ConvolveOperationChooser::setKernelValue(int i, int j, double value) {
  m_kernel->setValue(i, j, value);
  disconnect(this, SIGNAL(dataChanged()), this, SLOT(refreshPreview()));
  m_kernelComboBox->setCurrentIndex(m_kernelComboBox->count()-1);
  connect(this, SIGNAL(dataChanged()), this, SLOT(refreshPreview()));
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
    
    QString text = m_edgeControlComboBox->itemText(m_edgeControlComboBox->currentIndex());
    if (text == m_extendControlString) op->setEdgeControl(ConvolveOperation::EXTEND_EDGE);
    else if (text == m_cropControlString) op->setEdgeControl(ConvolveOperation::CROP_EDGE);
    else if (text == m_wrapControlString) op->setEdgeControl(ConvolveOperation::WRAP_EDGE);

    QString text2 = m_operatorComboBox->itemText(m_operatorComboBox->currentIndex());
    if (text2 == m_timesOperatorString) op->setOperator(ConvolveOperation::TIMES_OPERATOR);
    else if (text2 == m_medianOperatorString) op->setOperator(ConvolveOperation::MEDIAN_OPERATOR);
    else if (text2 == m_minOperatorString) op->setOperator(ConvolveOperation::MIN_OPERATOR);
    else if (text2 == m_maxOperatorString) op->setOperator(ConvolveOperation::MAX_OPERATOR);

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

    QString text = m_edgeControlComboBox->itemText(m_edgeControlComboBox->currentIndex());
    if (text == m_extendControlString) op->setEdgeControl(ConvolveOperation::EXTEND_EDGE);
    else if (text == m_cropControlString) op->setEdgeControl(ConvolveOperation::CROP_EDGE);
    else if (text == m_wrapControlString) op->setEdgeControl(ConvolveOperation::WRAP_EDGE);

    QString text2 = m_operatorComboBox->itemText(m_operatorComboBox->currentIndex());
    if (text2 == m_timesOperatorString) op->setOperator(ConvolveOperation::TIMES_OPERATOR);
    else if (text2 == m_medianOperatorString) op->setOperator(ConvolveOperation::MEDIAN_OPERATOR);
    else if (text2 == m_minOperatorString) op->setOperator(ConvolveOperation::MIN_OPERATOR);
    else if (text2 == m_maxOperatorString) op->setOperator(ConvolveOperation::MAX_OPERATOR);

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
  connect(m_kernelComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(kernelUpdate()));
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

  connect(m_buttonCanalRed, SIGNAL(stateChanged(int)), this, SLOT(refreshPreview()));
  connect(m_buttonCanalGreen, SIGNAL(stateChanged(int)), this, SLOT(refreshPreview()));
  connect(m_buttonCanalBlue, SIGNAL(stateChanged(int)), this, SLOT(refreshPreview()));
  connect(m_buttonCanalAlpha, SIGNAL(stateChanged(int)), this, SLOT(refreshPreview()));

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

  m_spinBoxWidth = new QSpinBox();
  m_spinBoxWidth->setRange(1, 99);
  m_spinBoxWidth->setValue(m_kernel->getWidth());
  m_spinBoxWidth->setSingleStep(2);
  
  m_spinBoxHeight = new QSpinBox();
  m_spinBoxHeight->setRange(1, 99);
  m_spinBoxHeight->setValue(m_kernel->getHeight());
  m_spinBoxHeight->setSingleStep(2);

  connect(m_spinBoxWidth, SIGNAL(valueChanged(int)), this, SLOT(kernelUpdate()));
  connect(m_spinBoxHeight, SIGNAL(valueChanged(int)), this, SLOT(kernelUpdate()));

  layout->addWidget(new QLabel(tr("Width")), 0, 0);
  layout->addWidget(m_spinBoxHeight, 0, 1);

  layout->addWidget(new QLabel(tr("Height")), 1, 0);
  layout->addWidget(m_spinBoxWidth, 1, 1);
  
  groupBox->setLayout(layout);
  return groupBox;
}

QHBoxLayout* ConvolveOperationChooser::createSettingsGroupBox() {
  QHBoxLayout* layout = new QHBoxLayout();

  m_edgeControlComboBox = new QComboBox();
  m_edgeControlComboBox->addItem(m_cropControlString);
  m_edgeControlComboBox->addItem(m_wrapControlString);
  m_edgeControlComboBox->addItem(m_extendControlString);

  m_operatorComboBox = new QComboBox();
  m_operatorComboBox->addItem(m_timesOperatorString);
  m_operatorComboBox->addItem(m_medianOperatorString);
  m_operatorComboBox->addItem(m_maxOperatorString);
  m_operatorComboBox->addItem(m_minOperatorString);

  connect(m_edgeControlComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(refreshPreview()));
  connect(m_operatorComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(refreshPreview()));

  QVBoxLayout* layoutBis = new QVBoxLayout();
  layoutBis->addWidget(createSizeGroupBox());
  layoutBis->addWidget(m_edgeControlComboBox);
  layoutBis->addWidget(m_operatorComboBox);
  
  layout->addWidget(createCanalsGroupBox());
  layout->addLayout(layoutBis);
  
  return layout;
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
