#ifndef _USER_INTERFACE_HH_
#define _USER_INTERFACE_HH_

#include <QMainWindow>
#include <QApplication>
#include <QDockWidget>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QClipboard>
#include <QShortcut>
#include <QKeySequence>
#include <QStatusBar>
#include "Matrix.hh"

class Previewer;
class Histogram;
class ColorChooser;
class ToolBoxChooser;
class AffineOperationChooser;
class ConvolveOperationChooser;
class AlgebricOperationChooser;
class ColorConvertOperationChooser;

class TracingManager;
class PictureManager;
class TabWidget;


class UserInterface : public QMainWindow { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  UserInterface(QApplication*,QClipboard* );
  ~UserInterface();

  /** Accesseurs */
  
  Previewer* getPreviewer();
  Histogram* getHistogram();
  ColorChooser* getColorChooser();
  ToolBoxChooser* getToolBoxChooser();
  TracingManager* getTracingManager();
  AffineOperationChooser* getAffineOperationChooser();
  ConvolveOperationChooser* getConvolveOperationChooser();
  AlgebricOperationChooser* getAlgebricOperationChooser();
  ColorConvertOperationChooser* getColorConvertOperationChooser();
  QClipboard* getClipBoard();
  /** Methodes */
  void update();

  Previewer* createPreviewer();
  Histogram* createHistogram();
  ColorChooser* createColorChooser();
  ToolBoxChooser* createToolBoxChooser();
  TracingManager* createTracingManager();
  AffineOperationChooser* createAffineOperationChooser();
  ConvolveOperationChooser* createConvolveOperationChooser();
  AlgebricOperationChooser* createAlgebricOperationChooser();
  ColorConvertOperationChooser* createColorConvertOperationChooser();

public slots:

  /** Slots */
  void open();
  void save();
  void close(QWidget*);
 
  void exit();

  void undo();
  void redo();
  
  void cut();
  void copy();
  void paste();
  
  void crop();
  void select();
  void move();
  void resetEditionTool(int);
  
  void zoomIn();
  void zoomOut();
  void normalSize();
  void fitToWindow();
  void updateToolBoxDocks();

  void changeGIMode();
  void about();
  void print(QString);
        
private:

  /** Methodes internes */
  void colorConvertOperation(Matrix<double>*);
  void convolveOperation(Matrix<double>*);

  void createActions();
  void updateActions();
  void createMenuBar();
  void createToolBars();
  void createToolBoxDocks();
  TabWidget* createTabWidget();
  
  QDockWidget* createDockWidget(QWidget* widget);
  
  void createFileAction();
  void createEditAction();
  void createViewAction();
  void createHelpAction();
  void createAffineTransformationOperationAction();
  void createColorConvertOperationAction();
  void createConvolveOperationAction();
  void createAlgebricOperationAction();
  
  QMenu* createFileMenu();
  QMenu* createEditMenu();
  QMenu* createViewMenu();
  QMenu* createHelpMenu();
  
  QToolBar* createFileToolBar();
  QToolBar* createEditToolBar();
  QToolBar* createViewToolBar();
  QToolBar* createHelpToolBar();

  QDockWidget* createPreviewerDock();
  QDockWidget* createHistogramDock();
  QDockWidget* createColorChooserDock();
  QDockWidget* createToolBoxChooserDock();
  QDockWidget* createTracingManagerDock();
  QDockWidget* createAffineOperationChooserDock();
  QDockWidget* createConvolveOperationChooserDock();
  QDockWidget* createAlgebricOperationChooserDock();
  QDockWidget* createColorConvertOperationChooserDock();

  /** Attributs */
  QApplication* m_QApplication;
  QClipboard* m_clipboard;
  PictureManager* m_pictureManager;
  TabWidget* m_viewTabWidget;
  
  Previewer* m_previewer;
  Histogram* m_histogram;
  ColorChooser* m_colorChooser;
  ToolBoxChooser* m_toolBoxChooser;
  TracingManager* m_tracingManager;
  AffineOperationChooser* m_affineOperationChooser;
  ConvolveOperationChooser* m_convolveOperationChooser;
  AlgebricOperationChooser* m_algebricOperationChooser;
  ColorConvertOperationChooser* m_colorConvertOperationChooser;

  QMenu* m_fileMenu;
  QMenu* m_editMenu;
  QMenu* m_viewMenu;
  QMenu* m_helpMenu;
  
  QToolBar* m_fileToolBar;
  QToolBar* m_editToolBar;
  QToolBar* m_viewToolBar;
  QToolBar* m_helpToolBar;

  QDockWidget* m_previewerDock;
  QDockWidget* m_histogramDock;
  QDockWidget* m_colorChooserDock;
  QDockWidget* m_toolBoxChooserDock;
  QDockWidget* m_tracingManagerDock;
  QDockWidget* m_affineOperationChooserDock;
  QDockWidget* m_convolveOperationChooserDock;
  QDockWidget* m_algebricOperationChooserDock;
  QDockWidget* m_colorConvertOperationChooserDock;
  
  bool m_actionIconMod;
  
  QAction* m_copy;
  QAction* m_cut;
  QAction* m_paste;

  QAction* m_openAct;
  QAction* m_saveAct;
  QAction* m_exitAct;
  
  QAction* m_closeTab;

  QAction* m_undoAct;
  QAction* m_redoAct;

  QAction* m_zoomInAct;
  QAction* m_zoomOutAct;
  QAction* m_normalSizeAct;
  QAction* m_fitToWindowAct;
  QAction* m_selection;
  QAction* m_move;
  QAction* m_crop;
  
  QAction* m_guiMode;
  QAction* m_aboutAct;
  QAction* m_aboutQtAct;

};

#endif
