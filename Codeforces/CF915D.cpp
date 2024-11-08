/**
 * @file CF915D.cpp
 * @brief solution to CF915D Almost Acyclic Graph
 * @date 2022-09-29
 * 拓扑排序
 */

#include <cstdio>
#include <algorithm>
#include <vector>

template <class T=int>
T rd() {
    char c;
    while (c=getchar(), c<'0'||'9'<c);
    T n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + c-'0';
    return n;
}

constexpr int MAXN{501};

int n, m;
std::vector<short> g[MAXN+1];
int indeg[MAXN+1]{};
int ind[MAXN+1];

int toposort()
{
    int cnt{0};
    short l=0, r=-1, q[MAXN+1];
    for (int i=1; i<=n; i++)
        if (ind[i]==0)
            q[++r]=i, cnt++;
    while (l<=r) {
        int u=q[l++];
        for (auto v: g[u])
            if (--ind[v]==0)
                q[++r]=v, cnt++;
    }
    return cnt;
}

int main()
{
    n=rd(); m=rd();
    for (int i=0, u,v; i<m; i++) {
        u=rd(); v=rd();
        indeg[v]++;
        g[u].push_back(v);
    }
    for (int i=1; i<=n; i++) {
        std::copy_n(indeg+1, n, ind+1);
        ind[i]--;
        if (toposort()==n) {
            printf("YES");
            return 0;
        }
    }
    printf("NO");
    return 0;
}