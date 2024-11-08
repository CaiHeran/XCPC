// P1613 跑路
// 图上DP

#include <cstdio>
#include <cstring>
#include <iostream>

template <typename T=int>
T rd()
{
    T n; char c=getchar();
    while (c<'0'||'9'<c)
        c = getchar();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + (c-'0');
    return n;
}

constexpr int MAXN = 51;

int main()
{
    int n=rd(), m=rd();
    bool g[MAXN][MAXN][64]{};
    int ma[MAXN][MAXN];
    memset(ma, 0x3f, sizeof(ma));

    while (m--)
    {
        int u=rd(), v=rd();
        g[u][v][0] = true;
        ma[u][v] = 1;
    }

    for (int k=1; k<64; ++k)
        for (int u=1; u<=n; ++u)
        for (int v=1; v<=n; ++v)
            for (int j=1; j<=n; ++j)
                if (g[u][j][k-1]&&g[j][v][k-1])
                {
                    g[u][v][k] = true;
                    ma[u][v] = 1;
                }
    // Floyd
    using std::min;
    for (int k=1; k<=n; ++k)
        for (int i=1; i<=n; ++i)
            for (int j=1; j<=n; ++j)
                ma[i][j] = min(ma[i][j], ma[i][k] + ma[k][j]);

    std::cout << ma[1][n];
}