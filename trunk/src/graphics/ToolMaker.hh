#ifndef _TOOL_MAKER_HH_
#define _TOOL_MAKER_HH_

class ColorChooser;
// class BrushChooser;
// class HistogramModifier;
// class AffineOperationChooser;
// class RescaleOperationChooser;
// class ConvolveOperationChooser;
// class AlgebricOperationChooser;
// class ColorConvertOperationChooser;

class ToolMaker {

public:

  /** Constructeurs et destructeur */
  ToolMaker();
  ~ToolMaker();

  /** Accesseurs */
  ColorChooser* getDefaultColorChooser() const;
  // BrushChooser* getDefaultBrushChooser() const;
  // HistogramModifier* getDefaultHistogramModifier() const;
  // AffineOperationChooser* getDefaultAffineOperationChooser() const;
  // RescaleOperationChooser* getDefaultRescaleOperationChooser() const;
  // ConvolveOperationChooser* getDefaultConvolveOperationChooser() const;
  // AlgebricOperationChooser* getDefaultAlgebricOperationChooser() const;
  // ColorConvertOperationChooser* getDefaultColorConvertOperationChooser() const;

  /** Methodes */
  ColorChooser* createColorChooser();
  // BrushChooser* createBrushChooser();
  // HistogramModifier* createHistogramModifier();
  // AffineOperationChooser* createAffineOperationChooser();
  // RescaleOperationChooser* createRescaleOperationChooser();
  // ConvolveOperationChooser* createConvolveOperationChooser();
  // AlgebricOperationChooser* createAlgebricOperationChooser();
  // ColorConvertOperationChooser* createColorConvertOperationChooser();

private:

  /** Attributs */
  ColorChooser* m_colorChooser;
  // BrushChooser* m_brushChooser;
  // HistogramModifier* m_histogramModifier;
  // AffineOperationChooser* m_affineOperationChooser;
  // RescaleOperationChooser* m_rescaleOperationChooser;
  // ConvolveOperationChooser* m_convolveOperationChooser;
  // AlgebricOperationChooser* m_algebricOperationChooser;
  // ColorConvertOperationChooser* m_colorConvertOperationChooser;

};

#endif
