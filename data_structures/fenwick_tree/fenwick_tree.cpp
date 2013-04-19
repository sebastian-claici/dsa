#include <fstream>
#include <vector>

class fenwick_tree {
public:
    explicit fenwick_tree(const std::vector<int>& vals);
    explicit fenwick_tree(const int _size);
    ~fenwick_tree();

    int query(int id);
    int query(int left, int right);
    int find(int sum);
    void update(int id, int to_add);

private:
    int size;
    int *tree;
};

fenwick_tree::fenwick_tree(const std::vector<int>& vals)
        : size(vals.size()) {
    tree = new int[vals.size() + 1];
    for (int i = 0; i < vals.size(); ++i) 
        update(i + 1, vals[i]); 
}

fenwick_tree::fenwick_tree(const int _size) 
        : size(_size) {
    tree = new int[_size + 1];
}

fenwick_tree::~fenwick_tree() {
    delete[] tree;
}

int fenwick_tree::query(int id) {
    int sum = 0;
    while (id > 0) {
        sum += tree[id];
        id -= (id & -id);
    }

    return sum;
}

int fenwick_tree::query(int left, int right) {
    return query(right) - query(left - 1);
}

void fenwick_tree::update(int id, int to_add) {
    while (id <= size) {
        tree[id] += to_add;
        id += (id & -id);
    }
}

int fenwick_tree::find(int sum) {
    int bitmask;
    for (bitmask = 1; bitmask < size; bitmask *= 2);

    for (int i = 0; bitmask != 0; bitmask /= 2) {
        if (i + bitmask <= size) {
            if (sum >= tree[i + bitmask]) {
                i += bitmask;
                sum -= tree[i];
                if (sum == 0)
                    return i;
            }
        }
    }

    return -1;
}

int main()
{
    std::ifstream fin("aib.in");
    std::ofstream fout("aib.out");

    int N, M;
    fin >> N >> M;

    fenwick_tree tree(N);
    for (int i = 0; i < N; ++i) {
        int x;
        fin >> x;
        tree.update(i + 1, x);
    }

    for (int i = 0; i < M; ++i) {
        int op;
        fin >> op;

        if (op == 0) {
            int id, val;
            fin >> id >> val;
            tree.update(id, val);
        } else if (op == 1) {
            int l, r;
            fin >> l >> r;
            fout << tree.query(l, r) << "\n";
        } else {
            int sum;
            fin >> sum;
            fout << tree.find(sum) << "\n";
        }
    }

    return 0;
}
