/**
 * @file CF797E.cpp
 * @date 2022-04-25
 * *分块
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

template <typename T=int>
T rd()
{
    T n; char c=getchar();
    while (c<'0'||'9'<c) c = getchar();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + c-'0';
    return n;
}

constexpr int MAXN{100'000}, MAXQ{100'000};

int main()
{
    int n = rd();
    int a[MAXN+1];
    std::generate_n(a+1, n, rd<int>);

    int q = rd();
    int l = std::sqrt(n);
    int f[320][MAXN+1]; // f[k][p] is ans for k<=sqrt(n)

    for (int k=1; k<=l; ++k)
        for (int j=n; j>=1; --j)
            f[k][j] = 1 + (j+a[j]+k <= n)*f[k][j+a[j]+k];

    while (q--)
    {
        int p=rd(), k=rd(); // <=n
        if (k<=l) {
            printf("%d\n", f[k][p]);
        }
        else {
            int cnt=0;
            while (p <= n) {
                p+=a[p]+k;
                ++cnt;
            }
            printf("%d\n", cnt);
        }
    }
}