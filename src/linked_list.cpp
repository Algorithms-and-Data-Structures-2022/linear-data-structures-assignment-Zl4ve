#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    if (front_ == nullptr) {
      front_ = new Node(value);
      back_ = new Node(value);
      size_ = 1;
    } else {
      Node* temp = back_;
      back_ = new Node(value);
      temp -> next = back_;
      size_++;
    }
  }

  bool LinkedList::Insert(int index, int value) {
    if (index < 0 || index > size_) {
      return false;
    }
    if (front_ == nullptr) {
      if (index == 0) {
        front_ = new Node(value);
        back_ = new Node(value);
        size_++;
        return true;
      }
      return false;
    }
    if (index == 0) {
      Node* temp = front_;
      front_ = new Node(value);
      front_ -> next = temp;
      size_++;
      return true;
    }
    if (index == size_) {
      Node* temp = back_;
      back_ = new Node(value);
      temp -> next = back_;
      size_++;
      return true;
    }
    Node* curr = front_;
    Node* prevCurr;
    for (int i = 0; i < index; i++) {
      if (i == index - 1) {
        prevCurr = curr;
      }
      curr = curr -> next;
    }
    Node* temp = curr;
    curr = new Node(value);
    curr -> next = temp;
    prevCurr -> next = curr;
    size_++;
    return true;
  }

  bool LinkedList::Set(int index, int new_value) {
    if (index < 0 || index >= size_) {
      return false;
    }
    Node* curr = front_;
    for (int i = 0; i < size_; i++) {
      if (i == index) {
        curr -> value = new_value;
      }
      curr = curr -> next;
    }
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index < 0 || index >= size_) {
      return std::nullopt;
    }
    if (index == 0) {
      int removedElem = front_ -> value;
      front_ = front_ -> next;
      size_--;
      return removedElem;
    }
    Node* curr = front_;
    Node* prevCurr;
    for (int i = 0; i < index; i++) {
      if (i == index - 1) {
        prevCurr = curr;
      }
      curr = curr -> next;
    }
    int removed = curr -> value;
    prevCurr -> next = curr -> next;
    curr -> next = nullptr;
    size_--;
    return removed;
  }

  void LinkedList::Clear() {
    Node* curr = front_;
    Node* temp;
    for (int i = 0; i < size_; i++) {
      temp = curr -> next;
      if (curr != nullptr) {
        delete curr;
      }
      curr = temp;
    }
    back_ = nullptr;
    front_ = nullptr;
    size_ = 0;
  }

  std::optional<int> LinkedList::Get(int index) const {
    if (index < 0 || index >= size_) {
      return std::nullopt;
    }
    Node* curr = front_;
    for (int i = 0; i < size_; i++) {
      if (i == index) {
        return curr -> value;
      }
      curr = curr -> next;
    }
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    Node* curr = front_;
    for (int i = 0; i < size_; i++) {
      if (curr -> value == value) {
        return i;
      }
      curr = curr -> next;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    Node* temp = front_;
    while (temp != nullptr) {
      if (temp -> value == value) {
        return true;
      }
      temp = temp -> next;
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return size_ == 0;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (front_ == nullptr) {
      return std::nullopt;
    }
    return front_ -> value;
  }

  std::optional<int> LinkedList::back() const {
    if (back_ == nullptr) {
      return std::nullopt;
    }
    return back_ -> value;
  }

  Node* LinkedList::FindNode(int index) const {
    if (index < 0 || index >= size_) {
      return nullptr;
    }
    Node* curr = front_;
    for (int i = 0; i < size_; i++) {
      if (i == index) {
        return curr;
      }
      curr = curr -> next;
    }
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment