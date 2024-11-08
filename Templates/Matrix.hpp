
#include <array>
#include <vector>
#include "general.hpp"

namespace Matrix
{
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

constexpr int MOD = 1e9+7;

// Static size
template <uint32 Rows, uint32 Cols, class T>
class Matrix
{
public:
    T a[Rows][Cols]{};

    constexpr uint32 rows() const noexcept
        { return Rows; }
    constexpr uint32 cols() const noexcept
        { return Cols; }

    constexpr auto& operator[](uint32 i) noexcept
        { return a[i]; }

    template <uint32 oCols>
    constexpr auto operator*(const Matrix<Cols,oCols,T>& r) const noexcept
    {
        Matrix<Rows, oCols, T> res{};
        for (uint32 i=0u; i<Rows; ++i)
            for (uint32 j=0u; j<oCols; ++j) {
                res[i][j] = 0;
                for (uint32 k=0u; k<Cols; ++k)
                    res[i][j] = (res[i][j] + (int64_t)a[i][k]*r.a[k][j]%MOD) % MOD;
            }
        return res;
    }

    template <std::enable_if_t<Rows == Cols, bool> = true>
    constexpr Matrix& operator*=(const Matrix<Cols,Cols,T>& r)
    {
        static_assert(Rows == Cols);
        return *this = *this * r;
    }

    template <std::enable_if_t<Rows == Cols, bool> = true>
    constexpr Matrix& pow(uint64 n)
    {
        static_assert(Rows == Cols);
        Matrix res = Identity<Rows,T>();
        while (n > 0)
        {
            if (n&1)
                res *= *this;
            *this *= *this;
            n >>= 1;
        }
        return *this = res;
    }

// utilities
    template <uint32 N, class _T>
    static constexpr Matrix Identity() noexcept
    {
        Matrix<N, N, _T> I{};
        for (uint32 i=0; i<N; ++i)
            I.a[i][i] = 1;
        return I;
    }
};

/* Example:
 Fibonacci number
  @code
uint64 Fibonacci(int n)
{
    Matrix<2,2,uint64> a{{0, 1}, {1, 1}};
    return a.pow(n-1)[1][1];
}
  @endcode
*/

// Dynamic size
template <typename T>
class dMatrix
{
protected:
    uint32 rows, cols;
    std::vector<T> A;
public:
    dMatrix(uint32 rows, uint32 cols, T val=0)
        : rows(rows), cols(cols), A(rows*cols, val) {}
    template <class Ty>
    dMatrix(uint32 rows, uint32 cols, Ty&& o)
        : rows(rows), cols(cols), A(std::forward<Ty>(o)) {}

    constexpr uint32 Rows() const noexcept
        { return rows; }
    constexpr uint32 Cols() const noexcept
        { return cols; }

    template <class Ty>
    dMatrix<T>& operator=(Ty&& r)
    {
        rows = r.rows;
        cols = r.cols;
        A = std::forward_like<Ty>(r).A;
        return *this;
    }

    T& operator[](uint32 i, uint32 j)
    {
        Expects(i < rows && j < cols);
        return A[i*cols+j];
    }

    const T& operator[](uint32 i, uint32 j) const
    {
        Expects(i < rows && j < cols);
        return A[i*cols+j];
    }

    T& operator()(uint32 i, uint32 j)
    {
        Expects(i < rows && j < cols);
        return A[i*cols+j];
    }

    dMatrix<T> operator*(const dMatrix<T>& r) const
    {
        Expects(cols == r.rows);
    
        dMatrix<T> res(rows, r.cols);
        for (uint32 i=0; i<rows; i++)
            for (uint32 j=0; j<r.cols; j++)
                for (uint32 k=0; k<cols; k++)
                    res[i,j] = (res[i,j] + A[i*cols+k]*r[k,j]) % MOD;
        return res;
    }

    dMatrix<T>& operator*=(const dMatrix& r)
        { return *this = *this * r; }

    dMatrix<T> pow(uint64 n)
    {
        Expects(rows != cols);

        dMatrix<T> res = Identity<T>(rows);
        while (n > 0) {
            if (n&1)
                res *= *this;
            *this *= *this;
            n >>= 1;
        }
        return *this = res;
    }

    template <typename Ty>
    static dMatrix<Ty> Identity(uint32 n)
    {
        dMatrix<Ty> I(n, n);
        for (uint32 i=0; i<n; i++)
            I(i,i) = 1;
        return I;
    }

};

/**
 * @brief Solve a system of linear equations using Gaussian elimination
 * @param m A augmented matrix of size n * (n+1) where n is the number of equations,
 *         and please make sure that the system has a unique solution
 * @return A vector of size n containing the solution
 */
template<typename T>
std::vector<T> solve(const dMatrix<T> &m)
{
    Expects(m.Rows()+1 == m.Cols());

    // copy matrix in order to swap rows
    std::vector<std::vector<T>> v;
    v.reserve(m.Rows());

    for (uint32 i=0; i<m.Rows(); i++)
        v.emplace_back(&m[i,0], &m[i,0]+m.Cols());

    for (uint32 i=0; i<m.Cols()-1; i++)
    {
        if (v[i][i]==0)
        {
            uint32 j=i+1;
            for (; j<m.Rows(); j++)
                if (v[j][i] != 0) {
                    v[i].swap(v[j]);
                    break;
                }
            Expects (j != m.Rows());
        }
        for (uint32 j=i+1; j<m.Rows(); j++)
        {
            T ratio = v[j][i] / v[i][i];
            for (uint32 k=i; k<m.Cols(); k++)
                v[j][k] -= ratio * v[i][k];
        }
    }

    for (int i=0; i<m.Rows(); i++)
    {
        for (int j=0; j<m.Cols(); j++)
            std::cout << v[i][j] << ' ';
        std::cout << std::endl;
    }

    std::vector<T> res(m.Rows());

    for (uint32 i=m.Rows()-1; i>0; i--)
    {
        res[i] = v[i][m.Rows()/*Cols-1*/] /= v[i][i];
        v[i][i] = 1;    // can be removed
        for (uint32 j=0; j<i; j++)
        {
            v[j][m.Rows()/*Cols-1*/] -= v[j][i] * v[i][m.Rows()/*Cols-1*/];
            v[j][i] = 0;    // can be removed
        }
    }

    res[0] = v[0][m.Rows()/*Cols-1*/] /= v[0][0];

    return res;
}

}

/*
int main()
{
    Matrix::dMatrix<double> a(4,5, std::vector<double>{1,2,1,-1,4, 2,3,-1,1,-1, 3,3,7,2,6, 4,5,1,3,-1});
    auto ans = Matrix::solve(a);
    for (auto x : ans)
        std::cout << x << ' ';
    std::cout << std::endl;
}
*/