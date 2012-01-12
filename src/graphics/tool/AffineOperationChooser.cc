#include "AffineOperationChooser.hh"

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QSpacerItem>
#include <QLabel>
#include <QSlider>

/** Constructeurs et destructeur */
AffineOperationChooser::AffineOperationChooser() {
  setAccessibleName(QString("AffineOp"));

  QSlider* scaleSlider = new QSlider(Qt::Horizontal);
  scaleSlider->setFocusPolicy(Qt::StrongFocus);
  scaleSlider->setRange(-100, 100);
  scaleSlider->setTickInterval(100);
  scaleSlider->setSingleStep(1);

  QVBoxLayout *scaleLayout = new QVBoxLayout;
  scaleLayout->addWidget(scaleSlider);

  QGroupBox* scaleBox = new QGroupBox(QString("Scale"));
  scaleBox->setLayout(scaleLayout);

  QSlider* rotationSliderX = new QSlider(Qt::Horizontal);
  rotationSliderX->setTickInterval(100);
  rotationSliderX->setSingleStep(1);

  QSlider* rotationSliderY = new QSlider(Qt::Horizontal);
  rotationSliderY->setTickInterval(100);
  rotationSliderY->setSingleStep(1);

  QSlider* rotationSliderZ = new QSlider(Qt::Horizontal);
  rotationSliderZ->setTickInterval(100);
  rotationSliderZ->setSingleStep(1);

  QVBoxLayout *rotationLayout = new QVBoxLayout;
  rotationLayout->addWidget(rotationSliderX);
  rotationLayout->addWidget(rotationSliderY);
  rotationLayout->addWidget(rotationSliderZ);

  QGroupBox* rotationBox = new QGroupBox(QString("Rotation"));
  rotationBox->setLayout(rotationLayout);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(scaleBox);
  layout->addWidget(rotationBox);
  layout->addStretch();

  setLayout(layout);
}

AffineOperationChooser::~AffineOperationChooser() {}
