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
};

template <typename T>
struct linked_list {
  Element<T>* head;
  Element<T>* tail;
  linked_list() {
    head = NULL;
    tail = head;
  }
  void append_element(T elem) {
    Element<T>* current = head;
    if(head == NULL) {
      head = new Element<T>(elem);
      tail = head;
      tail->list = this;
      tail->next = NULL;
      return;
    }
    while(current->next != NULL) {
      current = current->next;
    }
    current->next = new Element<T>(elem);
    tail = current->next;
    tail->list = this;
    tail->next = NULL;
  }
  void print() {
    Element<T>* current = head;
    printf("%d ", current->elem);
    while(current->next != NULL) {
      current = current->next;
      printf("%d ", current->elem);
    }
    printf("\n");
  }
};
