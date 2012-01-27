#ifndef _TOOLBOX_CHOOSER_HH_
#define _TOOLBOX_CHOOSER_HH_

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QRadioButton>
#include <QSlider>

class UserInterface;
class PictureModifier;
class SeamCarvingOperation;


class ToolBoxChooser : public QWidget { Q_OBJECT

public:

  /** Constructeurs et destructeurs */
  ToolBoxChooser(UserInterface*);
  ~ToolBoxChooser();

  /** Mutateurs */
  void setPictureModifier(PictureModifier*);

  /** Methodes */
  void refresh();

public slots:

  /** Slots */
  void modifySeamCarving();
  void resetOperation();
  void refreshPreview();
  void applyOperation();
  void resetSeamCarvingOperation();

private:

  /** Methodes internes */
  QGroupBox* createSeamCarvingGroupBox();
  QHBoxLayout* createControlsLayout();

  /** Attributs */
  UserInterface* m_userInterface;
  PictureModifier* m_pictureModifier;
  QRadioButton *m_radioWidth, *m_radioHeight; 
  QSpinBox *m_spinBoxSeamCarvingSize;
  QSlider *m_sliderSeamCarvingSize;
  SeamCarvingOperation* m_seamCarvingOperation;

};

#endif
