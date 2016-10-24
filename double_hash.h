#include <string.h>

template<typename T, typename K>
struct cell {
  bool isDeleted;
  bool isNull;
  T key;
  K element;
  cell() {
    isDeleted = false;
    isNull = true;
  }
};

template <typename T, typename K>
struct double_hash {
  cell<T,K>* cells;
  int size;
  int (*hash_function1)(T, int);
  int (*hash_function2)(T, int);
  double_hash(int m, int (*func1)(T, int), int (*func2)(T, int)) {
    hash_function1 = func1;
    hash_function2 = func2;
    size = m;
    cells = new cell<T,K>[m];
    //memset(cells, 0, sizeof(cell<T,K>) * m);
  }
  K* insert(T key, K value) {
    int h1 = hash_function1(key, size);
    int h2 = hash_function2(key, size);
    int i = 0;
    int index = (h1 + i * h2) % size;
    if(cells[index].isNull || cells[index].isDeleted) {
      cells[index].element = value;
      cells[index].isNull = false;
      cells[index].isDeleted = false;
      cells[index].key = key;
      return &cells[index].element;
    }
    while(!cells[index].isNull && !cells[index].isDeleted && i < size) {
      i++;
      index = (h1 + i * h2) % size;
    }
    if(i == size) {
      return NULL;
    } else {
      cells[index].key = key;
      cells[index].element = value;
      cells[index].isNull = false;
      cells[index].isDeleted = false;
      return &cells[index].element;
    }
  }
  K* search(T key) {
    int h1 = hash_function1(key, size);
    int h2 = hash_function2(key, size);
    int i = 0;
    int index = (h1 + i * h2) % size;
    if(cells[index].key == key && !cells[index].isDeleted) {
      return &cells[index].element;
    }
    while(!cells[index].isNull && i < size) {
      i++;
      index = (h1 + i * h2) % size;
      if(cells[index].key == key && !cells[index].isDeleted) {
        return &cells[index].element;
      }
    }
    return NULL;
  };
  K* operator[] (T elem) {
    return search(elem);
  }
  K* delete_(T key) {
    int h1 = hash_function1(key, size);
    int h2 = hash_function2(key, size);
    int i = 0;
    int index = (h1 + i * h2) % size;
    if(cells[index].key == key && !cells[index].isDeleted) {
      cells[index].isDeleted = true;
      return &cells[index].element;
    }
    while(!cells[index].isNull && i < size) {
      i++;
      index = (h1 + i * h2) % size;
      if(cells[index].key == key && !cells[index].isDeleted) {
        cells[index].isDeleted = true;
        return &cells[index].element;
      }
    }
    return NULL;
  }
};