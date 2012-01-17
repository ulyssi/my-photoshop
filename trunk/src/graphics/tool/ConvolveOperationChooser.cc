#include "ConvolveOperationChooser.hh"

#include <QVBoxLayout>
#include <QPushButton>

#include "ConvolveOperation.hh"
#include "UserInterface.hh"
#include "PictureModifier.hh"
#include "Previewer.hh"
#include "Picture.hh"


/** Constructeurs et destructeur */
ConvolveOperationChooser::ConvolveOperationChooser(UserInterface* userInterface) :
  m_userInterface(userInterface),
  m_pictureModifier(NULL)
{
  setAccessibleName(tr("ConvolveOp"));
    
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(createBlurGroupBox());
  layout->addWidget(createDetectionGroupBox());
  layout->addWidget(createCanalsGroupBox());
  layout->addLayout(createControlsLayout());
  layout->addStretch();

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
void ConvolveOperationChooser::modifyBlur() {
  resetDetectionOperation();
  
  if (m_buttonNoneBlur->isChecked()) {
    m_sliderBlurLevel->setEnabled(false);
    m_kernel = new Matrix<double>(1, 1);
    m_kernel->setValue(0, 0, 1.0);
  }
  else if (m_buttonAverageBlur->isChecked()) {
    m_sliderBlurLevel->setEnabled(true);
    m_kernel = new Matrix<double>(3, 3);
    double data[3][3] = {{ 1.00 , 1.00 , 1.00 },
			 { 1.00 , 1.00 , 1.00 },
			 { 1.00 , 1.00 , 1.00 }};
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
	m_kernel->setValue(i, j, (double)data[i][j]);
  }
  else if (m_buttonGaussianBlur->isChecked()) {
    m_sliderBlurLevel->setEnabled(true);
    m_kernel = new Matrix<double>(3, 3);
    double data[3][3] = {{ 1.00 , 2.00 , 1.00 },
			 { 2.00 , 4.00 , 2.00 },
			 { 1.00 , 2.00 , 1.00 }};
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
	m_kernel->setValue(i, j, (double)data[i][j]);
  }

  refreshPreview();
}

void ConvolveOperationChooser::modifyDetection() {
  resetBlurOperation();

  if (m_buttonNoneDetection->isChecked()) {
    m_sliderBlurLevel->setEnabled(false);
    m_kernel = new Matrix<double>(1, 1);
    m_kernel->setValue(0, 0, 1.0);
  }
  else if (m_buttonEdgeDetection->isChecked()) {
    m_kernel = new Matrix<double>(3, 3);
    double data[3][3] = {{ 0.00 , 1.00 , 0.00 },
			 { 1.00 , -4.00 , 1.00 },
			 { 0.00 , 1.00 , 0.00 }};
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
	m_kernel->setValue(i, j, (double)data[i][j]);
  }
  else if (m_buttonLeftEdgeStrengthening->isChecked()) {
    m_kernel = new Matrix<double>(3, 3);
    double data[3][3] = {{ 0.00 , 0.00 , 0.00 },
			 { -1.00 , 1.00 , 0.00 },
			 { 0.00 , 0.00 , 0.00 }};
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
	m_kernel->setValue(i, j, (double)data[i][j]);
  }
  else if (m_buttonRepulsing->isChecked()) {
    m_kernel = new Matrix<double>(3, 3);
    double data[3][3] = {{ -2.00 , -1.00 , 0.00 },
			 { -1.00 , 1.00 , 1.00 },
			 { 0.00 , 1.00 , 2.00 }};
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
	m_kernel->setValue(i, j, (double)data[i][j]);
  }

  refreshPreview();
}

void ConvolveOperationChooser::resetOperation() {
  resetBlurOperation();
  resetDetectionOperation();

  m_buttonCanalRed->setChecked(true);
  m_buttonCanalGreen->setChecked(true);
  m_buttonCanalBlue->setChecked(true);
  m_buttonCanalAlpha->setChecked(false);

  m_kernel = new Matrix<double>(1, 1);
  m_kernel->setValue(0, 0, 1.0);
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
QGroupBox* ConvolveOperationChooser::createBlurGroupBox() {
  QGroupBox* groupBox = new QGroupBox(tr("Blur"));
  QVBoxLayout* layout = new QVBoxLayout();

  m_buttonNoneBlur = new QRadioButton(tr("None"));
  m_buttonAverageBlur = new QRadioButton(tr("Average Blur"));
  m_buttonGaussianBlur = new QRadioButton(tr("Gaussian Blur"));
  m_sliderBlurLevel = new QSlider(Qt::Horizontal);
  m_sliderBlurLevel->setRange(1, 5);
  m_sliderBlurLevel->setTickInterval(10);
  m_sliderBlurLevel->setSingleStep(1);
  
  connect(m_buttonNoneBlur, SIGNAL(toggled(bool)), this, SLOT(modifyBlur()));
  connect(m_buttonAverageBlur, SIGNAL(toggled(bool)), this, SLOT(modifyBlur()));
  connect(m_buttonGaussianBlur, SIGNAL(toggled(bool)), this, SLOT(modifyBlur()));
  
  layout->addWidget(m_buttonNoneBlur);
  layout->addWidget(m_buttonAverageBlur);
  layout->addWidget(m_buttonGaussianBlur);
  layout->addWidget(m_sliderBlurLevel);
  
  groupBox->setLayout(layout);
  return groupBox;
}

QGroupBox* ConvolveOperationChooser::createDetectionGroupBox() {
  QGroupBox* groupBox = new QGroupBox(tr("Edge Detection"));
  QVBoxLayout* layout = new QVBoxLayout();

  m_buttonNoneDetection = new QRadioButton(tr("None"));
  m_buttonEdgeDetection = new QRadioButton(tr("Edge Detection"));
  m_buttonLeftEdgeStrengthening = new QRadioButton(tr("Left Edge Strengthening"));
  m_buttonRepulsing = new QRadioButton(tr("Repulsing"));

  connect(m_buttonNoneDetection, SIGNAL(toggled(bool)), this, SLOT(modifyDetection()));
  connect(m_buttonEdgeDetection, SIGNAL(toggled(bool)), this, SLOT(modifyDetection()));
  connect(m_buttonLeftEdgeStrengthening, SIGNAL(toggled(bool)), this, SLOT(modifyDetection()));
  connect(m_buttonRepulsing, SIGNAL(toggled(bool)), this, SLOT(modifyDetection()));
  
  layout->addWidget(m_buttonNoneDetection);
  layout->addWidget(m_buttonEdgeDetection);
  layout->addWidget(m_buttonLeftEdgeStrengthening);
  layout->addWidget(m_buttonRepulsing);
  
  groupBox->setLayout(layout);
  return groupBox;
}

QGroupBox* ConvolveOperationChooser::createCanalsGroupBox() {
  QGroupBox* groupBox = new QGroupBox(tr("Canals"));
  QHBoxLayout* layout = new QHBoxLayout();

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

QHBoxLayout* ConvolveOperationChooser::createControlsLayout() {
  QPushButton* pushButtonReset = new QPushButton(tr("Reset"));
  connect(pushButtonReset, SIGNAL(clicked()), this, SLOT(resetOperation()));

  QPushButton* pushButtonCustomized = new QPushButton(tr("Customize"));
  pushButtonCustomized->setEnabled(false);

  QPushButton* pushButtonApply = new QPushButton(tr("Apply"));
  connect(pushButtonApply, SIGNAL(clicked()), this, SLOT(applyOperation()));

  QHBoxLayout* layout = new QHBoxLayout();
  layout->addWidget(pushButtonReset);
  layout->addWidget(pushButtonCustomized);
  layout->addWidget(pushButtonApply);
  
  return layout;
}

void ConvolveOperationChooser::resetBlurOperation() {
  m_buttonNoneBlur->setChecked(true);
  m_buttonAverageBlur->setChecked(false);
  m_buttonGaussianBlur->setChecked(false);
  m_sliderBlurLevel->setValue(1);
  m_sliderBlurLevel->setEnabled(false);
}

void ConvolveOperationChooser::resetDetectionOperation() {
  m_buttonNoneDetection->setChecked(true);
  m_buttonEdgeDetection->setChecked(false);
  m_buttonLeftEdgeStrengthening->setChecked(false);
  m_buttonRepulsing->setChecked(false);
}
