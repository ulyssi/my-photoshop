#include "UserInterface.hh"

#include "tool/Histogram.hh"
#include "tool/Previewer.hh"
#include "tool/ColorChooser.hh"
#include "tool/TracingManager.hh"
#include "tool/ToolBoxChooser.hh"
#include "tool/AffineOperationChooser.hh"
#include "tool/ConvolveOperationChooser.hh"
#include "tool/ColorConvertOperationChooser.hh"
#include "tool/AlgebricOperationChooser.hh"


/** Accesseurs */
Previewer* UserInterface::getPreviewer() { return m_previewer; }
Histogram* UserInterface::getHistogram() { return m_histogram; }
ColorChooser* UserInterface::getColorChooser() { return m_colorChooser; }
ToolBoxChooser* UserInterface::getToolBoxChooser() { return m_toolBoxChooser; }
TracingManager* UserInterface::getTracingManager() { return m_tracingManager; }
AffineOperationChooser* UserInterface::getAffineOperationChooser() { return m_affineOperationChooser; }
ConvolveOperationChooser* UserInterface::getConvolveOperationChooser() { return m_convolveOperationChooser; }
AlgebricOperationChooser* UserInterface::getAlgebricOperationChooser() { return m_algebricOperationChooser; }
ColorConvertOperationChooser* UserInterface::getColorConvertOperationChooser() { return m_colorConvertOperationChooser; }


/** Methodes */
Previewer* UserInterface::createPreviewer() { return new Previewer(); }
Histogram* UserInterface::createHistogram() { return new Histogram(); }
ColorChooser* UserInterface::createColorChooser() { return new ColorChooser(); }
ToolBoxChooser* UserInterface::createToolBoxChooser() { return new ToolBoxChooser(this); }
TracingManager* UserInterface::createTracingManager() { return new TracingManager(); }
AffineOperationChooser* UserInterface::createAffineOperationChooser() { return new AffineOperationChooser(this); }
ConvolveOperationChooser* UserInterface::createConvolveOperationChooser() { return new ConvolveOperationChooser(this); }
AlgebricOperationChooser* UserInterface::createAlgebricOperationChooser() { return new AlgebricOperationChooser(); }
ColorConvertOperationChooser* UserInterface::createColorConvertOperationChooser() { return new ColorConvertOperationChooser(this); }


/** Methodes internes */
void UserInterface::createToolBoxDocks() {
  addDockWidget(Qt::LeftDockWidgetArea, m_affineOperationChooserDock = createAffineOperationChooserDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_convolveOperationChooserDock = createConvolveOperationChooserDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_algebricOperationChooserDock = createAlgebricOperationChooserDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_colorConvertOperationChooserDock = createColorConvertOperationChooserDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_toolBoxChooserDock = createToolBoxChooserDock());

  tabifyDockWidget(m_affineOperationChooserDock, m_convolveOperationChooserDock);
  tabifyDockWidget(m_affineOperationChooserDock, m_colorConvertOperationChooserDock);
  tabifyDockWidget(m_affineOperationChooserDock, m_algebricOperationChooserDock);
  tabifyDockWidget(m_affineOperationChooserDock, m_toolBoxChooserDock);

  addDockWidget(Qt::LeftDockWidgetArea, m_colorChooserDock = createColorChooserDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_histogramDock = createHistogramDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_tracingManagerDock = createTracingManagerDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_previewerDock = createPreviewerDock());

  tabifyDockWidget(m_histogramDock, m_tracingManagerDock);
  tabifyDockWidget(m_histogramDock, m_previewerDock);
}

void UserInterface::updateToolBoxDocks() {
  m_colorChooserDock->hide();
  m_algebricOperationChooserDock->hide();
}

QDockWidget* UserInterface::createPreviewerDock() {
  return createDockWidget(m_previewer = createPreviewer());
}

QDockWidget* UserInterface::createHistogramDock() {
  return createDockWidget(m_histogram = createHistogram());
}

QDockWidget* UserInterface::createColorChooserDock() {
  return createDockWidget(m_colorChooser = createColorChooser());
}

QDockWidget* UserInterface::createToolBoxChooserDock() {
  return createDockWidget(m_toolBoxChooser = createToolBoxChooser());
}

QDockWidget* UserInterface::createTracingManagerDock() {
  return createDockWidget(m_tracingManager = createTracingManager());
}

QDockWidget* UserInterface::createAffineOperationChooserDock() {
  return createDockWidget(m_affineOperationChooser = createAffineOperationChooser());
}

QDockWidget* UserInterface::createConvolveOperationChooserDock() {
  return createDockWidget(m_convolveOperationChooser = createConvolveOperationChooser());
}

QDockWidget* UserInterface::createAlgebricOperationChooserDock() {
  return createDockWidget(m_algebricOperationChooser = createAlgebricOperationChooser());
}

QDockWidget* UserInterface::createColorConvertOperationChooserDock() {
  return createDockWidget(m_colorConvertOperationChooser = createColorConvertOperationChooser());
}
