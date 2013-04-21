#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

template <class T, class Compare=std::less<T> >
class segment_tree {
public:
    explicit segment_tree(int _size): size(_size) {
        int sz = 1;
        while (sz <= _size)
            sz *= 2;
        sz *= 2;

        tree = new T[sz];
    }

    template <class ForwardIterator>
    explicit segment_tree(ForwardIterator begin, ForwardIterator end) {
        size = 0;
        ForwardIterator it = begin;
        while (it++ != end)
            ++size;

        int sz = 1;
        while (sz <= size)
            sz *= 2;
        sz *= 2;

        tree = new T[sz];

        _init(1, 0, size - 1, begin); 
    }

    ~segment_tree() {
        delete[] tree;
    }

    void update(int left, int right, T value) {
        _update(1, 0, size - 1, left, right, value);
    }

    T query(int left, int right) const {
        return _query(1, 0, size - 1, left, right); 
    }

private:
    template <class ForwardIterator> 
    void _init(int node, int left, int right, ForwardIterator& iter) {
        if (left == right) {
            tree[node] = *iter++;
        } else {
            int mid = left + (right - left) / 2;
            _init(2 * node, left, mid, iter);
            _init(2 * node + 1, mid + 1, right, iter);

            T left_val = tree[2 * node];
            T right_val = tree[2 * node + 1];

            if (comp(left_val, right_val)) {
                tree[node] = left_val;
            } else {
                tree[node] = right_val;
            }
        }
    }

    void _update(int node, int left, int right, int x, int y, T value) {
        if (x <= left && right <= y) {
            tree[node] = value;
        } else {
            int mid = left + (right - left) / 2;

            if (x <= mid)
                _update(2 * node, left, mid, x, y, value);
            if (y > mid)
                _update(2 * node + 1, mid + 1, right, x, y, value);

            T left_val = tree[2 * node];
            T right_val = tree[2 * node + 1];

            if (comp(left_val, right_val)) {
                tree[node] = left_val;
            } else {
                tree[node] = right_val;
            }
        }
    }

    T _query(int node, int left, int right, int x, int y) const {
        if (x <= left && right <= y) {
            return tree[node];
        } else {
            int mid = left + (right - left) / 2;

            T leftVal, rightVal;
            bool hasLeft = false, hasRight = false;
            if (x <= mid) {
                leftVal = _query(2 * node, left, mid, x, y);
                hasLeft = true;
            }
            if (y > mid) {
                rightVal = _query(2 * node + 1, mid + 1, right, x, y);
                hasRight = true;
            }

            if (!hasLeft) {
                if (!hasRight)
                    return leftVal;
                return rightVal;
            } else if (!hasRight) {
                return leftVal;
            } else {
                if (comp(leftVal, rightVal))
                    return leftVal;
                return rightVal;
            }
        }
    }

    int size;
    T *tree;
    Compare comp;
};

int main()
{
    std::ifstream fin("arbint.in");
    std::ofstream fout("arbint.out");

    int N, M;
    fin >> N >> M;

    std::vector<int> vec(N);
    for (int i = 0; i < N; ++i)
        fin >> vec[i];

    segment_tree<int, std::greater<int> > tree(vec.begin(), vec.end());

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
