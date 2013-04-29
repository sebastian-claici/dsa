#include <algorithm>
#include <fstream>

// Implementation of the Euclidean algorithm for finding the greatest common
// divisor of two integers. 
//
// For more information:
// http://en.wikipedia.org/wiki/Greatest_common_divisor#Using_Euclid.27s_algorithm

// Recursive implementation
// Args:
//      a: first integer
//      b: second integer
//
// Returns: the greatest common divisor of a and b.
int gcd_recur(int a, int b)
{
    if (b == 0)
        return a;
    return gcd_recur(b, a % b);
}

// Iterative implementation
// Args:
//      a: first integer
//      b: second integer
//
// Returns: the greatest common divisor of a and b.
int gcd_iter(int a, int b)
{
    if (a < b)
        std::swap(a, b);

    while (b != 0) {
        int aux = a % b;
        a = b;
        b = aux;
    }

    return a;
}

// Test code
int main()
{
    std::ifstream fin("euclid2.in");
    std::ofstream fout("euclid2.out");

    int T;
    fin >> T;
    
    while (T--) {
        int a, b;
        fin >> a >> b;
        fout << gcd_iter(a, b) << "\n";
    }

    return 0;
}
