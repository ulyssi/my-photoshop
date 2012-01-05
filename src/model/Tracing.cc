#include "Tracing.hh"
#include <iostream>

  /*constructeur destructeur*/
Tracing::Tracing(int width,int height){
  this->m_width=width;
  this->m_height=height;
  std::cout<<m_width<<" raba "<<m_height<<std::endl;
  m_data=new unsigned int*[m_width];
  for(int i=0;i<m_width;++i){
    m_data[i]=new unsigned int[m_height];
  }
  m_alpha=0;
}

Tracing::Tracing(QImage source){
  
  this->m_width=source.width();
  this->m_height=source.height();
  m_data=new unsigned int*[m_width];
  for(int i=0;i<m_width;++i){
    m_data[i]=new unsigned int[m_height];
  }
  m_alpha=0;
  for(int i=0;i<m_width;i++)
    for(int j=0;j<m_height;j++){
      m_data[i][j]=(unsigned int)source.pixel(i,j);
    }
 

}



Tracing::~Tracing(){
  std::cout<<"destruction\n";
  for(int i=0;i<m_width;++i){
    delete m_data[i];
  }
  delete m_data;
  std::cout<<"destruction fini\n";
}

  /*accesseurs*/
int Tracing::getWidth(){return m_width;}

int Tracing::getHeight(){return m_height;}

int Tracing::getOffX(){return m_offX;}

int Tracing::getOffY(){return m_offY;}

int Tracing::getAlpha(){return m_alpha;} 
unsigned int Tracing::getPix(int x,int y){return m_data[x][y];} 




/*mutateurs*/

//void Tracing::setWidth(int){  m_width;}
//void Tracing::setHeight(int){  m_height;}
void Tracing::setOffX(int val){m_offX=val;}

void Tracing::setOffY(int val){ m_offY=val;}

void Tracing::setAlpha(int val){m_alpha=val;} 

void Tracing::setPix(int x,int y, unsigned int val ){ m_data[x][y]=val;} 
