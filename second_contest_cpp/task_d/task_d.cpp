#include <iostream>
#include <stack>
#include <deque>

class MinQueue {
 private:
  std::deque<int> vals_deq_;
  std::deque<int> mins_deq_;

 public:
  int Enqueue(int num) {
    if (vals_deq_.empty()) {
      vals_deq_.push_back(num);
      mins_deq_.push_back(num);
    } else {
      vals_deq_.push_back(num);

      while (!mins_deq_.empty() && mins_deq_.back() > num) {
        mins_deq_.pop_back();
      }

      mins_deq_.push_back(num);
    }

    return 0;
  }

  int Dequeue() {
    int result = 0;
    if (vals_deq_.front() == mins_deq_.front()) {
      result = vals_deq_.front();

      mins_deq_.pop_front();
      vals_deq_.pop_front();
    } else {
      result = vals_deq_.front();
      vals_deq_.pop_front();
    }

    return result;
  }

  int Min() {
    return mins_deq_.front();
  }

  int Front() {
    return vals_deq_.front();
  }

  size_t Size() {
    return vals_deq_.size();
  }

  int Clear() {
    vals_deq_.clear();
    mins_deq_.clear();

    return 0;
  }

  bool Empty() {
    return vals_deq_.empty();
  }
};

int Solution();
int QueueEmptyCheck(MinQueue& queue);

int main() {
  Solution();

  return 0;
}

int Solution() {
  int m = 0;
  std::cin >> m;

  MinQueue queue;
  std::string request;

  int tmp_num = 0;

  for (int i = 0; i < m; ++i) {
    std::cin >> request;
    if (request == "enqueue") {
      std::cin >> tmp_num;
      queue.Enqueue(tmp_num);

      std::cout << "ok\n";
    } else if (request == "dequeue") {
      if (QueueEmptyCheck(queue)) {
        std::cout << "error\n";
      } else {
        tmp_num = queue.Dequeue();
        std::cout << tmp_num << '\n';
      }
    } else if (request == "front") {
      if (QueueEmptyCheck(queue)) {
        std::cout << "error\n";
      } else {
        tmp_num = queue.Front();
        std::cout << tmp_num << '\n';
      }
    } else if (request == "size") {
      tmp_num = static_cast<int>(queue.Size());
      std::cout << tmp_num << '\n';
    } else if (request == "clear") {
      queue.Clear();
      std::cout << "ok\n";
    } else if (request == "min") {
      if (QueueEmptyCheck(queue)) {
        std::cout << "error\n";
      } else {
        tmp_num = queue.Min();
        std::cout << tmp_num << '\n';
      }
    }
  }

  return 0;
}

int QueueEmptyCheck(MinQueue& queue) {
  if (queue.Empty()) {
    return 1;
  }

  return 0;
}