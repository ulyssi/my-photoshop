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

  QSlider* rotationSlider = new QSlider(Qt::Horizontal);
  rotationSlider->setTickInterval(100);
  rotationSlider->setSingleStep(1);

  QVBoxLayout *rotationLayout = new QVBoxLayout;
  rotationLayout->addWidget(rotationSlider);

  QGroupBox* rotationBox = new QGroupBox(QString("Rotation"));
  rotationBox->setLayout(rotationLayout);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(scaleBox);
  layout->addWidget(rotationBox);
  layout->addStretch();

  setLayout(layout);
}

AffineOperationChooser::~AffineOperationChooser() {}
