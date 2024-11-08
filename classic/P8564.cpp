/**
 * @file P8564.cpp
 * @brief solution to P8564 ρars/ey
 * @date 2022-10-04
 * 树形DP 树上背包
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

template <class T=int>
T rd() {
    char c=getchar();
    while (c<'0'||'9'<c) c = getchar();
    T n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + c-'0';
    return n;
}
template<class T>
constexpr void _min(T& a, const T& b)
    { if (b<a) a=b; }

using int64 = int64_t;
constexpr int MAXN{5001};
constexpr int64 INF{0x3f3f3f3f3f3f3f3f};

int n;
std::vector<short> tr[MAXN+1];
int f[MAXN+1];
short sz[MAXN+1]{};
int64 dp[MAXN+1][MAXN+1]; // 以i为根的子树留j个结点需要的最小代价
int64 dpt[MAXN+1];

void solve(int u=1, int fa=0)
{
    sz[u] = 1;
    if (u!=1 && tr[u].size()<=1) {
        dp[u][1] = 0;
        return;
    }
    dp[u][1] = 0;
    for (auto v: tr[u])
        if (v!=fa) {
            solve(v, u);
            memcpy(dpt+1, dp[u]+1, 8*sz[u]);
            memset(dp[u]+1, 0x3f, 8*(sz[u]+sz[v]));
            for (int i=1; i<=sz[u]; i++)
                for (int j=1; j<=sz[v]; j++)
                    _min(dp[u][i+j], dpt[i]+dp[v][j]);
            sz[u] += sz[v];
        }
    dp[u][1] = INF;
    for (int i=2; i<=sz[u]; i++)
        _min(dp[u][1], dp[u][i] + f[i]);
}

int main()
{
    n = rd();
    f[1] = 0;
    std::generate_n(f+2, n-1, rd<int>);
    for (int i=1, u,v; i<n; i++) {
        u=rd(); v=rd();
        tr[u].push_back(v);
        tr[v].push_back(u);
    }
    solve(1);
    printf("%lld", dp[1][1]);
}