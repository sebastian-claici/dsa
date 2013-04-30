#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Implemenation of a graph data structure. This example only
// creates directed, unweighted graphs. Each graph is represented by 
// a set of nodes, and an adjacency list for each node.
//
// This is a simple implementation just for the sake of the topological
// sort algorithm.
//
// Note: T must define a hash value
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

    // Retrieve a topological sort of this graph.
    //
    // A topological sort of a directed graph is a linear ordering of its
    // vertices such that for every directed edge u-v from node u to node 
    // v, u comes before v in the ordering.
    //
    // For more information: http://en.wikipedia.org/wiki/Topological_sorting
    //
    // Returns: a vector of nodes such that if u-v is an edge in the graph,
    //      then u comes before v in the vector.
    std::vector<T> topological_sort() {
        // in_degree represents the amount of edges coming into each node
        std::unordered_map<T, int> in_degree;
        for (auto entry : edges) {
           for (auto neighbour : entry.second) {
               ++in_degree[neighbour];
           }
        }

        std::queue<T> q;
        for (auto node : nodes)
            if (in_degree[node] == 0)
                q.push(node);

        // Gradually remove nodes that have no incoming edges; remove all
        // edges starting from the removed node, and add all nodes that 
        // have in-degree 0 to the queue.
        std::vector<T> result;
        while (!q.empty()) {
            T node = q.front();
            q.pop();
            result.push_back(node);

            if (edges.count(node) == 0)
                continue;

            for (auto neighbour : edges[node]) {
                --in_degree[neighbour];
                if (in_degree[neighbour] == 0)
                    q.push(neighbour);
            }
        }

        return result;
    }

private:
     std::unordered_map<T, std::vector<T>> edges;
     std::unordered_set<T> nodes;
};

// Test code
int main()
{
    std::ifstream fin("sortaret.in");
    std::ofstream fout("sortaret.out");

    int N, M;
    fin >> N >> M;

    std::vector<int> v;
    for (int i = 1; i <= N; ++i)
        v.push_back(i);

    graph<int> g(begin(v), end(v));
    for (int i = 0; i < M; ++i) {
        int src, dst;
        fin >> src >> dst;
        g.add_edge(src, dst);
    }

    auto result = g.topological_sort();
    for (auto node : result) 
        fout << node << " ";
    fout << "\n";

    return 0;
}
