#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
class board {
private:
    vector<bool> diag1, diag2, vert;
    vector<int> horiz;
    int size;
    bool tryQueen(int x, int y) {
        return !diag1[x + y] && !diag2[size + x - y] && !vert[x];
    }
    void putQueen(int x, int y) {
        horiz[y] = x;
        diag1[x + y] = diag2[size + x - y] = vert[x] = true;
    }
    void unputQueen(int x, int y) {
        horiz[y] = -1;
        diag1[x + y] = diag2[size + x - y] = vert[x] = false;
    }
public:
    board(int sz) :size(sz), horiz(sz, -1), diag1(2 * sz, false), diag2(2 * sz, false), vert(sz, false)
    {}
    int count_roots(int y=0) {
        if (y == size)
            return 1;
        int count = 0;
        for (int x = 0; x < size; ++x) {
            if (tryQueen(x, y)) {
                putQueen(x, y);
                count += count_roots(y + 1);
                unputQueen(x, y);
            }
        }
        return count;
    }
};
int main()
{
    int n;
    cin >> n;
    board game(n);
    cout << game.count_roots();
    return 0;
}