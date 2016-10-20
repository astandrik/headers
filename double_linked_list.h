template <typename T, typename K>
struct double_list;

template <typename T,typename K>
struct list_element {
  T key;
  K value;
  list_element<T,K>* prev;
  list_element<T,K>* next;
  double_list<T,K>* list;
};

template <typename T, typename K>
struct double_list {
  list_element<T,K>* head;
  double_list() {
    head = NULL;
  }
  double_list<T,K>& insert(T element, K val);
  K* search(T key);
  double_list<T,K>& delete_(T element);
  K* operator[] (T elem) {
    return search(elem);
  }
};




template <typename T, typename K>
double_list<T,K>& double_list<T,K>::insert(T element, K val) {
  if(head == NULL) {
    head = new list_element<T,K>();
    head->key = element;
    head->prev = NULL;
    head->next = NULL;
    head->list = this;
    head->value = val;
  } else {
    list_element<T,K>* current = head;
    while(current->next != NULL) {
      current = current->next;
    }
    list_element<T,K>* new_elem = new list_element<T,K>();
    new_elem->prev = current;
    new_elem->next = NULL;
    new_elem->key = element;
    new_elem->value = val;
    current->next = new_elem;
  }
  return *this;
}

template <typename T, typename K>
double_list<T,K>& double_list<T,K>::delete_(T element) {
  if(head == NULL) {
    return *this;
  } else {
    list_element<T,K>* current = head;
    while(current->key != element) {
      current = current->next;
      if(current == NULL) {
        return *this;
      }
    }
    if(current->prev == NULL) {
      head = current->next;
    } else {
      current->prev->next = current->next;
    }
    return *this;
  }

}

template <typename T, typename K>
K* double_list<T,K>::search (T key) {
  list_element<T,K>* current = head;
  if(current == NULL) {
    return NULL;
  }
  while(current->key != key) {
    current = current->next;
    if(current == NULL) {
      return NULL;
    }
  }
  return &(current->value);
}