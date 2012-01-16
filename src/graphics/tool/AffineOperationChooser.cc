#include "AffineOperationChooser.hh"

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QGroupBox>
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
  m_scaleX(100), 
  m_scaleY(100), 
  m_alpha(0),
  m_pictureModifier(NULL)
{
  setAccessibleName(tr("AffineOp"));

  m_scaleSliderX->setFocusPolicy(Qt::StrongFocus);
  m_scaleSliderX->setRange(0, 200);
  m_scaleSliderX->setTickInterval(200);
  m_scaleSliderX->setSingleStep(1);
  connect(m_scaleSliderX, SIGNAL(valueChanged(int)), this, SLOT(setValueScaleX(int)));

  m_scaleSliderY->setFocusPolicy(Qt::StrongFocus);
  m_scaleSliderY->setRange(0, 200);
  m_scaleSliderY->setTickInterval(200);
  m_scaleSliderY->setSingleStep(1);
  connect(m_scaleSliderY, SIGNAL(valueChanged(int)), this, SLOT(setValueScaleY(int)));

  QVBoxLayout *scaleLayout = new QVBoxLayout;
  scaleLayout->addWidget(m_scaleSliderX);
  scaleLayout->addWidget(m_scaleSliderY);

  QGroupBox* scaleBox = new QGroupBox(QString("Scale"));
  scaleBox->setLayout(scaleLayout);

  m_rotationSlider->setRange(-360, 360);
  m_rotationSlider->setTickInterval(720);
  m_rotationSlider->setSingleStep(1);
  connect(m_rotationSlider, SIGNAL(valueChanged(int)), this, SLOT(setValueRotation(int)));

  QVBoxLayout *rotationLayout = new QVBoxLayout;
  rotationLayout->addWidget(m_rotationSlider);
  
  QGroupBox* rotationBox = new QGroupBox(tr("Rotation"));
  rotationBox->setLayout(rotationLayout);

  QPushButton* pushButtonApply = new QPushButton(tr("Apply"));
  connect(pushButtonApply, SIGNAL(clicked()), this, SLOT(applyOperation()));
  
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(scaleBox);
  layout->addWidget(rotationBox);
  layout->addWidget(pushButtonApply);
  layout->addStretch();
  
  initialize();
  setLayout(layout);
}

AffineOperationChooser::~AffineOperationChooser() {}


/** Mutateurs */
void AffineOperationChooser::setPictureModifier(PictureModifier* pictureModifier) { 
  m_pictureModifier = pictureModifier;
  refresh();
}


/** Methodes */
void AffineOperationChooser::initialize() {
  m_scaleSliderX->setValue(100);
  m_scaleSliderY->setValue(100);
  m_rotationSlider->setValue(0);
}

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
  m_alpha = alpha/2.0;
  refresh(); 
}

void AffineOperationChooser::applyOperation() {
  Picture* p = m_pictureModifier->getPicture();
  AffineTransformationOperation* op = new AffineTransformationOperation(p);
  op->setRescale(m_scaleX / 100.0, m_scaleY / 100.0);
  op->setRotationDegree(m_alpha);
  op->setCenter(p->getWidth()/2, p->getHeight()/2);
  p = op->applyOperation();
  p->refresh();
  m_pictureModifier->refresh();
  refresh();
  initialize();
}
