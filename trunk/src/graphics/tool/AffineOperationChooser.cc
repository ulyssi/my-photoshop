#include "AffineOperationChooser.hh"

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QImage>
#include "Matrix.hh"

#include "Picture.hh"
#include "PictureModifier.hh"
#include "UserInterface.hh"
#include "AffineTransformationOperation.hh"
#include "Previewer.hh"


/** Constructeurs et destructeur */
AffineOperationChooser::AffineOperationChooser(UserInterface* userInterface) :
  m_userInterface(userInterface),
  m_scaleSliderX(new QSlider(Qt::Horizontal)),
  m_scaleSliderY(new QSlider(Qt::Horizontal)),
  m_rotationSlider(new QSlider(Qt::Horizontal)),
  m_buttonSymetrieNormal(new QRadioButton(tr("Normal"))),
  m_buttonSymetrieX(new QRadioButton(tr("Horizontal Symetrie"))),
  m_buttonSymetrieY(new QRadioButton(tr("Vertical Symetrie"))),
  m_buttonSymetrie(new QRadioButton(tr("Central Symetrie"))),
  m_symetrieNormal(true),
  m_symetrieX(false),
  m_symetrieY(false),
  m_symetrie(false),
  m_scaleX(100), 
  m_scaleY(100), 
  m_alpha(0),
  m_pictureModifier(NULL)
{
  setAccessibleName(tr("AffineOp"));
  
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(createScaleGroupBox());
  layout->addWidget(createRotationGroupBox());
  layout->addWidget(createSymetrieGroupBox());
  layout->addLayout(createControlsLayout());
  layout->addStretch();
  
  resetOperation();
  setLayout(layout);
}

AffineOperationChooser::~AffineOperationChooser() {}


/** Mutateurs */
void AffineOperationChooser::setPictureModifier(PictureModifier* pictureModifier) { 
  m_pictureModifier = pictureModifier;
  refresh();
}


/** Methodes */
void AffineOperationChooser::refresh() { 
  refreshPreview();
}

void AffineOperationChooser::refreshPreview() {
  Previewer* previewer = m_userInterface->getPreviewer();
  if (m_pictureModifier != NULL) {
    Picture* p = m_pictureModifier->getPicture();
    AffineTransformationOperation* op = new AffineTransformationOperation(p);
    op->setRescale(m_scaleX / 100.0, m_scaleY / 100.0);
    op->setRotationDegree(m_alpha);
    if (m_symetrieNormal) op->setSymetrie(false);
    else if (m_symetrieX) op->setSymetrieX(m_symetrieX);
    else if (m_symetrieY) op->setSymetrieY(m_symetrieY);
    else if (m_symetrie) op->setSymetrie(m_symetrie);
    op->setCenter(p->getWidth() / 2.0, p->getHeight() / 2.0);
    previewer->setData(op->updatePreview());
  }
}


/** Slots */
void AffineOperationChooser::setValueScaleX(int scaleX) {
  m_scaleX = scaleX;
  refresh(); 
}

void AffineOperationChooser::setValueScaleY(int scaleY) {
  m_scaleY = scaleY;
  refresh(); 
}

void AffineOperationChooser::setValueRotation(int alpha) {
  m_alpha = alpha;
  refresh(); 
}

void AffineOperationChooser::setValueSymetrieNormal(bool symetrieNormal) {
  m_symetrieNormal = symetrieNormal;
  refresh(); 
}

void AffineOperationChooser::setValueSymetrieX(bool symetrieX) {
  m_symetrieX = symetrieX;
  refresh(); 
}

void AffineOperationChooser::setValueSymetrieY(bool symetrieY) {
  m_symetrieY = symetrieY;
  refresh(); 
}

void AffineOperationChooser::setValueSymetrie(bool symetrie) {
  m_symetrie = symetrie;
  refresh(); 
}

void AffineOperationChooser::resetOperation() {
  m_scaleSliderX->setValue(100);
  m_scaleSliderY->setValue(100);
  m_rotationSlider->setValue(0);
  m_buttonSymetrieNormal->setChecked(true);
}

