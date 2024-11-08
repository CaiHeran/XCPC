/**
 * @file P5536.cpp
 * @brief solution to P5536 【XR-3】核心城市
 * @date 2022-10-03
 * 树的直径 树的中心 贪心
 */

#include <cstdio>
#include <algorithm>
#include <functional>
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

constexpr int MAXN = 1e5+1;

int n, k;
std::vector<int> tr[MAXN+1];
int maxd, far;
int dep[MAXN+1], pa[MAXN+1];
int dist[MAXN+1];

void dfs1(int u, int fa=-1)
{
    if (dep[u] > maxd) {
        maxd = dep[u];
        far = u;
    }
    for (int v: tr[u])
        if (v!=fa) {
            dep[v] = dep[u]+1;
            dfs1(v, u);
        }
}
void dfs2(int u, int fa=-1)
{
    if (dep[u] > maxd) {
        maxd = dep[u];
        far = u;
    }
    for (int v: tr[u])
        if (v!=fa) {
            dep[v] = dep[u]+1;
            pa[v] = u;
            dfs2(v, u);
        }
}

int dfs3(int u, int fa=-1)
{
    int maxd=dep[u];
    for (int v: tr[u])
        if (v!=fa) {
            dep[v] = dep[u]+1;
            maxd = std::max(maxd, dfs3(v, u));
        }
    dist[u] = maxd - dep[u];
    return maxd;
}

int main()
{
    n=rd(); k=rd();
    for (int i=1, u,v; i<n; i++) {
        u=rd(); v=rd();
        tr[u].push_back(v);
        tr[v].push_back(u);
    }
    // 求树的中心
    maxd=0; dep[1]=0;
    dfs1(1);
    int rt = far;
    maxd=0; dep[rt]=0;
    dfs2(rt);
    rt = far;
    for (int i=0; i < maxd/2; i++)
        rt = pa[rt];

    dep[rt]=0;
    dfs3(rt);
    std::nth_element(dist+1, dist+k+1, dist+n+1, std::greater<int>{});
    printf("%d", dist[k+1]+1); // 不是 dist[k] (对于最后一层只取一部分的情况)
}