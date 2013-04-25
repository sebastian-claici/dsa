#include <algorithm>
#include <fstream>
#include <vector>

template <class Iterable>
Iterable longest_common_substring(const Iterable& A,
                                  const Iterable& B)
{
    std::vector<std::vector<int> > dp(A.size() + 1, 
            std::vector<int>(B.size() + 1));

    for (int i = 1; i <= A.size(); ++i)
        for (int j = 1; j <= B.size(); ++j) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

    Iterable result;

    int i = A.size(), j = B.size();
    while (i != 0 && j != 0) {
        if (A[i - 1] == B[j - 1]) {
            result.push_back(A[i - 1]);
            --i, --j;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }

    std::reverse(result.begin(), result.end());

    return result;
}

int main()
{
    std::ifstream fin("cmlsc.in");
    std::ofstream fout("cmlsc.out");

    int N, M;
    fin >> N >> M;

    std::vector<int> A(N);
    for (int i = 0; i < N; ++i)
        fin >> A[i];

    std::vector<int> B(M);
    for (int i = 0; i < M; ++i)
        fin >> B[i];

    std::vector<int> result = longest_common_substring(A, B);

    typedef std::vector<int>::iterator iter;
    fout << result.size() << "\n";
    for (iter it = result.begin(); it != result.end(); ++it)
        fout << *it << " ";
    fout << "\n";

    return 0;
}