void AffineOperationChooser::applyOperation() {
  Picture* p = m_pictureModifier->getPicture();
  AffineTransformationOperation* op = new AffineTransformationOperation(p);
  op->setRescale(m_scaleX / 100.0, m_scaleY / 100.0);
  op->setRotationDegree(m_alpha);
  if (m_symetrieNormal) op->setSymetrie(false);
  else if (m_symetrieX) op->setSymetrieX(m_symetrieX);
  else if (m_symetrieY) op->setSymetrieY(m_symetrieY);
  else if (m_symetrie) op->setSymetrie(m_symetrie);
  op->setCenter(p->getWidth()/2, p->getHeight()/2);
  p = op->applyOperation();
  p->refresh();
  m_pictureModifier->refresh();
  resetOperation();
}


/** Methodes internes */
QGroupBox* AffineOperationChooser::createScaleGroupBox() {
  QGroupBox* groupBox = new QGroupBox(tr("Scale"));
  QGridLayout* layout = new QGridLayout;

  {
    QLabel* label = new QLabel(tr("Width"));
    m_scaleSliderX->setFocusPolicy(Qt::StrongFocus);
    m_scaleSliderX->setRange(0, 200);
    m_scaleSliderX->setTickInterval(200);
    m_scaleSliderX->setSingleStep(1);
    connect(m_scaleSliderX, SIGNAL(valueChanged(int)), this, SLOT(setValueScaleX(int)));
    layout->addWidget(label, 0, 0);
    layout->addWidget(m_scaleSliderX, 0, 1);
  }

  {
    QLabel* label = new QLabel(tr("Height"));
    m_scaleSliderY->setFocusPolicy(Qt::StrongFocus);
    m_scaleSliderY->setRange(0, 200);
    m_scaleSliderY->setTickInterval(200);
    m_scaleSliderY->setSingleStep(1);
    connect(m_scaleSliderY, SIGNAL(valueChanged(int)), this, SLOT(setValueScaleY(int)));
    layout->addWidget(label, 1, 0);
    layout->addWidget(m_scaleSliderY, 1, 1);
  }

  groupBox->setLayout(layout);
  return groupBox;
}

QGroupBox* AffineOperationChooser::createRotationGroupBox() {
  QGroupBox* groupBox = new QGroupBox(tr("Rotation"));
  QHBoxLayout* layout = new QHBoxLayout;

  {
    QLabel* label = new QLabel(tr("Angle"));
    m_rotationSlider->setRange(-180, 180);
    m_rotationSlider->setTickInterval(360);
    m_rotationSlider->setSingleStep(1);
    connect(m_rotationSlider, SIGNAL(valueChanged(int)), this, SLOT(setValueRotation(int)));
    layout->addWidget(label);
    layout->addWidget(m_rotationSlider);
  }
  
  groupBox->setLayout(layout);
  return groupBox;
}

QGroupBox* AffineOperationChooser::createSymetrieGroupBox() {
  QGroupBox* groupBox = new QGroupBox(tr("Symetrie"));
  QVBoxLayout *layout = new QVBoxLayout;

  connect(m_buttonSymetrieNormal, SIGNAL(toggled(bool)), this, SLOT(setValueSymetrieNormal(bool)));
  connect(m_buttonSymetrieX, SIGNAL(toggled(bool)), this, SLOT(setValueSymetrieX(bool)));
  connect(m_buttonSymetrieY, SIGNAL(toggled(bool)), this, SLOT(setValueSymetrieY(bool)));
  connect(m_buttonSymetrie, SIGNAL(toggled(bool)), this, SLOT(setValueSymetrie(bool)));
  
  layout->addWidget(m_buttonSymetrieNormal);
  layout->addWidget(m_buttonSymetrieX);
  layout->addWidget(m_buttonSymetrieY);
  layout->addWidget(m_buttonSymetrie);

  groupBox->setLayout(layout);
  return groupBox;
}

QHBoxLayout* AffineOperationChooser::createControlsLayout() {
  QHBoxLayout* layout = new QHBoxLayout();
  
  QPushButton* pushButtonReset = new QPushButton(tr("Reset"));
  connect(pushButtonReset, SIGNAL(clicked()), this, SLOT(resetOperation()));

  QPushButton* pushButtonCustomized = new QPushButton(tr("Customized"));
  pushButtonCustomized->setEnabled(false);

  QPushButton* pushButtonApply = new QPushButton(tr("Apply"));
  connect(pushButtonApply, SIGNAL(clicked()), this, SLOT(applyOperation()));

  layout->addWidget(pushButtonReset);
  layout->addWidget(pushButtonCustomized);
  layout->addWidget(pushButtonApply);

  return layout;
}
