#include <iostream>

struct Node {
  Node* next = nullptr;
  Node* prev = nullptr;

  int value = 0;
};

class Deque {
 private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  size_t size_ = 0;

 public:
  Deque() = default;

  Deque(const Deque&) = default;
  Deque& operator=(const Deque&) = default;

  Deque(const Deque&&) {
  }

  int PushFront(int val) {
    Node* new_node = new Node;
    new_node->next = head_;
    new_node->value = val;
    ++size_;

    if (head_ != nullptr) {
      head_->prev = new_node;
    }
    if (tail_ == nullptr) {
      if (head_ == nullptr) {
        tail_ = new_node;
      } else {
        tail_ = head_;
      }
    }

    head_ = new_node;
    return 0;
  }

  int PushBack(int val) {
    Node* new_node = new Node;
    new_node->value = val;
    new_node->prev = tail_;
    ++size_;

    if (tail_ != nullptr) {
      tail_->next = new_node;
    }
    if (head_ == nullptr) {
      if (tail_ == nullptr) {
        head_ = new_node;
      } else {
        head_ = tail_;
      }
    }

    tail_ = new_node;

    return 0;
  }

  int PopFront() {
    if (size_ == 0) {
      return 0xBADF00D;
    }

    int result = head_->value;
    Node* next_node = nullptr;

    if (head_->next != nullptr) {
      next_node = head_->next;
      next_node->prev = nullptr;
      delete head_;
      head_ = next_node;
    } else {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    }

    --size_;
    return result;
  }

  int PopBack() {
    if (size_ == 0) {
      return 0xBADF00D;
    }

    int result = tail_->value;
    Node* prev_node = nullptr;

    if (tail_->prev != nullptr) {
      prev_node = tail_->prev;
      prev_node->next = nullptr;
      delete tail_;
      tail_ = prev_node;
    } else {
      delete tail_;
      head_ = nullptr;
      tail_ = nullptr;
    }

    --size_;
    return result;
  }

  int Front() const {
    if (size_ == 0) {
      return 0xBADF00D;
    }

    int result = head_->value;

    return result;
  }

  int Back() const {
    if (size_ == 0) {
      return 0xBADF00D;
    }

    int result = tail_->value;

    return result;
  }

  size_t Size() const {
    return size_;
  }

  void Clear() {
    Node* tmp_head = nullptr;
    while (size_ != 0) {
      tmp_head = head_->next;
      delete head_;
      head_ = tmp_head;
      --size_;
    }
    head_ = nullptr;
    tail_ = nullptr;
  }

  ~Deque() {
    Node* tmp_head = nullptr;
    while (size_ != 0) {
      tmp_head = head_->next;
      delete head_;
      head_ = tmp_head;
      --size_;
    }
    size_ = 0;
  }
};

int Solution();

int main() {
  int k = 0;
  std::cin >> k;

  Solution();

  return 0;
}

int Solution() {
  Deque deque;

  int tmp_val = 0;
  std::string request;

  while (request != "exit") {

    if (request == "push_front") {
      std::cin >> tmp_val;
      deque.PushFront(tmp_val);
      std::cout << "ok\n";
    } else if (request == "push_back") {
      std::cin >> tmp_val;
      deque.PushBack(tmp_val);

      std::cout << "ok\n";
    } else if (request == "pop_front") {
      tmp_val = deque.PopFront();
      if (tmp_val == 0xBADF00D) {
        std::cout << "error\n";
      } else {
        std::cout << tmp_val << '\n';
      }
    } else if (request == "pop_back") {
      tmp_val = deque.PopBack();
      if (tmp_val == 0xBADF00D) {
        std::cout << "error\n";
      } else {
        std::cout << tmp_val << '\n';
      }
    } else if (request == "front") {
      tmp_val = deque.Front();
      if (tmp_val == 0xBADF00D) {
        std::cout << "error\n";
      } else {
        std::cout << tmp_val << '\n';
      }
    } else if (request == "back") {
      tmp_val = deque.Back();
      if (tmp_val == 0xBADF00D) {
        std::cout << "error\n";
      } else {
        std::cout << tmp_val << '\n';
      }
    } else if (request == "size") {
      std::cout << deque.Size() << '\n';
    } else if (request == "clear") {
      deque.Clear();
      std::cout << "ok\n";
    }
    std::cin >> request;
  }

  std::cout << "bye\n";

  return 0;
}
