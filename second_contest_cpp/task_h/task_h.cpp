#include <iostream>
#include <deque>
// #define DBG printf("%s:%d -- %s\n", __FILE__, __LINE__, __FUNCTION__);

int Solution();

bool CheckBracket(std::deque<char>& deque, char checkable_bracket);

int main() {
  Solution();

  return 0;
}

int Solution() {
  std::deque<char> deque;

  std::string brackets;
  bool psp_flag = true;
  std::cin >> brackets;

  for (char bracket : brackets) {
    switch (bracket) {
      case ('('): {
        deque.push_front(bracket);
        break;
      }
      case ('{'): {
        deque.push_front(bracket);
        break;
      }
      case ('['): {
        deque.push_front(bracket);
        break;
      }
      case (')'): {
        psp_flag = CheckBracket(deque, '(');
        break;
      }
      case (']'): {
        psp_flag = CheckBracket(deque, '[');
        break;
      }
      case ('}'): {
        psp_flag = CheckBracket(deque, '{');
        break;
      }
    }
    if (!psp_flag) {
      std::cout << "NO\n";
      break;
    }
  }
  if (!deque.empty() && psp_flag) {
    psp_flag = false;
    std::cout << "NO\n";
  }

  if (psp_flag) {
    std::cout << "YES\n";
  }
  return 0;
}

bool CheckBracket(std::deque<char>& deque, const char checkable_bracket) {
  bool psp_flag = true;
  char tmp_bracket = 'a';
  if (deque.empty()) {
    psp_flag = false;
  } else {
    tmp_bracket = deque.front();
    deque.pop_front();
    if (tmp_bracket != checkable_bracket) {
      psp_flag = false;
    }
  }

  return psp_flag;
}