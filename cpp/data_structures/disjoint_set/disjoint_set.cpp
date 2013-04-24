#include <fstream>
#include <iostream>
#include <vector>

// Implementation of a disjoint_set data structure.
//
// A disjoint_set data structure is a data structure that keeps track of a
// set of elements partitioned into a number of disjoint (nonoverlapping)
// subsets. A union-find algorithm is an algorithm that performs two
// operations on such a data structure:
//      * Find: determine which subset a particular element is in.
//      * Union: Join two subsets into a single subset.
//
// For more information: 
// http://en.wikipedia.org/wiki/Disjoint-set_data_structure
class disjoint_set {
public:
    explicit disjoint_set(int N);
    ~disjoint_set();

    int find(int val);
    void unite(int lhs, int rhs);
    bool same_component(int lhs, int rhs);

private:
    int *parent;
    int *rank;
};

// Constructs a disjoint-set of specified size.
//
// Args:
//      size: size of the resulting data structure
disjoint_set::disjoint_set(int size) {
    parent = new int[size];
    rank = new int[size];

    for (int i = 0; i < size; ++i)
        parent[i] = i;
}

disjoint_set::~disjoint_set() {
    delete[] parent;
    delete[] rank;
}

// Find the component in which val is located.
//
// Args:
//      val: the element for which we want to find the enclosing component
//
// Returns: the root element of the component containing val
int disjoint_set::find(int val) {
    if (val == parent[val])
        return val;

    // To speed-up future queries, path compression is applied. We only
    // care about the path between an element and the root of its component
    // so intermediate paths can be compressed.
    return parent[val] = find(parent[val]);
}

// Unite the components which contain lhs and rhs.
//
// Args:
//      lhs: element of component to unite with component of rhs
//      rhs: elemenf of component to unite with component of lhs
void disjoint_set::unite(int lhs, int rhs) {
    int parent_lhs = find(lhs);
    int parent_rhs = find(rhs);

    // To avoid having an unbalanced tree, a union pairs the lower
    // weighted sub-tree as the child of the heavier sub-tree.
    // If both elements are equally weighted, one is chosen at random.
    if (rank[parent_lhs] < rank[parent_rhs])
        parent[parent_lhs] = parent_rhs;
    else
        parent[parent_rhs] = parent_lhs;

    if (rank[parent_lhs] == rank[parent_rhs])
        ++rank[parent_lhs];
}

// Query whether lhs and rhs are in the same component.
//
// Args:
//      lhs: component to query
//      rhs: component to query
//
// Returns: true if lhs and rhs are in the same component,
//      false otherwise
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
