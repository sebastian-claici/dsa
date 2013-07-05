#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <class T>
class graph {
public:
    explicit graph() {}

    template <class InputIterator>
    explicit graph(InputIterator begin, InputIterator end)
        : nodes(begin, end) {}

    void add_node(T node) {
        nodes.insert(node);
    }
    
    void add_edge(T src, T dst) {
        nodes.insert(src);
        nodes.insert(dst);
        edges[src].push_back(dst);
        edges[dst].push_back(src);
    }

    int connected_components() {
        std::unordered_set<T> visited;

        int components = 0;
        for (T node : nodes) {
            if (!visited.count(node)) {
               dfs(node, visited);
               ++components;
            }
        }

        return components;
    }

private:
    void dfs(T node, std::unordered_set<T>& visited) {
        visited.insert(node);

        for (T next : edges[node]) {
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
