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
  
  static Matrix<T>* centrer(int w1, int h1, Matrix<T>* k){
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
