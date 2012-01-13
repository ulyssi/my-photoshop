#include "AffineOperationChooser.hh"

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QSpacerItem>
#include <QSlider>
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
  m_scaleX(100), 
  m_scaleY(100), 
  m_alpha(0),
  m_pictureModifier(NULL),
  m_running(new QMutex)
{
  setAccessibleName(tr("AffineOp"));

  QSlider* scaleSliderX = new QSlider(Qt::Horizontal);
  scaleSliderX->setFocusPolicy(Qt::StrongFocus);
  scaleSliderX->setRange(0, 200);
  scaleSliderX->setTickInterval(200);
  scaleSliderX->setSingleStep(1);
  scaleSliderX->setValue(100);
  connect(scaleSliderX, SIGNAL(valueChanged(int)), this, SLOT(setValueScaleX(int)));

  QSlider* scaleSliderY = new QSlider(Qt::Horizontal);
  scaleSliderY->setFocusPolicy(Qt::StrongFocus);
  scaleSliderY->setRange(0, 200);
  scaleSliderY->setTickInterval(200);
  scaleSliderY->setSingleStep(1);
  scaleSliderY->setValue(100);
  connect(scaleSliderY, SIGNAL(valueChanged(int)), this, SLOT(setValueScaleY(int)));

  QVBoxLayout *scaleLayout = new QVBoxLayout;
  scaleLayout->addWidget(scaleSliderX);
  scaleLayout->addWidget(scaleSliderY);

  QGroupBox* scaleBox = new QGroupBox(QString("Scale"));
  scaleBox->setLayout(scaleLayout);

  QSlider* rotationSlider = new QSlider(Qt::Horizontal);
  rotationSlider->setRange(-360, 360);
  rotationSlider->setTickInterval(720);
  rotationSlider->setSingleStep(1);
  rotationSlider->setValue(0);
  connect(rotationSlider, SIGNAL(valueChanged(int)), this, SLOT(setValueRotation(int)));

  QVBoxLayout *rotationLayout = new QVBoxLayout;
  rotationLayout->addWidget(rotationSlider);
  
  QGroupBox* rotationBox = new QGroupBox(tr("Rotation"));
  rotationBox->setLayout(rotationLayout);

  QPushButton* pushButtonApply = new QPushButton(tr("Apply"));
  connect(pushButtonApply, SIGNAL(clicked()), this, SLOT(applyOperation()));
  
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(scaleBox);
  layout->addWidget(rotationBox);
  layout->addWidget(pushButtonApply);
  layout->addStretch();

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
  affinePreview();
}

void AffineOperationChooser::affinePreview() {
  Previewer* previewer = m_userInterface->getPreviewer();
  if (m_pictureModifier != NULL) {
    Picture* p = m_pictureModifier->getPicture();
    AffineTransformationOperation* op = new AffineTransformationOperation(p);
    op->setRescale(m_scaleX / 100.0, m_scaleY / 100.0);
    op->setRotationDegree(m_alpha);
    op->setCenter(p->getWidth()/2, p->getHeight()/2);
    previewer->setData(op->updatePreview());
  }
}


/** Slots */
void AffineOperationChooser::setValueScaleX(int scaleX) { m_scaleX = scaleX; refresh(); }

void AffineOperationChooser::setValueScaleY(int scaleY) { m_scaleY = scaleY; refresh(); }

void AffineOperationChooser::setValueRotation(int alpha) { m_alpha = alpha/2.0; refresh(); }

void AffineOperationChooser::applyOperation() {
  Picture* p = m_pictureModifier->getPicture();
  AffineTransformationOperation* op = new AffineTransformationOperation(p);
  op->setRescale(m_scaleX / 100.0, m_scaleY / 100.0);
  op->setRotationDegree(m_alpha);
  op->setCenter(p->getWidth()/2, p->getHeight()/2);
  p = op->applyOperation();
  p->refresh();
  m_pictureModifier->refresh();
}
