#ifndef _RESCALE_OPERATION_CHOOSER_HH_
#define _RESCALE_OPERATION_CHOOSER_HH_

#include <QLabel>
#include <QString>


class RescaleOperationChooser : public QLabel { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  RescaleOperationChooser();
  ~RescaleOperationChooser();

  /** Accesseurs */
  const QString& getTabName() const;

private:

  /** Attributs */
  QString m_tabName;

};

#endif
