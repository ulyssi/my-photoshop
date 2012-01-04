#include <string>

class Picture {
  
public:

  /** Constructeurs et destructeur */
  Picture(std:string path);
  ~Picture();

  /** Accesseurs */
  QImage getImage() const;

private:

  /** Attributs */
  std::string m_path;

}
