// attention pas de destructeur... à voir
// enum binaire, greyscale, color

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
//---------- NEW MODIF
void Picture::addTracing(Tracing* tracing){
    // recalcul d'offset???
    tracing->setIndex(m_listTracing.size()); //size correspond à queue + 1
    m_listTracing.push_back(tracing);
}

void Picture::insertTracing(Tracing* tracing, int index){
  //insère un calque à la position indiquée par l'index
  // si l'index est pertinent
  int i(m_listTracing.size());
  if(index >= 0 && index <= i){
    m_listTracing.push_back(tracing); //après ajout, le i correspond plus à la taille mais à l'indice de queu donc pas de décrémentation
    Tracing *temp;
    temp = m_listTracing[i];
    while(i > index){
      m_listTracing[i] = m_listTracing[i-1];
      m_listTracing[i]->setIndex(i);
      i--;
    }
    m_listTracing[i] = temp;
    m_listTracing[i]->setIndex(i);
  } else cout << "index erroné, il doit être compris entre :" << "0 et " << i << endl;
}

void Picture::removeTracing(int index){
  // écrasement par déplacement
  int i(m_listTracing.size());
  if(index >= 0 && index < i){
    delete m_listTracing[index];
    m_listTracing[index] = 0; // <=> pointeur null
    int size = i;
    i = index;
    while (i < size-1){
      m_listTracing[i] = m_listTracing[i+1];
      m_listTracing[i]->setIndex(i);
      i++;
    }
    m_listTracing.pop_back(); //supression de la case inutile en queue
  } else cout << "index erroné, il doit être compris entre :" << "0 et " << i-1 << endl;
}

void Picture::removeTracing(Tracing *tracing){
  removeTracing(tracing->getIndex());
}