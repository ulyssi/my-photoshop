#include "UserInterface.hh"

#include "Histogram.hh"
#include "ColorChooser.hh"
#include "AffineOperationChooser.hh"
#include "RescaleOperationChooser.hh"
#include "ConvolveOperationChooser.hh"
#include "AlgebricOperationChooser.hh"
#include "ColorConvertOperationChooser.hh"


/** Accesseurs */
Histogram* UserInterface::getHistogram() { return m_histogram; }
ColorChooser* UserInterface::getColorChooser() { return m_colorChooser; }
AffineOperationChooser* UserInterface::getAffineOperationChooser() { return m_affineOperationChooser; }
RescaleOperationChooser* UserInterface::getRescaleOperationChooser() { return m_rescaleOperationChooser; }
ConvolveOperationChooser* UserInterface::getConvolveOperationChooser() { return m_convolveOperationChooser; }
AlgebricOperationChooser* UserInterface::getAlgebricOperationChooser() { return m_algebricOperationChooser; }
ColorConvertOperationChooser* UserInterface::getColorConvertOperationChooser() { return m_colorConvertOperationChooser; }


/** Methodes */
Histogram* UserInterface::createHistogram() { return new Histogram(); }
ColorChooser* UserInterface::createColorChooser() { return new ColorChooser(); }
AffineOperationChooser* UserInterface::createAffineOperationChooser() { return new AffineOperationChooser(); }
RescaleOperationChooser* UserInterface::createRescaleOperationChooser() { return new RescaleOperationChooser(); }
ConvolveOperationChooser* UserInterface::createConvolveOperationChooser() { return new ConvolveOperationChooser(); }
AlgebricOperationChooser* UserInterface::createAlgebricOperationChooser() { return new AlgebricOperationChooser(); }
ColorConvertOperationChooser* UserInterface::createColorConvertOperationChooser() { return new ColorConvertOperationChooser(); }


/** Methodes internes */
void UserInterface::createToolBoxDocks() {
  addDockWidget(Qt::LeftDockWidgetArea, m_histogramDock = createHistogramDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_colorChooserDock = createColorChooserDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_affineOperationChooserDock = createAffineOperationChooserDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_rescaleOperationChooserDock = createRescaleOperationChooserDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_convolveOperationChooserDock = createConvolveOperationChooserDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_algebricOperationChooserDock = createAlgebricOperationChooserDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_colorConvertOperationChooserDock = createColorConvertOperationChooserDock());
}

void UserInterface::updateToolBoxDocks() {
  if (m_histogram->isEnabled()) m_histogramDock->show(); else m_histogramDock->hide();
  if (m_colorChooser->isEnabled()) m_colorChooserDock->show(); else m_colorChooserDock->hide();
  if (m_affineOperationChooser->isEnabled()) m_affineOperationChooserDock->show(); else m_affineOperationChooserDock->hide();
  if (m_rescaleOperationChooser->isEnabled()) m_rescaleOperationChooserDock->show(); else m_rescaleOperationChooserDock->hide();
  if (m_convolveOperationChooser->isEnabled()) m_convolveOperationChooserDock->show(); else m_convolveOperationChooserDock->hide();
  if (m_algebricOperationChooser->isEnabled()) m_algebricOperationChooserDock->show(); else m_algebricOperationChooserDock->hide();
  if (m_colorConvertOperationChooser->isEnabled()) m_colorConvertOperationChooserDock->show(); else m_colorConvertOperationChooserDock->hide();
}

QDockWidget* UserInterface::createHistogramDock() {
  return createDockWidget(m_histogram = createHistogram()); 
}

QDockWidget* UserInterface::createColorChooserDock() { 
  return createDockWidget(m_colorChooser = createColorChooser());
}

QDockWidget* UserInterface::createAffineOperationChooserDock() { 
  return createDockWidget(m_affineOperationChooser = createAffineOperationChooser()); 
}

QDockWidget* UserInterface::createRescaleOperationChooserDock() {
  return createDockWidget(m_rescaleOperationChooser = createRescaleOperationChooser()); 
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
