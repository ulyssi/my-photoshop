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
    int vectX = (width - m_width)/2, vectY = (height - m_height)/2;
    
    T** data = new T*[width];
    for (int i = 0; i < width; i++) {
      data[i] = new T[height];
      for (int j = 0; j < height; j++) {
	if (0 <= i - vectX && i - vectX < m_width && 0 <= j - vectY && j - vectY < m_height)
	  data[i][j] = m_data[i - vectX][j - vectY];
	else data[i][j] = value;
      }
    }

    m_data = data;
    m_width = width;
    m_height = height;
  }
  
};

  
#endif
