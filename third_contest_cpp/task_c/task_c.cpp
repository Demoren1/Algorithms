#include <iostream>
#include <algorithm>

struct Player {
  size_t num = 0;
  size_t n_tasks = 0;
  size_t penalty_time = 0;
};

int Solution();
int FillPlayers(Player* players, size_t n);
bool CustomComparator(const Player& first, const Player& second);
int ShowPlayers(Player* players, size_t n);

int main() {
  Solution();
  return 0;
}

int Solution() {
  size_t n = 0;

  std::cin >> n;
  auto players = new Player[n];

  FillPlayers(players, n);
  std::sort(players, players + n, CustomComparator);
  ShowPlayers(players, n);

  delete[] players;
  return 0;
}

int FillPlayers(Player* players, size_t n) {
  size_t tmp_tasks = 0;
  size_t tmp_time = 0;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> tmp_tasks >> tmp_time;
    players[i].num = i + 1;
    players[i].n_tasks = tmp_tasks;
    players[i].penalty_time = tmp_time;
  }

  return 0;
}

int ShowPlayers(Player* players, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    std::cout << players[i].num << '\n';
  }

  return 0;
}

bool CustomComparator(const Player& first, const Player& second) {
  if (first.n_tasks < second.n_tasks) {
    return false;
  }

  if (first.n_tasks > second.n_tasks) {
    return true;
  }

  if (first.penalty_time > second.penalty_time) {
    return false;
  }

  if (first.penalty_time < second.penalty_time) {
    return true;
  }

  if (first.num > second.num) {
    return false;
  }

  return true;
}