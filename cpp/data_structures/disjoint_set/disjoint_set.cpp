#include <fstream>
#include <iostream>
#include <vector>

class disjoint_set {
public:
    explicit disjoint_set(int N);

    int find(int val);
    void unite(int lhs, int rhs);
    bool same_component(int lhs, int rhs);

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

disjoint_set::disjoint_set(int N) {
    rank.resize(N);
    parent.resize(N);

    for (int i = 0; i < N; ++i)
        parent[i] = i;
}

int disjoint_set::find(int val) {
    if (val == parent[val])
        return val;

    return parent[val] = find(parent[val]);
}

void disjoint_set::unite(int lhs, int rhs) {
    int parent_lhs = find(lhs);
    int parent_rhs = find(rhs);

    if (rank[parent_lhs] < rank[parent_rhs])
        parent[parent_lhs] = parent_rhs;
    else
        parent[parent_rhs] = parent_lhs;

    if (rank[parent_lhs] == rank[parent_rhs])
        ++rank[parent_lhs];
}

bool disjoint_set::same_component(int lhs, int rhs) {
    return find(lhs) == find(rhs);
}

int main()
{
    std::ifstream fin("disjoint.in");
    std::ofstream fout("disjoint.out");

    int N, M;
    fin >> N >> M;

    disjoint_set ds(N);

    for (int i = 0; i < M; ++i) {
        int op, x, y;
        fin >> op >> x >> y;
        --x, --y;

        if (op == 1) {
            ds.unite(x, y);
        } else {
            if (ds.same_component(x, y)) {
                fout << "YES\n";
            } else {
                fout << "NO\n";
            }
        }
    }

    return 0;
}
