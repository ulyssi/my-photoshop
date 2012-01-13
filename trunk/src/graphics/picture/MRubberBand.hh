#ifndef _MRubberBand_HH_
#define _MRubberBand_HH_
#include <QRubberBand>
#include <QWidget>
class MRubberBand : public QRubberBand{ Q_OBJECT
public: 
  MRubberBand(QRubberBand::Shape,QWidget*);
  ~MRubberBand();
protected:
  /** override from QWidget**/
  void paintEvent ( QPaintEvent * );
  /**Attributs **/
  QColor m_border_color;
  QColor m_background_color;

};
#endif
