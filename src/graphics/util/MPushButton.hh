#include <QPushButton>
class MPushButton : public QPushButton{ Q_OBJECT
public:
  MPushButton(int i);
  ~MPushButton();
  void setIndex(int i);
  int getIndex();
public slots: 
  void click();
signals:
  void clickedButton(int);
private:
  int m_index;
};
