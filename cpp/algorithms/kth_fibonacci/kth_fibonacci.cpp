#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <valarray>

template <class T>
class matrix {
public:
    explicit matrix(int _row, int _col):
        row(_row), col(_col), mat(_row * _col) {}

    explicit matrix(int _row, int _col, const T& val):
        row(_row), col(_col), mat(val, _row * _col) {}

    T& operator()(int i, int j) {
        return mat[i * row + j];
    }

    static const matrix ident(int n) {
        matrix res(n, n);
        for (int i = 0; i < n; ++i)
            res(i, i) = 1;

        return res;
    }

    static const matrix zeros(int n) {
        return matrix(n, n, 0);
    }

    matrix operator+(const matrix& add) {
        matrix res(row, col);
        for (size_t i = 0; i < mat.size(); ++i)
            res.mat[i] = mat[i] + add.mat[i];

        return res;
    }

    void operator+=(const matrix& add) {
        for (size_t i = 0; i < mat.size(); ++i) 
            mat[i] += add.mat[i];
    }

    matrix operator*(matrix& mult) {
        matrix res(row, mult.col);
        for (int i = 0; i < row; ++i) 
            for (int k = 0; k < mult.col; ++k) 
                for (int j = 0; j < col; ++j) {
                    int aux = (*this)(i, j) * mult(j, k);
                    res(i, k) += aux;
                }

        return res;
    }

    matrix operator^(int n) {
        matrix res(ident(row));
        matrix base(*this);

        while (n != 0) {
            if (n % 2 == 1)
                res = res * base;
            base = base * base;
            n /= 2;
        }

        return res;
    }

    matrix& operator^=(int n) {
        matrix res = (*this) ^ n;
        std::swap(*this, res);

        return *this;
    }

    void print() {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j)
                std::cout << (*this)(i, j) << " ";
            std::cout << std::endl;
        }
    }

private:
    int row;
    int col;
    std::valarray<T> mat;
};

long long kth_fibonacci(const int k)
{
    matrix<int> fib_matrix(2, 2);
    fib_matrix(0, 0) = 1;
    fib_matrix(0, 1) = 1;
    fib_matrix(1, 0) = 1;
    fib_matrix(1, 1) = 0;

    fib_matrix ^= k;

    return fib_matrix(0, 1);
}

// Test code
int main()
{
    std::cout << kth_fibonacci(20) << "\n"; // 6765
    std::cout << kth_fibonacci(13) << "\n"; // 233
    std::cout << kth_fibonacci(40) << "\n"; // 102334155

    return 0;
}
