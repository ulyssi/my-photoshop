#include "MPushButton.hh"

MPushButton::MPushButton(int i ){
  m_index=i;
  QObject::connect(this,SIGNAL(clicked()),this,SLOT(click()));
}
MPushButton::~MPushButton(){}
  
void MPushButton::setIndex(int i){
  m_index=i;
}

int MPushButton::getIndex(){
  return m_index;
}

void MPushButton::click(){
  emit clickedButton(m_index);
}
