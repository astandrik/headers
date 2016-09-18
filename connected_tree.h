template<typename T>
struct tree_element {
  tree_element* parent;
  T elem;
  int rank;
  tree_element(T e) {
    elem = e;
    parent = this;
    rank = 0;
  }
  tree_element() {
    elem = 0;
    parent = this;
    rank = 0;
  }
  tree_element* Union(tree_element& e) {
    tree_element* a = find_set(this);
    tree_element* b = find_set(&e);
    if(a->rank > b->rank) {
      b->parent = a;
    } else {
      a->parent = b;
      if(rank == e.rank) {
          b->rank++;
      }
    }
    return parent;
  }
  static tree_element* find_set(tree_element* e);
  void print() {
    tree_element* current = this;
    printf("%d\n", current->elem);
    while(current != current->parent) {
      current = current->parent;
      printf("%d\n", current->elem);
    }
  }
};

template<typename T>
tree_element<T>* tree_element<T>::find_set(tree_element<T>* e)  {
  if (e != e->parent) {
    e->parent = find_set(e->parent);
  }
  return e->parent;
}