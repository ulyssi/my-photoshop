// attention pas de destructeur... à voir
// enum binaire, greyscale, color

#include "Picture.hh"
#include "PixelMod.hh"
#include "Tracing.hh"
#include "MergeOperation.hh"

using namespace std;

Picture::Picture(QString path) :
  m_path(path),
  m_tracingList()
{
  m_name = m_path.right(m_path.length()-1-m_path.lastIndexOf("/"));

  QImage image = loadQImage(m_path);
  m_data = new Matrix<unsigned int>(image.width(), image.height());
  for (int i = 0; i < getWidth(); i++)
    for (int j = 0; j < getHeight(); j++)
      m_data->setValue(i, j, (unsigned int)image.pixel(i, j));

  m_tracingList.push_back(new Tracing(m_data));
 
}

Picture::~Picture() {}

QString Picture::getPath() { return m_path;}

QString Picture::getName() { return m_name; }

int Picture::getWidth() { return m_data->getWidth(); }

int Picture::getHeight() { return m_data->getHeight(); }

Matrix<unsigned int>* Picture::getData() { return m_data; }

vector<Tracing*>& Picture::getTracingList() { return m_tracingList; }

Tracing* Picture::getBackground() { return m_tracingList[0]; }

void Picture::refresh() {
  std::cout<<"refreshing"<<std::endl;
  MergeOperation* m=new MergeOperation();
  Tracing *cTracing=m->doOperation(m_tracingList);
 

  if(cTracing->getWidth()!=getWidth()||cTracing->getHeight()!=getHeight()){
    delete m_data;
    m_data = new Matrix<unsigned int>(cTracing->getWidth(),cTracing->getHeight());
  }
  for (int i = 0; i<getWidth(); i++)
    for (int j = 0; j < getHeight(); j++)
      m_data->setValue(i, j, (unsigned int)cTracing->getValue(i, j));
  delete cTracing;
 
}

// Charge une image à partir de son path
QImage Picture::loadQImage(QString& path) {
  QImage temp = QImage(path);
  if(temp.isNull()) cout << "Error image.format -> QImage" << endl;
  return temp;
}

// sauvegarde une image à partir de son path, return true si succes
bool Picture::saveQImage(QString& path, QImage image){
    return image.save(path);
}

void Picture::addTracing(Tracing* tracing){
    // recalcul d'offset???
    tracing->setIndex(m_tracingList.size()); //size correspond à queue + 1
    m_tracingList.push_back(tracing);
}

void Picture::insertTracing(Tracing* tracing, int index){
  //insère un calque à la position indiquée par l'index
  // si l'index est pertinent
  int i(m_tracingList.size());
  if(index >= 0 && index <= i){
    m_tracingList.push_back(tracing); //après ajout, le i correspond plus à la taille mais à l'indice de queu donc pas de décrémentation
    Tracing *temp;
    temp = m_tracingList[i];
    while(i > index){
      m_tracingList[i] = m_tracingList[i-1];
      m_tracingList[i]->setIndex(i);
      i--;
    }
    m_tracingList[i] = temp;
    m_tracingList[i]->setIndex(i);
  } else cout << "index erroné, il doit être compris entre :" << "0 et " << i << endl;
}

void Picture::removeTracing(int index){
  // écrasement par déplacement
  int i(m_tracingList.size());
  if(index >= 0 && index < i){
    //delete m_tracingList[index];
    m_tracingList[index] = 0; // <=> pointeur null
    int size = i;
    i = index;
    while (i < size-1){
      m_tracingList[i] = m_tracingList[i+1];
      m_tracingList[i]->setIndex(i);
      i++;
    }
    m_tracingList.pop_back(); //supression de la case inutile en queue
  } else cout << "index erroné, il doit être compris entre :" << "0 et " << i-1 << endl;
}

void Picture::removeTracing(Tracing *tracing){
  removeTracing(tracing->getIndex());
}
