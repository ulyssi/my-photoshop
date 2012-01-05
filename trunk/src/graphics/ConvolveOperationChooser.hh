#ifndef _CONVOLVE_OPERATION_CHOOSER_HH_
#define _CONVOLVE_OPERATION_CHOOSER_HH_

#include <QLabel>
#include <QString>


class ConvolveOperationChooser : public QLabel { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  ConvolveOperationChooser();
  ~ConvolveOperationChooser();

  /** Accesseurs */
  const QString& getTabName() const;

private:

  /** Attributs */
  QString m_tabName;

};

#endif
