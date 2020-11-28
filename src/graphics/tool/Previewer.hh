#ifndef _PREVIEW_HH_
#define _PREVIEW_HH_

#include <QScrollArea>
#include <QLabel>

#include "../../model/Matrix.hh"

class PictureModifier;
class Picture;


class Previewer : public QScrollArea { Q_OBJECT

public:

  /** Constructeurs et destructeur */
  Previewer();
  ~Previewer();

  /** Mutateurs */
  void setPictureModifier(PictureModifier*);
  void setPicture(Picture*);
  void setData(Matrix<unsigned int>*);

  /** Predicats */
  bool isEnabled();

  /** Methodes */
  void refresh();

private:

  /** Attributs */
  PictureModifier* m_pictureModifier;
  Picture* m_picture;
  Matrix<unsigned int>* m_data;
  QLabel* m_imageLabel;

};

#endif
