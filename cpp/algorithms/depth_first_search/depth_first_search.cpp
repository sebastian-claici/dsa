#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Find the number of connected components in an undirected graph.
//
// A connected component is a set of nodes C such that for all 
// nodes x, y in C, there is a path between x and y.
//
// Time complexity: O(M), where M is the number of edges.
//
// For more information: http://en.wikipedia.org/wiki/Depth-first_search 
template <class T>
class graph {
public:
    // Creates an empty graph with no nodes and no edges.
    explicit graph() {}

    // Creates a graph with nodes taken from the range [begin, end).
    //
    // Args:
    //      begin: iterator pointing to the beginning of a range
    //      end: iterator pointing to the end of a range
    template <class InputIterator>
    explicit graph(InputIterator begin, InputIterator end)
        : nodes(begin, end) {}

    // Adds a node to the graph
    //
    // Args:
    //      node: new node to be added
    void add_node(T node) {
        nodes.insert(node);
    }
    
    // Adds an edge between the nodes src and dst. Adds src and dst to 
    // the list of nodes.
    //
    // Args:
    //      src: start node of the edge
    //      dst: end node of the edge
    void add_edge(T src, T dst) {
        nodes.insert(src);
        nodes.insert(dst);
        edges[src].push_back(dst);
        edges[dst].push_back(src);
    }

    // Return the number of connected components of this graph.
    //
    // Returns: an integer representing the number of connected components.
    int connected_components() {
        std::unordered_set<T> visited;

        int components = 0;
        for (const T node : nodes) {
            if (!visited.count(node)) {
               dfs(node, visited);
               ++components;
            }
        }

        return components;
    }

private:
    // Perform a depth first search of the graph, marking each
    // visited node.
    //
    // Args:
    //      node: node being currently inspected
    //      visited: set of already visited nodes
    void dfs(const T node, std::unordered_set<T>& visited) {
        visited.insert(node);

        for (const T next : edges[node]) {
            if (!visited.count(next))
                dfs(next, visited);
        }
    }

    std::unordered_set<T> nodes;
    std::unordered_map<T, std::vector<T>> edges;
};

// Test code
int main()
{
    std::ifstream fin("dfs.in");
    std::ofstream fout("dfs.out");

    int N, M;
    fin >> N >> M;

    graph<int> g;
    for (int i = 1; i <= N; ++i) 
        g.add_node(i);

    for (int i = 1; i <= M; ++i) {
        int x, y;
        fin >> x >> y;
        g.add_edge(x, y);
    }

    fout << g.connected_components() << "\n";

    return 0;
}
