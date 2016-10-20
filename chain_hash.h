#include "double_linked_list.h"

template <typename T, typename K>
struct chained_hash {
  double_list<T, K>* chains;
  int size;
  int (*hash_function)(T, int);
  chained_hash(int n, int (*func)(T, int)) {
    hash_function = func;
    size = n;
    chains = new double_list<T,K>[n];
  }
  chained_hash<T, K>& insert(T element, K val) {
    int index = hash_function(element, size);
    chains[index].insert(element, val);
    return *this;
  }
  K* search(T element) {
    int index = hash_function(element, size);
    K* elem = chains[index].search(element);
    return elem;
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