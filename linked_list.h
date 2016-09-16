template <typename T>
struct linked_list;

template <typename T>
struct Element {
  linked_list<T>* list;
  Element<T>* next;
  T elem;
  Element(T el) {
    elem = el;
  }
  Element<T>* find_set() {
    return &(list->head->elem);
  }
};

template <typename T>
struct linked_list {
  Element<T>* head;
  Element<T>* tail;
  int length;
  linked_list() {
    head = NULL;
    tail = head;
    length = 0;
  }
  linked_list(T el) {
    head = NULL;
    tail = head;
    length = 0;
    append_element(el);
  }
  ~linked_list() {
    Element<T>* current = head;
    if(current == NULL) {
      return;
    } else {
      Element<T>* next = current->next;
      delete current;
      while(next != NULL) {
        current = next;
        next = current->next;
        delete current;
      }
      return;
    }

  }
  linked_list<T>& append_element(T element);
  void print();
  linked_list<T>& Union(linked_list<T>& l);
};

template<typename T>
linked_list<T>& linked_list<T>::Union(linked_list<T>& l) {
  if(length > l.length) {
    length = length + l.length;
    Element<T>* current = l.head;
    while(current != NULL) {
      append_element(current->elem);
      current = current->next;
    }
    delete &l;
    return *this;
  } else {
    l.length = length + l.length;
    Element<T>* current = head;
    while(current != NULL) {
      l.append_element(current->elem);
      current = current->next;
    }
    delete this;
    return l;
  }
}

template <typename T>
void linked_list<T>::print() {
  Element<T>* current = head;
  printf("%d ", current->elem);
  while(current->next != NULL) {
    current = current->next;
    printf("%d ", current->elem);
  }
  printf("\n");
}

template <typename T>
linked_list<T>& linked_list<T>::append_element(T elem) {
  length++;
  Element<T>* current = head;
  if(head == NULL) {
    head = new Element<T>(elem);
    tail = head;
    tail->list = this;
    tail->next = NULL;
    return *this;
  }
  while(current->next != NULL) {
    current = current->next;
  }
  current->next = new Element<T>(elem);
  tail = current->next;
  tail->list = this;
  tail->next = NULL;
  return *this;
}