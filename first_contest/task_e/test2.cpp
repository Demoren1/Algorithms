#include <iostream>
#include <vector>

class FenwickTree {
public:
    FenwickTree(int n) : n(n), tree(n + 1, 0) {}

    void update(int index, int delta) {
        index++; // Индексация с 1
        while (index <= n) {
            tree[index] += delta;
            index += index & -index;
        }
    }

    int query(int index) {
        index++; // Индексация с 1
        int result = 0;
        while (index > 0) {
            result += tree[index];
            index -= index & -index;
        }
        return result;
    }

private:
    int n;
    std::vector<int> tree;
};

int main() {
    int n;
    std::cin >> n;
    std::vector<int> exhibits(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> exhibits[i];
    }

    FenwickTree fenwick_tree(n);

    for (int exhibit : exhibits) {
        fenwick_tree.update(exhibit, 1);
    }

    int m;
    std::cin >> m;

    for (int i = 0; i < m; ++i) {
        std::string query;
        std::cin >> query;

        if (query == "s") {
            int l, r;
            std::cin >> l >> r;
            l--; // Индексация с 0
            r--; // Индексация с 0
            int result = fenwick_tree.query(r) - (l > 0 ? fenwick_tree.query(l - 1) : 0);
            std::cout << result << std::endl;
        } else {
            int i, v;
            std::cin >> i >> v;
            i--; // Индексация с 0
            fenwick_tree.update(exhibits[i], -1);
            fenwick_tree.update(v, 1);
            exhibits[i] = v;
        }
    }

    return 0;
}
