#include <cstdio>
#include <iostream>

typedef std::uint64_t ull;

ull read()
{
    ull n; char c=getchar();
    while (c<'0'||'9'<c)
        c = getchar();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + (c-'0');
    return n;
}

constexpr int maxn = 2e6;

int n, m, c, k;
ull a[maxn];

int cnt_1(ull n)
{
    int a=0;
    while (n)
        a += n&1, n>>=1;
    return a;
}

int main()
{
    n=read(), m=read(), c=read(), k=read();
    ull has=0, re=0;
    for (int i=0; i<n; ++i)
        a[i] = read();
    for (int i=0; i<n; ++i)
        has |= a[i];
    for (int i=0; i<m; ++i)
        re |= 1<<read(), read();
    int cnt=0;
    for (int i=0; i<k; ++i)
        cnt += has>>i&1 || !(re>>i&1);
    printf("%llu", 1<<cnt);
}