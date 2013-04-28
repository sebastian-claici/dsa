#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

class graph {
 public:
    explicit graph(int _size)
        : size(_size), 
          cost_matrix(_size, std::vector<int>(_size)),
          adjacency_matrix(_size, std::vector<bool>(_size, false)) {}

    void add_edge(int src, int dst, int cost) {
        if (cost != 0)
            adjacency_matrix[src][dst] = true; 
        cost_matrix[src][dst] = cost;
    }

    std::vector<std::vector<int>> roy_floyd() {
        std::vector<std::vector<int>> result(size, std::vector<int>(size));

        for (auto i = 0; i < size; ++i)
            for (auto j = 0; j < size; ++j) {
                result[i][j] = cost_matrix[i][j];
                if (i != j && result[i][j] == 0)
                    result[i][j] = std::numeric_limits<int>::max() / 2 - 1;
            }

        for (auto k = 0; k < size; ++k) {
            for (auto i = 0; i < size; ++i) {
                for (auto j = 0; j < size; ++j) {
                    result[i][j] = std::min(result[i][j], 
                            result[i][k] + result[k][j]);
                }
            }
        }

        return result;
    }

 private:
    int size;
    std::vector<std::vector<int>> cost_matrix;
    std::vector<std::vector<bool>> adjacency_matrix;
};

int main()
{
    std::ifstream fin("royfloyd.in");
    std::ofstream fout("royfloyd.out");

    int N;
    fin >> N;

    graph g(N);
    for (auto i = 0; i < N; ++i)
        for (auto j = 0; j < N; ++j) {
            int cost;
            fin >> cost;
            g.add_edge(i, j, cost);
        }

    std::vector<std::vector<int>> result = g.roy_floyd();
    for (auto i = 0; i < result.size(); ++i) {
        for (auto j = 0; j < result[i].size(); ++j)
            fout << result[i][j] << " ";
        fout << "\n";
    }

    return 0;
}
