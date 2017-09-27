#ifndef VEC_HH
#define VEC_HH

typedef int ElementType;

class Vector
{
public:
  Vector(int capacity = 10);
  ~Vector();
  ElementType at(int i); // Access the element at index i. No bounds checking
  int capacity(); // Number of elements the vector currently has
  int size(); // Number of values currently stored in the vector
  bool empty();//Returns true if and only if the vector contains no values
  void push_back(ElementType); // Append a value at the end of the vector
  void pop_back(); // Erase value at the end of the vector
  ElementType & front(); // Return a reference to vector's first element
  ElementType & back();  // Return a reference to vector's last element

private:
  int _entries; // Number of values currently stored
  int _cap;    // Number of elements the vector currently has
  ElementType *_data[];
};

Vector::Vector(int capacity)
{
  try {
    _data = new ElementType[capacity];
  }
  catch(bad_alloc & ba)
  {
    cerr << "Allocation exception." << endl;
  }
  _cap = capacity;
  _entries = 0;
}

Vector::~Vector()
{
  delete [] _data;
}

int Vector::capacity()
{
  return _cap;
}

int Vector::size()
{
  return _size;
}
