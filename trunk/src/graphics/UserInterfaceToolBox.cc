#include "UserInterface.hh"

#include "Histogram.hh"
#include "Previewer.hh"
#include "ColorChooser.hh"
#include "TracingManager.hh"
#include "AffineOperationChooser.hh"
#include "ConvolveOperationChooser.hh"
#include "AlgebricOperationChooser.hh"
#include "ColorConvertOperationChooser.hh"


/** Accesseurs */
Previewer* UserInterface::getPreviewer() { return m_previewer; }
Histogram* UserInterface::getHistogram() { return m_histogram; }
ColorChooser* UserInterface::getColorChooser() { return m_colorChooser; }
TracingManager* UserInterface::getTracingManager() { return m_tracingManager; }
AffineOperationChooser* UserInterface::getAffineOperationChooser() { return m_affineOperationChooser; }
ConvolveOperationChooser* UserInterface::getConvolveOperationChooser() { return m_convolveOperationChooser; }
AlgebricOperationChooser* UserInterface::getAlgebricOperationChooser() { return m_algebricOperationChooser; }
ColorConvertOperationChooser* UserInterface::getColorConvertOperationChooser() { return m_colorConvertOperationChooser; }


/** Methodes */
Previewer* UserInterface::createPreviewer() { return new Previewer(); }
Histogram* UserInterface::createHistogram() { return new Histogram(); }
ColorChooser* UserInterface::createColorChooser() { return new ColorChooser(); }
TracingManager* UserInterface::createTracingManager() { return new TracingManager(); }
AffineOperationChooser* UserInterface::createAffineOperationChooser() { return new AffineOperationChooser(this); }
ConvolveOperationChooser* UserInterface::createConvolveOperationChooser() { return new ConvolveOperationChooser(); }
AlgebricOperationChooser* UserInterface::createAlgebricOperationChooser() { return new AlgebricOperationChooser(); }
ColorConvertOperationChooser* UserInterface::createColorConvertOperationChooser() { return new ColorConvertOperationChooser(); }


/** Methodes internes */
void UserInterface::createToolBoxDocks() {
  addDockWidget(Qt::LeftDockWidgetArea, m_affineOperationChooserDock = createAffineOperationChooserDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_convolveOperationChooserDock = createConvolveOperationChooserDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_algebricOperationChooserDock = createAlgebricOperationChooserDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_colorConvertOperationChooserDock = createColorConvertOperationChooserDock());
  
  tabifyDockWidget(m_affineOperationChooserDock, m_convolveOperationChooserDock);
  tabifyDockWidget(m_affineOperationChooserDock, m_algebricOperationChooserDock);
  tabifyDockWidget(m_affineOperationChooserDock, m_convolveOperationChooserDock);
  tabifyDockWidget(m_affineOperationChooserDock, m_colorConvertOperationChooserDock);

  addDockWidget(Qt::LeftDockWidgetArea, m_colorChooserDock = createColorChooserDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_histogramDock = createHistogramDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_tracingManagerDock = createTracingManagerDock());
  addDockWidget(Qt::LeftDockWidgetArea, m_previewerDock = createPreviewerDock());

  tabifyDockWidget(m_histogramDock, m_tracingManagerDock);
  tabifyDockWidget(m_histogramDock, m_previewerDock);
}

void UserInterface::updateToolBoxDocks() {
  if (m_previewerAct->isChecked() && m_previewer->isEnabled())
    m_previewerDock->show();
  else m_previewerDock->hide();

  if (m_histogramAct->isChecked() && m_histogram->isEnabled())
    m_histogramDock->show();
  else m_histogramDock->hide();
  
  if (m_colorChooserAct->isChecked() && m_colorChooser->isEnabled())
    m_colorChooserDock->show();
  else m_colorChooserDock->hide();
  
  if (m_tracingManagerAct->isChecked() && m_tracingManager->isEnabled())
    m_tracingManagerDock->show();
  else m_tracingManagerDock->hide();
  
  if (m_affineOperationAct->isChecked() && m_affineOperationChooser->isEnabled())
    m_affineOperationChooserDock->show();
  else m_affineOperationChooserDock->hide();
    
  if (m_convolveOperationAct->isChecked() && m_convolveOperationChooser->isEnabled())
    m_convolveOperationChooserDock->show();
  else m_convolveOperationChooserDock->hide();
  
  if (m_algebricOperationAct->isChecked() && m_algebricOperationChooser->isEnabled())
    m_algebricOperationChooserDock->show();
  else m_algebricOperationChooserDock->hide();
  
  if (m_colorConvertOperationAct->isChecked() && m_colorConvertOperationChooser->isEnabled())
    m_colorConvertOperationChooserDock->show();
  else m_colorConvertOperationChooserDock->hide();
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
