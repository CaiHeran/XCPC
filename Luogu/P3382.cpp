/**
 * @file P3382.cpp
 * @brief solution to P3382 【模板】三分法
 * @date 2022-08-15
 * 三分法
 */

#include <cstdio>
#include <iostream>
#include <iomanip>

constexpr int MAXN{14};

int n;
double a[MAXN+2]; // x^0 -> x^n

double f(double x)
{
    double y=a[0], res=x;
    for (int i=1; i<=n; ++i, res*=x)
        y += res*a[i];
    return y;
}

int main()
{
    using namespace std;
    double l, r;
    cin >> n >> l >> r;
    for (int i=n; i>=0; --i)
        cin >> a[i];

    constexpr double eps = 1e-6;
    double mid;
    while (r-l > eps)
    {
        mid = (l+r)/2;
        if (f(mid-eps)<=f(mid+eps))
            l = mid;
        else r = mid;
    }
    /*
    double m1, m2;
    while (r-l > eps)
    {
        m1 = l + (r-l)/3;
        m2 = r - (r-l)/3;
        if (f(m1)<=f(m2))
            l = m1;
        else r = m2;
    }
    */
    cout << setprecision(8) << mid << flush;
}