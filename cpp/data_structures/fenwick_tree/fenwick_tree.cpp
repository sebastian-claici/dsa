#include <fstream>
#include <vector>

// Implementation of a Fenwick tree data structure.
//
// A Fenwick tree or binary indexed tree is a data structure providing
// efficient methods for calculation and manipulation of the prefix sums
// of a table of values.
//
// For more information: http://en.wikipedia.org/wiki/Fenwick_tree
class fenwick_tree {
public:
    template <class ForwardIterator>
    explicit fenwick_tree(ForwardIterator begin, ForwardIterator end);
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

// Constructs a Fenwick tree from the range [begin, end). Each element
// in the resulting tree will hold the cumulative frequency up to
// that point.
//
// Args:
//      begin: iterator pointing to the beginning of the range
//      end: iterator pointing to the end of the range
template <class ForwardIterator>
fenwick_tree::fenwick_tree(ForwardIterator begin, ForwardIterator end) {
    size = 0;
    ForwardIterator it = begin;
    while (it++ != end)
        ++size;

    int i = 1;
    tree = new int[size + 1];
    while (begin != end) 
        update(i++, *begin++); 
}

// Constructs a Fenwick tree of a specified size. Each element in the
// tree will be initially 0. Because Fenwick trees are 1-indexed, the 
// created tree is one more than the size given as an argument.
//
// Args:
//      _size: size of the tree to be constructed
fenwick_tree::fenwick_tree(const int _size) 
        : size(_size) {
    tree = new int[_size + 1];
}

// Frees all memory held by this data structure.
fenwick_tree::~fenwick_tree() {
    delete[] tree;
}

// Queries the cumulative frequency at id.
//
// Args:
//      id: the index (1-based) to query
int fenwick_tree::query(int id) {
    int sum = 0;
    while (id > 0) {
        sum += tree[id];
        // id & -id is the lowest set bit in id; by subtracting this
        // from id, we move to the next number whose cumulative
        // frequency we need to add, but haven't yet added.
        id -= (id & -id);
    }

    return sum;
}

// Queries the cumulative frequency in the range [left, right].
//
// Args:
//      left: leftmost index (1-based) of the interval to be queried
//      right: rightmost index (1-based) of the interval to be queried
int fenwick_tree::query(int left, int right) {
    return query(right) - query(left - 1);
}

// Update the value at index id to be initial_value + to_add. Returns -1
// if there is no index satisfying the requirements.
//
// Args:
//      id: index where the update should occur
//      to_add: amount to add to the element at index id
void fenwick_tree::update(int id, int to_add) {
    while (id <= size) {
        tree[id] += to_add;
        // id & -id is the lowest set bit in id; by adding this
        // to id, we move to the next highest number that 
        // not have the lowest bit in id set.
        id += (id & -id);
    }
}

// Find the index where the cumulative frequency is exactly equal
// to sum.
//
// Args:
//      sum: the value to which the cumulative frequency must be 
//          equal to
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
