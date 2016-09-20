template<typename T>
struct Min_Heap {
  T** array;
  int size;
  Min_Heap(int s) {
    size = s;
    array = new T*[size];
  }
  Min_Heap(int s, int ss) {
    size = s;
    array = new T*[ss];
  }
  ~Min_Heap() {
    delete [] array;
  }
  static int left(int i) {
    return (i<<1) + 1;
  }
  static int right(int i) {
    return (i+1)<<1;
  }
  static int parent(int i) {
    return (i-1) >>1;
  }
  Min_Heap* insert_min(T* elem) {
    size++;
    array[size-1] = elem;
    int i = size -1;
    min_heapify(i);
    return this;
  }
  void min_heapify(T* a) {
    for(int i = 0; i < size; i++) {
      if(a == array[i]) {
        min_heapify(i);
        break;
      }
    }
  }
  void min_heapify(int i) {
    int p = parent(i);
    while(p >= 0 && *array[i] < *array[p]) {
      T* c = array[p];
      array[p] = array[i];
      array[i] = c;
      i = p;
      p = parent(i);
    }
  }
  void heapify_down(int i) {
    bool flag = true;
    while(flag) {
      int l = left(i);
      int r = right(i);
      int smallest = i;
      if(l < size && *array[l] < *array[i]) {
        smallest = l;
      }
      if(r < size && *array[r] < *array[smallest]) {
        smallest = r;
      }
      if(smallest != i) {
        T* c = array[smallest];
        array[smallest] = array[i];
        array[i] = c;
        i = smallest;
        flag = true;
      } else {
        flag = false;
      }
    }
  }
  T* extract_min() {
    T* c = array[size - 1];
    array[size-1] = array[0];
    array[0] = c;
    T* result = array[size-1];
    size--;
    heapify_down(0);
    return result;
  }
  void print() {
    for(int i = 0; i < size; i++) {
      printf("%d ", array[i]);
    }
    printf("\n");
  }
};

template<typename T>
Min_Heap<T> build_min_heap(T* array, int size) {
  Min_Heap<T> heap(size);
  for(int i = 0; i < size; i++) {
    heap.array[i] = &array[i];
  }
  int start = (((size-1)-1) >> 1) + 1;
  for(int i = start; i < size; i++) {
    heap.min_heapify(i);
  }
  return heap;
}