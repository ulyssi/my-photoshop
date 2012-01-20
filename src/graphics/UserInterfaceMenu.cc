#include "UserInterface.hh"

#include <QMenuBar>



/** Methodes internes */
void UserInterface::createMenuBar() {
  menuBar()->addMenu(createFileMenu());
  menuBar()->addMenu(createEditMenu());
  menuBar()->addMenu(createViewMenu());
  menuBar()->addMenu(createOperationMenu());
  menuBar()->addMenu(createHelpMenu());
}

QMenu* UserInterface::createFileMenu() {
  m_fileMenu = new QMenu(tr("&File"), this);
  m_fileMenu->addAction(m_openAct);
  m_fileMenu->addAction(m_saveAct);
  m_fileMenu->addSeparator();
  m_fileMenu->addAction(m_exitAct);
  return m_fileMenu;
}

QMenu* UserInterface::createEditMenu() {
  m_editMenu = new QMenu(tr("&Edit"), this);
  m_editMenu->addAction(m_undoAct);
  m_editMenu->addAction(m_redoAct);
  m_fileMenu->addSeparator();
  m_editMenu->addAction(m_copy);
  m_editMenu->addAction(m_paste);
  m_editMenu->addAction(m_cut);
  return m_editMenu;
}

QMenu* UserInterface::createViewMenu() {
  m_viewMenu = new QMenu(tr("&View"), this);
  m_viewMenu->addAction(m_zoomInAct);
  m_viewMenu->addAction(m_zoomOutAct);
  m_viewMenu->addAction(m_normalSizeAct);
  m_viewMenu->addAction(m_fitToWindowAct);
  m_viewMenu->addSeparator();
  m_viewMenu->addAction(m_previewerAct);
  m_viewMenu->addAction(m_histogramAct);
  m_viewMenu->addAction(m_colorChooserAct);
  m_viewMenu->addAction(m_toolBoxChooserAct);
  m_viewMenu->addAction(m_tracingManagerAct);
  m_viewMenu->addAction(m_affineOperationAct);
  m_viewMenu->addAction(m_convolveOperationAct);
  m_viewMenu->addAction(m_algebricOperationAct);
  m_viewMenu->addAction(m_colorConvertOperationAct);
  return m_viewMenu;
}

QMenu* UserInterface::createHelpMenu() {
  m_helpMenu = new QMenu(tr("&Help"), this);
  m_helpMenu->addAction(m_aboutAct);
  m_helpMenu->addAction(m_aboutQtAct);
  return m_helpMenu;
}

QMenu* UserInterface::createOperationMenu() {
  m_operationMenu = new QMenu(tr("&Operation"), this);
  m_operationMenu->addMenu(createAffineTransformationOperationMenu());
  m_operationMenu->addMenu(createColorConvertOperationMenu());
  m_operationMenu->addMenu(createConvolveOperationMenu());
  m_operationMenu->addMenu(createAlgebricOperationMenu());
  return m_operationMenu;
}

QMenu* UserInterface::createAffineTransformationOperationMenu() {
  QMenu* menu = new QMenu(tr("Affine Transformation"), this);
  menu->addAction(m_rescaleAct);
  return menu;
}

QMenu* UserInterface::createColorConvertOperationMenu() {
  QMenu* menu = new QMenu(tr("Color Convert"), this);
  menu->addAction(m_greyScaleAct);
  menu->addAction(m_colorConvertAct);
  return menu;
}

QMenu* UserInterface::createConvolveOperationMenu() {
  QMenu* menu = new QMenu(tr("Convolve"), this);
  menu->addAction(m_increaseContrastAct);
  menu->addAction(m_averageBlurAct);
  menu->addAction(m_gaussianBlurAct);
  menu->addAction(m_leftEdgeStrengtheningAct);
  menu->addAction(m_edgeDetectionAct);
  menu->addAction(m_repulsingAct);
  menu->addAction(m_convolveAct);
  return menu;
}

QMenu* UserInterface::createAlgebricOperationMenu() {
  QMenu* menu = new QMenu(tr("Algebric"), this);
  return menu;
}
