#ifndef _OPERATION_CHOOSER_HH_
#define _OPERATION_CHOOSER_HH_

#include <QTabWidget>
#include <QString>

class AffineOperationChooser;
class RescaleOperationChooser;
class ConvolveOperationChooser;
class AlgebricOperationChooser;
class ColorConvertOperationChooser;


class OperationChooser : public QTabWidget { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  OperationChooser();
  ~OperationChooser();

  /** Accesseurs */
  const QString& getTabName() const;
  AffineOperationChooser* getAffineOperationChooser() const;
  RescaleOperationChooser* getRescaleOperationChooser() const;
  ConvolveOperationChooser* getConvolveOperationChooser() const;
  AlgebricOperationChooser* getAlgebricOperationChooser() const;
  ColorConvertOperationChooser* getColorConvertOperationChooser() const;

private:

  /** Attributs */
  QString m_tabName;
  AffineOperationChooser* m_affineOperationChooser;
  RescaleOperationChooser* m_rescaleOperationChooser;
  ConvolveOperationChooser* m_convolveOperationChooser;
  AlgebricOperationChooser* m_algebricOperationChooser;
  ColorConvertOperationChooser* m_colorConvertOperationChooser;

};

#endif
