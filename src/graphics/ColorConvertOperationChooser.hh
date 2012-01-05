#ifndef _COLOR_CONVERT_OPERATION_CHOOSER_HH_
#define _COLOR_CONVERT_OPERATION_CHOOSER_HH_

#include <QLabel>
#include <QString>


class ColorConvertOperationChooser : public QLabel { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  ColorConvertOperationChooser();
  ~ColorConvertOperationChooser();

  /** Accesseurs */
  const QString& getTabName() const;

private:

  /** Attributs */
  QString m_tabName;

};

#endif
