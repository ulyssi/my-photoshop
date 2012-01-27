#include "ToolBoxChooser.hh"

#include <QVBoxLayout>
#include <QGridLayout>
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
  // if (m_seamCarvingOperation != NULL) {
  //   delete m_seamCarvingOperation;
  //   m_seamCarvingOperation = NULL;
  // }
  if (m_pictureModifier != NULL) {
    // m_seamCarvingOperation = new SeamCarvingOperation(m_pictureModifier->getPicture());
    disconnect(m_sliderSeamCarvingWidth, SIGNAL(valueChanged(int)), this, SLOT(modifySeamCarving()));
    disconnect(m_sliderSeamCarvingHeight, SIGNAL(valueChanged(int)), this, SLOT(modifySeamCarving()));

    int width = m_pictureModifier->getPicture()->getWidth();
    m_sliderSeamCarvingWidth->setRange(0, 2 * width);
    m_sliderSeamCarvingWidth->setValue(width);
    m_spinBoxSeamCarvingWidth->setRange(0, 2 * width);
    m_spinBoxSeamCarvingWidth->setValue(width);

    int height = m_pictureModifier->getPicture()->getHeight();
    m_sliderSeamCarvingHeight->setRange(0, 2 * height);
    m_sliderSeamCarvingHeight->setValue(height);
    m_spinBoxSeamCarvingHeight->setRange(0, 2 * height);
    m_spinBoxSeamCarvingHeight->setValue(height);

    connect(m_sliderSeamCarvingWidth, SIGNAL(valueChanged(int)), this, SLOT(modifySeamCarving()));
    connect(m_sliderSeamCarvingHeight, SIGNAL(valueChanged(int)), this, SLOT(modifySeamCarving()));
  }
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

void ToolBoxChooser::refreshPreview() {
  Previewer* previewer = m_userInterface->getPreviewer();
  // if (m_seamCarvingOperation != NULL) {
  if (m_pictureModifier != NULL) {
    if (m_seamCarvingOperation == NULL) m_seamCarvingOperation = new SeamCarvingOperation(m_pictureModifier->getPicture());
    // m_seamCarvingOperation->setTargetWidth(m_pictureModifier->getPicture()->getWidth() - 1);
    m_seamCarvingOperation->setTargetWidth(m_sliderSeamCarvingWidth->value());
    m_seamCarvingOperation->setTargetHeight(m_sliderSeamCarvingHeight->value());
    previewer->setData(m_seamCarvingOperation->updatePreview());
  }
}

void ToolBoxChooser::applyOperation() {}


/** Methodes internes */
QGroupBox* ToolBoxChooser::createSeamCarvingGroupBox() {
  QGroupBox* groupBox = new QGroupBox(tr("Seam Carving"));
  QGridLayout* layout = new QGridLayout();

  m_spinBoxSeamCarvingWidth = new QSpinBox();
  m_spinBoxSeamCarvingWidth->setRange(1, 1000);
  m_spinBoxSeamCarvingWidth->setSingleStep(1);

  m_sliderSeamCarvingWidth = new QSlider(Qt::Horizontal);
  m_sliderSeamCarvingWidth->setRange(1, 1000);
  m_sliderSeamCarvingWidth->setTickInterval(10);
  m_sliderSeamCarvingWidth->setSingleStep(1);

  m_spinBoxSeamCarvingHeight = new QSpinBox();
  m_spinBoxSeamCarvingHeight->setRange(1, 1000);
  m_spinBoxSeamCarvingHeight->setSingleStep(1);

  m_sliderSeamCarvingHeight = new QSlider(Qt::Horizontal);
  m_sliderSeamCarvingHeight->setRange(1, 1000);
  m_sliderSeamCarvingHeight->setTickInterval(10);
  m_sliderSeamCarvingHeight->setSingleStep(1);
  
  connect(m_sliderSeamCarvingWidth, SIGNAL(valueChanged(int)), this, SLOT(modifySeamCarving()));
  connect(m_sliderSeamCarvingHeight, SIGNAL(valueChanged(int)), this, SLOT(modifySeamCarving()));

  connect(m_spinBoxSeamCarvingWidth, SIGNAL(valueChanged(int)), m_sliderSeamCarvingWidth, SLOT(setValue(int)));
  connect(m_spinBoxSeamCarvingHeight, SIGNAL(valueChanged(int)), m_sliderSeamCarvingHeight, SLOT(setValue(int)));

  connect(m_sliderSeamCarvingWidth, SIGNAL(valueChanged(int)), m_spinBoxSeamCarvingWidth, SLOT(setValue(int)));
  connect(m_sliderSeamCarvingHeight, SIGNAL(valueChanged(int)), m_spinBoxSeamCarvingHeight, SLOT(setValue(int)));
  
  layout->addWidget(new QLabel(tr("Width")), 0, 0);
  layout->addWidget(m_sliderSeamCarvingWidth, 0, 1);
  layout->addWidget(m_spinBoxSeamCarvingWidth, 0, 2);

  layout->addWidget(new QLabel(tr("Height")), 1, 0);
  layout->addWidget(m_sliderSeamCarvingHeight, 1, 1);
  layout->addWidget(m_spinBoxSeamCarvingHeight, 1, 2);
  
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

void ToolBoxChooser::resetSeamCarvingOperation() {
}
