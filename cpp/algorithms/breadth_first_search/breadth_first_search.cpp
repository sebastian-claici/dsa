#include <fstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>

// Computes the single-source shortest paths from a any node
// to all the other nodes in the graph.
//
// Graph is directed, and weights are all 1 (although the algorithm
// works if the weights are any constant)
//
// Time complexity: O(M), where M is the number of edges.
//
// For more information: https://en.wikipedia.org/wiki/Breadth-first_search
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
    template <class ForwardIterator>
    explicit graph(ForwardIterator begin, ForwardIterator end)
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
    }

    // Finding the shortest paths in an unweighted graph can be 
    // done by running a breadth-first search over the graph.
    //
    // Since the edges are unweighted, the first time we encounter
    // a node is also at the lowest depth we can encounter it.
    //
    // Args:
    //      src: the source node for the search
    //
    // Returns: a map between node and distance from source. If a node
    //      is unreachable, then the distance is -1.
    std::unordered_map<T, int> distance_map(T src) {
        std::queue<T> q;
        std::unordered_set<T> visited;
        std::unordered_map<T, int> dist;

        for (T node : nodes)
            dist[node] = -1;

        q.push(src);
        visited.insert(src);
        dist[src] = 0;
        while (!q.empty()) {
            T node = q.front();
            q.pop();

            for (T next : edges[node]) {
                if (!visited.count(next)) {
                    visited.insert(next);
                    q.push(next);
                    dist[next] = dist[node] + 1;
                }
            }
        }

        return dist;
    }

private:
    std::unordered_set<T> nodes;
    std::unordered_map<T, std::vector<T>> edges;
};

// Test code
int main()
{
    std::ifstream fin("bfs.in");
    std::ofstream fout("bfs.out");

    int N, M, S;
    fin >> N >> M >> S;

    graph<int> g;
    for (int i = 1; i <= N; ++i)
        g.add_node(i);

    for (int i = 1; i <= M; ++i) {
        int x, y;
        fin >> x >> y;
        g.add_edge(x, y);
    }

    auto res = g.distance_map(S);
    for (int i = 1; i <= N; ++i)
        fout << res[i] << " ";
    fout << "\n";

    return 0;
}
