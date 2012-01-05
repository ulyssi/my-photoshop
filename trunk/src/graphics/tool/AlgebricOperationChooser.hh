#ifndef _ALGEBRIC_OPERATION_CHOOSER_HH_
#define _ALGEBRIC_OPERATION_CHOOSER_HH_

#include <QLabel>
#include <QString>


class AlgebricOperationChooser : public QLabel { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  AlgebricOperationChooser();
  ~AlgebricOperationChooser();

  /** Accesseurs */
  const QString& getTabName() const;

private:

  /** Attributs */
  QString m_tabName;

};

#endif
