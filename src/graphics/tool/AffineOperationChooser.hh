#ifndef _AFFINE_OPERATION_CHOOSER_HH_
#define _AFFINE_OPERATION_CHOOSER_HH_

#include <QLabel>
#include <QString>


class AffineOperationChooser : public QLabel { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  AffineOperationChooser();
  ~AffineOperationChooser();

  /** Accesseurs */
  const QString& getTabName() const;

private:

  /** Attributs */
  QString m_tabName;

};

#endif