#include <fstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>

template <class T>
class graph {
public:
    explicit graph() {}

    template <class ForwardIterator>
    explicit graph(ForwardIterator begin, ForwardIterator end)
        : nodes(begin, end) {}

    void add_node(T node) {
        nodes.insert(node);
    }
    
    void add_edge(T src, T dst) {
        nodes.insert(src);
        nodes.insert(dst);
        edges[src].push_back(dst);
    }

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
