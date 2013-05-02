#include <fstream>

// Implementation of the extended Euclidean algorithm.
//
// The extended Euclidean algorithm is used for finding integer solution
// for the equation:
//
//          a * x + b * y = d
//
// where d is the greatest common divisor of a and b.
//
// We know that a * x + b * y = d for some x, y; due to the Euclidean
// algorithm, we must also have:
//
//          b * x0 + (a % b) * y0 = d
//
// If we rewrite a % b = a - b * (a div b), where a div b is the integer part 
// of a / b, and group terms, we obtain:
//
//          b * (x0 - (a div b) * y0 - y) = a * (x - y0)
//
// From here, one solution is:
//          
//          x = y0
//          y = x0 - (a div b) * y0
//
// All that remains is the initial solution. When b == 0, we have that 
// a == d, so the initial solution can simply be:
//
//          x = 1
//          y = 0
void extended_euclid(int a, int b, int *d, int *x, int *y)
{
    if (b == 0) {
        *d = a;
        *y = 0;
        *x = 1;
    } else {
        int x0, y0;
        extended_euclid(b, a % b, d, &x0, &y0);
        *x = y0;
        *y = x0 - a / b * y0;
    }
}

// Test code
// Find a integer solution of a * x + b * y = c for given a, b, c
int main()
{
    std::ifstream fin("euclid3.in");
    std::ofstream fout("euclid3.out");

    int T;
    fin >> T;

    while (T--) {
        int a, b, c;
        fin >> a >> b >> c;

        int x, y, d;
        extended_euclid(a, b, &d, &x, &y);
        if (c % d != 0) {
            fout << 0 << " " << 0 << "\n";
        } else {
            x = x * (c / d);
            y = y * (c / d);
            fout << x << " " << y << "\n";
        }
    }

    return 0;
}
