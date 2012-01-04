#include "ColorChooser.hh"

#include <QString>
#include <QLabel>


ColorChooser::ColorChooser() {
  QLabel *label = new QLabel;
  label->setBackgroundRole(QPalette::Base);
  label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  label->setScaledContents(true);
  label->setText(QString("ColorChooser"));
  setWidget(label);
}

ColorChooser::~ColorChooser() {}
