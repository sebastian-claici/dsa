#include <fstream>
#include <vector>

// Returns a list of all prime numbers up to N (inclusive). Uses the
// sieve of Eratosthenes technique to filter out numbers that are not
// prime.
//
// Time complexity: O(N * log(log(N)))
//
// Args:
//      N: number up to which prime numbers should be recovered
//
// Returns: a vector containing all prime numbers up to N in sorted
//      order
std::vector<int> sieve(const int N)
{
    std::vector<int> primes;

    // initially, all numbers are considered prime
    std::vector<bool> is_prime(N, true);

    for (int i = 2; i <= N; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            
            auto limit = static_cast<long long>(i) * i;
            if (limit > N)
                continue;
            // mark all multiples of i as non-prime
            for (int j = i * i; j <= N; j += i)
                is_prime[j] = false;
        }
    }

    return primes;
}

// Test code
int main()
{
    std::ifstream fin("ciur.in");
    std::ofstream fout("ciur.out");

    int N;
    fin >> N;

    auto primes = sieve(N);
    fout << primes.size() << "\n";

    return 0;
}
