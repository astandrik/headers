template<typename T, typename K>
struct Cell {
  bool isDeleted;
  bool isNull;
  T key;
  K element;
  Cell() {
    isNull = true;
    isDeleted = false;
  }
} cell;

template <typename T, typename K>
struct double_hash {
  Cell* cells;
  int size;
  int (*hash_function1)(T, int);
  int (*hash_function2)(T, int);
  double_hash(int m, int (*func1)(T, int), int (*func2)(T, int)) {
    hash_function1 = func1;
    hash_function2 = func2;
    size = m;
    cells = new Cell<K>[m];
  }
  chained_hash<T, K>& insert(T element, K val) {
    int index = hash_function(element, size);
    chains[index].insert(element, val);
    return *this;
  }
  K* search(T key) {
    int h1 = hash_function1(element, size);
    int h2 = hash_function2(element, size);
    int i = 0;
    int index = (h1 + i * h2) % size;
    if(cells[index].key == key) {
      return cells[index].element;
    }
    while(!cells[index].isNull && i < m) {
      i++;
      index = (h1 + i * h2) % size;
      if(cells[index].key == key) {
        return cells[index].element;
      }
    }
    return NULL;
  };
  K* operator[] (T elem) {
    return search(elem);
  }
  chained_hash<T,K>& delete_(T element) {
    int index = hash_function(element, size);
    chains[index].delete_(element);
    return &this;
  }
};