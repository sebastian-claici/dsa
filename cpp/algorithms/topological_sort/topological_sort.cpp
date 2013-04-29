#include <fstream>
#include <iostream>
#include <queue>
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

    void add_edge(T src, T dst) {
        nodes.insert(src);
        nodes.insert(dst);
        edges[src].push_back(dst);
    }

    std::vector<T> topological_sort() {
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
