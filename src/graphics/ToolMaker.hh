#ifndef _TOOL_MAKER_HH_
#define _TOOL_MAKER_HH_

class ColorChooser;
// class BrushChooser;
// class HistogramModifier;
class OperationChooser;
class AffineOperationChooser;
class RescaleOperationChooser;
class ConvolveOperationChooser;
class AlgebricOperationChooser;
class ColorConvertOperationChooser;

class ToolMaker {

public:

  /** Constructeurs et destructeur */
  ToolMaker();
  ~ToolMaker();

  /** Accesseurs */
  ColorChooser* getDefaultColorChooser() const;
  // BrushChooser* getDefaultBrushChooser() const;
  // HistogramModifier* getDefaultHistogramModifier() const;
  OperationChooser* getDefaultOperationChooser() const;
  AffineOperationChooser* getDefaultAffineOperationChooser() const;
  RescaleOperationChooser* getDefaultRescaleOperationChooser() const;
  ConvolveOperationChooser* getDefaultConvolveOperationChooser() const;
  AlgebricOperationChooser* getDefaultAlgebricOperationChooser() const;
  ColorConvertOperationChooser* getDefaultColorConvertOperationChooser() const;

  /** Methodes de classe */
  static ColorChooser* createColorChooser();
  // static BrushChooser* createBrushChooser();
  // static HistogramModifier* createHistogramModifier();
  static OperationChooser* createOperationChooser();
  static AffineOperationChooser* createAffineOperationChooser();
  static RescaleOperationChooser* createRescaleOperationChooser();
  static ConvolveOperationChooser* createConvolveOperationChooser();
  static AlgebricOperationChooser* createAlgebricOperationChooser();
  static ColorConvertOperationChooser* createColorConvertOperationChooser();

private:

  /** Attributs */
  ColorChooser* m_colorChooser;
  // BrushChooser* m_brushChooser;
  // HistogramModifier* m_histogramModifier;
  OperationChooser* m_operationChooser;
  AffineOperationChooser* m_affineOperationChooser;
  RescaleOperationChooser* m_rescaleOperationChooser;
  ConvolveOperationChooser* m_convolveOperationChooser;
  AlgebricOperationChooser* m_algebricOperationChooser;
  ColorConvertOperationChooser* m_colorConvertOperationChooser;

};

#endif
