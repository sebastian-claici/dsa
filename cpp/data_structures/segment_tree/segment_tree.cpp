#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

// Implementation of a segment tree data structure.
//
// A segment tree is a tree data structure for storing intervals. It allows
// querying which of the stored segments contain a given point. A segment tree
// for a set of n intervals uses O(n * logn) storage and can be built in
// O(n * logn) time.
//
// For more information: http://en.wikipedia.org/wiki/Segment_tree
//
// Sample usage:
//      segment_tree<int> tree(20);
//      tree.update(2, 2, 10); 
//      tree.query(2, 4);
template <class T, class Compare=std::less<T> >
class segment_tree {
public:
    // Constructs a segment tree with enough nodes to hold _size
    // intervals of length 1.
    //
    // Args:
    //      _size: number of elementary intervals the tree should cover
    explicit segment_tree(int _size): size(_size) {
        int sz = 1;
        while (sz <= _size)
            sz *= 2;
        sz *= 2;

        tree = new T[sz];
    }

    // Constructs a segment tree where each elementary interval is
    // taken from within the range [begin, end).
    //
    // Args:
    //      begin: iterator pointing to the beginning of range of T values
    //      end: iterator pointing to the end of a range of T values
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

    // Deletes all data held by this instance of a segment tree
    ~segment_tree() {
        delete[] tree;
    }

    // Updates the interval [left, right] with value. Based on the
    // comparator function used, this could mean either the minimum
    // element in that range gets updated, or the maximum, or similar. 
    //
    // Args:
    //      left: leftmost edge of the interval to be updated
    //      right: rightmost edge of the interval to be updated
    //      value: new value for that interval
    void update(int left, int right, T value) {
        _update(1, 0, size - 1, left, right, value);
    }

    // Queries the value in the interval [left, right]. Based on the
    // comparator function used, this could mean either the minimum
    // element in that range, or the maximum, or similar.
    //
    // Args:
    //      left: leftmost edge of the interval queried
    //      right: rightmost edge of the interval queried
    T query(int left, int right) const {
        return _query(1, 0, size - 1, left, right); 
    }

private:
    // Initializes the segment tree such that the value stored in
    // [i, i] is the i-th value of the iterator (0-based index), i.e.,
    //      [0, 0] holds *it
    //      [3, 3] holds *(it + 3)
    //
    // Args:
    //      node: current node in the tree traversal
    //      left: leftmost edge of the interval stored in the current node
    //      right: rightmost edge of the interval stored in the current node
    //      iter: pointer to an iterator over T values
    template <class ForwardIterator> 
    void _init(int node, int left, int right, ForwardIterator& iter) {
        // We are in an elementary interval.
        if (left == right) {
            tree[node] = *iter++;
        } else {
            int mid = left + (right - left) / 2;
            // Update left and right children.
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

    // Implementation of the update function.
    //
    // Args:
    //      node: current node in the tree traversal
    //      left: leftmost edge of the interval stored in the current node
    //      right: rightmost edge of the interval stored in the current node
    //      x: leftmost edge of the interval we want to update
    //      y: rightmost edge of the interval we want to update
    //      value: new value for the interval
    void _update(int node, int left, int right, int x, int y, T value) {
        // We are in an elementary interval.
        if (x <= left && right <= y) {
            tree[node] = value;
        } else {
            int mid = left + (right - left) / 2;

            // If left or right children contain part of the result,
            // update each, and combine the result to update the
            // current interval.
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

    // Implementation of the query function.
    //
    // Args:
    //      node: current node in the tree traversal
    //      left: leftmost edge of the interval stored in the current node
    //      right: rightmost edge of the interval stored in the current node
    //      x: leftmost edge of the interval we want to update
    //      y: rightmost edge of the interval we want to update
    T _query(int node, int left, int right, int x, int y) const {
        if (x <= left && right <= y) {
            return tree[node];
        } else {
            int mid = left + (right - left) / 2;

            T leftVal, rightVal;
            bool hasLeft = false, hasRight = false;
            // If left or right children contain part of the interval,
            // query each individually, and combine the results.
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
