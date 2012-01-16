#include "ConvolveOperationChooser.hh"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QSlider>

#include "ConvolveOperation.hh"
#include "UserInterface.hh"
#include "PictureModifier.hh"


/** Constructeurs et destructeur */
ConvolveOperationChooser::ConvolveOperationChooser(UserInterface* userInterface) :
  m_userInterface(userInterface),
  m_pictureModifier(NULL)
{
  setAccessibleName(QString("ConvolveOp"));
  
  QGroupBox* blurBox = new QGroupBox(tr("Blur"));
  {
    QRadioButton* buttonAverageBlur = new QRadioButton(tr("Average Blur"));
    QRadioButton* buttonGaussianBlur = new QRadioButton(tr("Gaussian Blur"));
    QSlider* sliderBlurLevel = new QSlider(Qt::Horizontal);
    sliderBlurLevel->setRange(1, 5);
    sliderBlurLevel->setTickInterval(10);
    sliderBlurLevel->setSingleStep(1);
    
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(buttonAverageBlur);
    layout->addWidget(buttonGaussianBlur);
    layout->addWidget(sliderBlurLevel);
    blurBox->setLayout(layout);
  }

  QGroupBox* edgeDetectionBox = new QGroupBox(tr("Edge Detection"));
  {
    QRadioButton* buttonEdgeDetection = new QRadioButton(tr("Edge Detection"));
    QRadioButton* buttonLeftEdgeStrengthening = new QRadioButton(tr("Left Edge Strengthening"));
    QRadioButton* buttonRepulsing = new QRadioButton(tr("Repulsing"));
    
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(buttonEdgeDetection);
    layout->addWidget(buttonLeftEdgeStrengthening);
    layout->addWidget(buttonRepulsing);
    edgeDetectionBox->setLayout(layout);
  }

  QGroupBox* canalsBox = new QGroupBox(tr("Canals"));
  {
    QCheckBox* buttonRed = new QCheckBox(tr("Red"));
    QCheckBox* buttonGreen = new QCheckBox(tr("Green"));
    QCheckBox* buttonBlue = new QCheckBox(tr("Blue"));
    QCheckBox* buttonAlpha = new QCheckBox(tr("Alpha"));
    
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(buttonRed);
    layout->addWidget(buttonGreen);
    layout->addWidget(buttonBlue);
    layout->addWidget(buttonAlpha);
    canalsBox->setLayout(layout);
  }
  
  QPushButton* pushButtonReset = new QPushButton(tr("Reset"));
  connect(pushButtonReset, SIGNAL(clicked()), this, SLOT(initialize()));

  QPushButton* pushButtonApply = new QPushButton(tr("Apply"));
  connect(pushButtonApply, SIGNAL(clicked()), this, SLOT(applyOperation()));
  
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(blurBox);
  layout->addWidget(edgeDetectionBox);
  layout->addWidget(canalsBox);
  layout->addWidget(pushButtonReset);
  layout->addWidget(pushButtonApply);
  layout->addStretch();

  setLayout(layout);
}

ConvolveOperationChooser::~ConvolveOperationChooser() {}


/** Methodes */
void ConvolveOperationChooser::setPictureModifier(PictureModifier* pictureModifier) {
  m_pictureModifier = pictureModifier;
}

/** Slots */
void ConvolveOperationChooser::averageBlur() {
  
}

void ConvolveOperationChooser::gaussianBlur() {}

void ConvolveOperationChooser::initialize() {}

void ConvolveOperationChooser::applyOperation() {}

void ConvolveOperationChooser::refresh() { 
  refreshPreview();
}

void ConvolveOperationChooser::refreshPreview() {
  Previewer* previewer = m_userInterface->getPreviewer();
  if (m_pictureModifier != NULL) {
    Picture* p = m_pictureModifier->getPicture();
    // ConvolveOperation* op = new ConvolveOperation(p);
    // previewer->setData(op->updatePreview());
  }
}
