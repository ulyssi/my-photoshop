#ifndef _MATRIX_HH_
#define _MATRIX_HH_

template <class T> class Matrix {
  
  /** Attributs */
  int m_width, m_height;
  T** m_data;

public:

  /** Constructeurs et destructeur */
  Matrix(int width, int height) :
    m_width(width),
    m_height(height)
  {
    m_data = new T*[m_width];
    for (int i = 0; i < m_width; i++) m_data[i] = new T[m_height];
  }

  Matrix(Matrix<T>* matrix) :
    m_width(matrix->m_width),
    m_height(matrix->m_height)
  {
    m_data = new T*[m_width];
    for (int i = 0; i < m_width; i++) {
      m_data[i] = new T[m_height];
      for (int j = 0; j < m_height; j++)
        m_data[i][j] = matrix->m_data[i][j];
    }
  }

  Matrix(int width, int height, T** data) :
    m_width(width),
    m_height(height)
  {
    m_data = new T*[m_width];
    for (int i = 0; i < m_width; i++) {
      m_data[i] = new T[m_height];
      for (int j = 0; j < m_height; j++)
        m_data[i][j] = data[i][j];
    }
  }

  ~Matrix() {
    for (int i = 0; i < m_width; i++) delete m_data[i];
    delete m_data;
  }


  /** Accesseurs */
  inline int getWidth() const { return m_width; }
  inline int getHeight() const { return m_height; }

  inline T& getValue(int i, int j) const { return m_data[i][j]; }
  T** getData() { return m_data; }
  
  /** Mutateurs */
  inline void setValue(int i, int j, T value) { m_data[i][j] = value; }
  //  void setValue(int i, int j, T& value) { m_data[i][j] = value; }
  
  void setData(Matrix<T>* matrix) {
    setData(matrix->m_width, matrix->m_height, matrix->m_data);
  }

  void setData(int width, int height, T** data) {
    delete m_data;
    m_width = width;
    m_height = height;
    m_data = new T*[m_width];
    for (int i = 0; i < m_width; i++) {
      m_data[i] = new T[m_height];
      for (int j = 0; j < m_height; j++)
	m_data[i][j] = data[i][j];
    }
  }
  

  /** Methodes */
  void initialize(T value) {
    for (int i = 0; i < m_width; i++) 
      for (int j = 0; j < m_height; j++)
	m_data[i][j] = value;
  }
  
  void resize(int width, int height, T value) {
    int decalX = width - m_width, decalY = height - m_height;
    
    T** data = new T*[width];
    for (int i = 0; i < width; i++) {
      data[i] = new T[height];
      for (int j = 0; j < height; j++) {
	if (0 <= i + decalX && i + decalX < m_width && 0 <= j + decalY && j + decalY < m_height)
	  data[i][j] = m_data[i+decalX][j+decalY];
	else 
	  data[i][j] = value;
      }
    }

    m_data = data;
    m_width = width;
    m_height = height;
  }


  //   T** data = 

  //   if (width < m_width) {
  //     int decal = (m_width - width) / 2;
  //     for (int i = decal; i < m_width; i++)
  // 	for (int j = 0; j < m_height; j++) {
  // 	  QDoubleSpinBox* source = ((QDoubleSpinBox*)m_layout->itemAtPosition(j, i)->widget());
  // 	  QDoubleSpinBox* target = ((QDoubleSpinBox*)m_layout->itemAtPosition(j, i - decal)->widget());
  // 	  target->setValue(source->value());
  // 	}

  //     for (int i = width; i < m_width; i++)
  // 	for (int j = 0; j < m_height; j++) {
  // 	  QWidget* widget = m_layout->itemAtPosition(j, i)->widget();
  // 	  m_layout->removeItem(m_layout->itemAtPosition(j, i));
  // 	  delete m_layout->itemAtPosition(j, i);
  // 	  delete widget;
  // 	}

  //     m_width = width;
  //     emit(widthChanged(m_width));
  //   }
  //   else if (m_width < width) {
  //     for (int i = m_width; i < width; i++)
  // 	for (int j = 0; j < m_height; j++) {
  // 	  QDoubleSpinBox* spinBox = new QDoubleSpinBox();
  // 	  spinBox->setValue(m_min);
  // 	  spinBox->setRange(m_min, m_max);
        
  // 	  m_signalMapper->setMapping((QObject*)spinBox, (QObject*)new QPoint(i, j));
  // 	  connect(spinBox, SIGNAL(valueChanged(double)), m_signalMapper, SLOT(map()));
        
  // 	  m_layout->addWidget(spinBox, j, i);
  // 	}

  //     int decal = (width - m_width) / 2;
  //     for (int i = m_width-1; i >= 0; i--)
  // 	for (int j = 0; j < m_height; j++) {
  // 	  QDoubleSpinBox* source = ((QDoubleSpinBox*)m_layout->itemAtPosition(j, i)->widget());
  // 	  QDoubleSpinBox* target = ((QDoubleSpinBox*)m_layout->itemAtPosition(j, i + decal)->widget());
  // 	  target->setValue(source->value());
  // 	  source->setValue(m_min);
  // 	}
  //   }
  // }

  static Matrix<T>* centrer(int w1, int h1, Matrix<T>* k) {
    int w = 1 + 2 * w1;
    int h = 1 + 2 * h1;
    Matrix<T>* kernel;
    int width = k->getWidth();
    int height = k->getHeight();
    if(w < width){
      if(h < height){
	kernel = new Matrix<T>(width, height);
      } else {
	kernel = new Matrix<T>(width, h);
      }
    } else { //w > = 3 
      if(h < height){
	kernel = new Matrix<T>(w, height);
      } else {
	kernel = new Matrix<T>(w, h);
      }
    }
    for (int i = 0; i < w; i++)
      for (int j = 0; j < h; j++) {
	kernel->setValue(i, j, 0.0);
	if (i >= i/width && i < i/width+width){
	  if (j >= j/height && j < j/height+height){
	    kernel->setValue(i, j, k->getValue(i-i/width,j-j/height));
	  } 
	}
      }
    return kernel;
  }
  
  
};

  
#endif
