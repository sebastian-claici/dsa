#include <algorithm>
#include <fstream>

int gcd_recur(int a, int b)
{
    if (b == 0)
        return a;
    return gcd_recur(b, a % b);
}

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
