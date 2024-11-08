// P1410 子序列
// DP

#include <cstdio>
#include <iostream>
#include <algorithm>

template <typename T=int>
T rd()
{
    char c=getchar();
    while (c<'0'||'9'<c) c = getchar();
    T n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + c-'0';
    return n;
}

constexpr int MAXN = 2001;

template<class T>
int LuS(T it, const T end)
{
    int Len=1, d[std::distance(it, end)];
    d[0] = *it;
    while (++it!=end)
    {
        if (*it<=d[Len-1])
            d[Len++] = *it;
        else
            *std::upper_bound(d, d+Len, *it, std::greater<int>{}) = *it;
    }
    return Len;
}

int main()
{
    int n, s[MAXN];
    while (~scanf("%d", &n))
    {
        std::for_each(s, s+n, [](int&n){n=rd();});
        puts(LuS(s, s+n)>2? "No!":"Yes!");
    }
}