#include <Qstring>
#include <Qimage>
using namespace std;
class Picture {
  
public:

  /** Constructeurs et destructeur */
  Picture(Qstring path);
  ~Picture();

  /** Accesseurs */
  QImage& getImage() const;

private:

  /** Attributs */
  Qstring & m_path;
  Qimage image;

}
