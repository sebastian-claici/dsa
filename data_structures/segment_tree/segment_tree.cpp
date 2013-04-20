#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

template <class T>
class segment_tree {
public:
    explicit segment_tree(int size);
    explicit segment_tree(const std::vector<T>& init_data);

    void update(int left, int right, T value);
    T query(int left, int right) const;

private:
    void _init(int node, int left, int right, 
               const std::vector<T>& init_data);
    void _update(int node, int left, int right, int x, int y, T value);
    T _query(int node, int left, int right, int x, int y) const;

    int size;
    std::vector<T> tree;
};

template <class T>
segment_tree<T>::segment_tree(int _size): size(_size) {
    int sz = 1;
    while (sz <= _size)
        sz *= 2;
    sz *= 2;

    tree.resize(sz);
}

template <class T>
segment_tree<T>::segment_tree(const std::vector<T>& init_data)
        : size(init_data.size()) {
    int sz = 1;
    while (sz <= init_data.size())
        sz *= 2;
    sz *= 2;

    tree.resize(sz);

    _init(1, 0, init_data.size() - 1, init_data);
}

template <class T>
void segment_tree<T>::update(int left, int right, T value) {
    _update(1, 0, size - 1, left, right, value);
}

template <class T>
T segment_tree<T>::query(int left, int right) const {
    return _query(1, 0, size - 1, left, right); 
}

template <class T>
void segment_tree<T>::_init(int node, int left, int right, 
                            const std::vector<T>& init_data) {
    if (left == right) {
        tree[node] = init_data[left];
    } else {
        int mid = left + (right - left) / 2;
        _init(2 * node, left, mid, init_data);
        _init(2 * node + 1, mid + 1, right, init_data);

        tree[node] = std::max(tree[2 * node], tree[2 * node + 1]);
    }
}

template <class T>
void segment_tree<T>::_update(int node, int left, int right, 
                              int x, int y, T value) {
    if (x <= left && right <= y) {
        tree[node] = value;
    } else {
        int mid = left + (right - left) / 2;

        if (x <= mid)
            _update(2 * node, left, mid, x, y, value);
        if (y > mid)
            _update(2 * node + 1, mid + 1, right, x, y, value);
        
        tree[node] = std::max(tree[2 * node], tree[2 * node + 1]);
    }
}

template <class T>
T segment_tree<T>::_query(int node, int left, int right, 
                          int x, int y) const {
    if (x <= left && right <= y) {
        return tree[node];
    } else {
        int mid = left + (right - left) / 2;

        T value = std::numeric_limits<T>::min();
        if (x <= mid)
            value = std::max(value, _query(2 * node, left, mid, x, y));
        if (y > mid)
            value = std::max(value, _query(2 * node + 1, mid + 1, 
                                           right, x, y));

        return value;
    }
}

int main()
{
    std::ifstream fin("arbint.in");
    std::ofstream fout("arbint.out");

    int N, M;
    fin >> N >> M;

    std::vector<int> vec(N);
    for (int i = 0; i < N; ++i)
        fin >> vec[i];

    segment_tree<int> tree(vec);

    for (int i = 0; i < M; ++i) {
        int op, a, b;
        fin >> op >> a >> b;

        if (op == 0) {
            --a, --b;
            fout << tree.query(a, b) << std::endl;
        } else {
            --a;
            tree.update(a, a, b);
        }
    }
    
    return 0;
}
