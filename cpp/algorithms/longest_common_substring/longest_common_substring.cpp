#include <algorithm>
#include <fstream>
#include <vector>


// Implementation of the longest common substring dynamic programming 
// algorithm.
// 
// The longest common substring problem is to find the longest string that is a
// substring of two or more strings.
// 
// Example: the longest common substring of the strings "ABABC" and "BABCA" is
// "ABC".
// 
// Time complexity: O(N * M), where N and M are the lengths of the two strings.
template <class Iterable>
Iterable longest_common_substring(const Iterable& A,
                                  const Iterable& B)
{
    // best[i][j] - length of the longest common substring between
    //      A[0..i] and B[0..j]
    // 
    // best[i][j] is computed as follows:
    //      best[i][j] = best[i - 1][j - 1] + 1, if A[i - 1] == B[j - 1]
    //          (we can extend the longest substring by 1)
    //      best[i][j] = max(best[i - 1][j], best[i][j - 1]) otherwise
    // 
    std::vector<std::vector<int> > best(A.size() + 1, 
            std::vector<int>(B.size() + 1));

    for (int i = 1; i <= A.size(); ++i)
        for (int j = 1; j <= B.size(); ++j) {
            if (A[i - 1] == B[j - 1]) {
                best[i][j] = best[i - 1][j - 1] + 1;
            } else {
                best[i][j] = std::max(best[i - 1][j], best[i][j - 1]);
            }
        }

    Iterable result;

    int i = A.size(), j = B.size();
    while (i != 0 && j != 0) {
        if (A[i - 1] == B[j - 1]) {
            result.push_back(A[i - 1]);
            --i, --j;
        } else if (best[i - 1][j] > best[i][j - 1]) {
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
