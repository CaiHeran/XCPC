
#include <cstdio>
#include <algorithm>

constexpr int MAXN = 1e5;

int readN()
{
    int n; char c=getchar();
    while (c<'0'||'9'<c)
        c = getchar();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + (c-'0');
    return n;
}

template<typename T>
int LIS(T it, const T end)
{
    int Len=0, d[end-it]{*it};
    while (++it!=end)
    {
        if (*it > d[Len])
            d[++Len] = *it;
        else
            *std::lower_bound(d, d+Len, *it) = *it;
    }
    return Len+1;
}

int main()
{
    int n=readN();
    int s1[n+1], s2[n];
    for (int i=1; i<=n; ++i)
        s1[i] = readN();
    for (int i=0; i<n; ++i)
        s2[i] = readN();

    int m[n+1];
    for (int i=1; i<=n; ++i)
        m[s1[i]] = i;
    std::for_each(s2, s2+n, [&m](int& a){a=m[a];});

    printf("%d", LIS(s2, s2+n));
}