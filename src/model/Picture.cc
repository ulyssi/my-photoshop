// attention pas de destructeur... à voir


#include "Picture.hh"
#include "util/FileManager.hh"

using namespace std;

Picture::Picture(QString path) :
  m_path(path),
  m_listTracing(3), 
  m_ch_rectX_sup(1),
  m_ch_rectX_inf(2),
  m_ch_rectY_sup(3),
  m_ch_rectY_inf(2)
{
  m_name = m_path.right(m_path.lastIndexOf("/"));
  m_image = loadQImage(m_path);
  m_width = m_image.width();
  m_height = m_image.height();
  m_listTracing.push_back(new Tracing(m_image));
 
}

QString Picture::getPath(){return m_path;}

QString Picture::getName(){return m_name;}

int Picture::getWidth(){return m_width;}

int Picture::getHeight(){return m_height;}

QImage& Picture::getImage(){
  if((m_ch_rectX_inf|m_ch_rectY_inf|m_ch_rectX_sup|m_ch_rectY_sup)!=0){
    /*todo make it real*/
    cout<<"make it real?\n";
    Tracing * tmp  =m_listTracing.back(); 
    for(int i=0;i<tmp->getWidth();i++){
      for(int j=0;j<tmp->getHeight();j++){
	if(i>50 && i<200&& j>50 && j<100){
	  m_image.setPixel(i,j,(uint)46544);
	}
	else{
	  m_image.setPixel(i,j,(uint)tmp->getPix(i,j));
	}
      }
    }    
  }cout<<"reading\n" << endl;
  return m_image;
}

vector<Tracing*>& Picture::getListTracing(){return m_listTracing;}

// Charge une image à partir de son path
QImage Picture::loadQImage(QString& path){
  QImage temp = QImage(path);
  if(temp.isNull()) cout << "Error image.format -> QImage" << endl;
  return temp;
}

// sauvegarde une image à partir de son path, return true si succes
bool Picture::saveQImage(QString& path, QImage image){
    return image.save(path);
}
