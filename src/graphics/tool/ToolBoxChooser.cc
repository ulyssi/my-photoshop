#include "ToolBoxChooser.hh"

#include <QVBoxLayout>
#include <QPushButton>

#include "Picture.hh"
#include "Previewer.hh"
#include "UserInterface.hh"
#include "PictureModifier.hh"
#include "SeamCarvingOperation.hh"


/** Constructeurs et destructeur */
ToolBoxChooser::ToolBoxChooser(UserInterface* userInterface) :
  m_userInterface(userInterface),
  m_pictureModifier(NULL),
  m_seamCarvingOperation(NULL)
{
  setAccessibleName(tr("ToolBox"));
    
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(createSeamCarvingGroupBox());
  layout->addLayout(createControlsLayout());
  layout->addStretch();

  resetOperation();
  setLayout(layout);
}

ToolBoxChooser::~ToolBoxChooser() {}


/** Mutateurs */
void ToolBoxChooser::setPictureModifier(PictureModifier* pictureModifier) { 
  m_pictureModifier = pictureModifier; 
  if (m_pictureModifier != NULL) m_seamCarvingOperation = new SeamCarvingOperation(m_pictureModifier->getPicture());
  resetSeamCarvingOperation();
}


/** Methodes */
void ToolBoxChooser::refresh() {
  // refreshPreview(); 
}


/** Slots */
void ToolBoxChooser::modifySeamCarving() {
  refreshPreview();
}

void ToolBoxChooser::resetOperation() {
  resetSeamCarvingOperation();
}

void ToolBoxChooser::resetSeamCarvingOperation() {
  if (m_pictureModifier != NULL) {
    disconnect(m_sliderSeamCarvingSize, SIGNAL(valueChanged(int)), this, SLOT(modifySeamCarving()));

    int valueMax = 0;
    if (m_radioWidth->isChecked()) {
      valueMax = m_pictureModifier->getPicture()->getWidth();
      if (m_seamCarvingOperation != NULL) 
	m_seamCarvingOperation->setTargetHeight(m_pictureModifier->getPicture()->getHeight());
    }
    else {
      valueMax = m_pictureModifier->getPicture()->getHeight();
      if (m_seamCarvingOperation != NULL) 
	m_seamCarvingOperation->setTargetWidth(m_pictureModifier->getPicture()->getWidth());
    }
    
    m_sliderSeamCarvingSize->setRange(0, 2 * valueMax);
    m_sliderSeamCarvingSize->setValue(valueMax);
    m_spinBoxSeamCarvingSize->setRange(0, 2 * valueMax);
    m_spinBoxSeamCarvingSize->setValue(valueMax);

    connect(m_sliderSeamCarvingSize, SIGNAL(valueChanged(int)), this, SLOT(modifySeamCarving()));
    refreshPreview();
  }
}

void ToolBoxChooser::refreshPreview() {
  Previewer* previewer = m_userInterface->getPreviewer();
  if (m_pictureModifier != NULL) {
    if (m_seamCarvingOperation == NULL) m_seamCarvingOperation = new SeamCarvingOperation(m_pictureModifier->getPicture());
    if (m_radioWidth->isChecked()) m_seamCarvingOperation->setTargetWidth(m_sliderSeamCarvingSize->value());
    else m_seamCarvingOperation->setTargetHeight(m_sliderSeamCarvingSize->value());
    previewer->setData(m_seamCarvingOperation->updatePreview());
  }
}

void ToolBoxChooser::applyOperation() {
  if (m_pictureModifier != NULL) {
    Picture* picture = m_pictureModifier->getPicture();
    SeamCarvingOperation* op = new SeamCarvingOperation(picture);
    if (m_radioWidth->isChecked()) op->setTargetWidth(m_sliderSeamCarvingSize->value());
    else op->setTargetHeight(m_sliderSeamCarvingSize->value());
    picture = op->applyOperation();
    picture->refresh();
    m_pictureModifier->refresh();
    resetOperation();
  }
}


/** Methodes internes */
QGroupBox* ToolBoxChooser::createSeamCarvingGroupBox() {
  QGroupBox* groupBox = new QGroupBox(tr("Seam Carving"));
  QVBoxLayout* layout = new QVBoxLayout();

  m_spinBoxSeamCarvingSize = new QSpinBox();
  m_spinBoxSeamCarvingSize->setRange(1, 1000);
  m_spinBoxSeamCarvingSize->setSingleStep(1);

  m_sliderSeamCarvingSize = new QSlider(Qt::Horizontal);
  m_sliderSeamCarvingSize->setRange(1, 1000);
  m_sliderSeamCarvingSize->setTickInterval(10);
  m_sliderSeamCarvingSize->setSingleStep(1);

  connect(m_sliderSeamCarvingSize, SIGNAL(valueChanged(int)), this, SLOT(modifySeamCarving()));
  connect(m_spinBoxSeamCarvingSize, SIGNAL(valueChanged(int)), m_sliderSeamCarvingSize, SLOT(setValue(int)));
  connect(m_sliderSeamCarvingSize, SIGNAL(valueChanged(int)), m_spinBoxSeamCarvingSize, SLOT(setValue(int)));
  
  QHBoxLayout* layoutAxe = new QHBoxLayout();

  m_radioWidth = new QRadioButton(tr("Width"));
  m_radioWidth->setChecked(true);
  m_radioHeight = new QRadioButton(tr("Height"));

  connect(m_radioWidth, SIGNAL(toggled(bool)), this, SLOT(resetSeamCarvingOperation()));
  connect(m_radioHeight, SIGNAL(toggled(bool)), this, SLOT(resetSeamCarvingOperation()));

  layoutAxe->addWidget(m_radioWidth);
  layoutAxe->addWidget(m_radioHeight);
  layoutAxe->addWidget(m_spinBoxSeamCarvingSize);

  layout->addLayout(layoutAxe);
  layout->addWidget(m_sliderSeamCarvingSize);
  
  groupBox->setLayout(layout);
  return groupBox;
}

QHBoxLayout* ToolBoxChooser::createControlsLayout() {
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


