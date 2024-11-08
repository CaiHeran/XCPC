/**
 * @file CF337D.cpp
 * @brief solution to CF337D Book of Evil
 * @date 2022-09-13
 * 树形DP 换根DP
 */

#include <cstdio>
#include <cstring>
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

constexpr int MAXN{100001};

int n, m, d;
std::vector<int> tr[MAXN+1];
int indis[MAXN+1][2]; // maximum and secondary distances from monsters in the subtree
int updis[MAXN+1]; // maximum distances from monsters out of the subtree

void dfs1(int u, int fa=-1)
{
    for (int v: tr[u])
      if (v!=fa) {
        dfs1(v, u);
        if (indis[v][0]+1 >= indis[u][0])
            indis[u][1] = indis[u][0],
            indis[u][0] = indis[v][0]+1;
        else indis[u][1] = std::max(indis[u][1], indis[v][0]+1);
      }
}
void dfs2(int u, int fa=-1)
{
    for (int v: tr[u])
      if (v!=fa) {
        if (indis[u][0] == indis[v][0]+1)
            updis[v] = std::max(updis[u], indis[u][1])+1;
        else
            updis[v] = std::max(updis[u], indis[u][0])+1;
        dfs2(v, u);
      }
}

int main()
{
    n=rd(); m=rd(); d=rd();
    memset(indis[1], 0xcf, sizeof(*indis)*n*2);
    memset(updis+1, 0xcf, sizeof(*updis)*n);
    for (int i=0, p; i<m; i++) {
        p = rd();
        indis[p][0] = indis[p][1] = 0;
    }
    for (int i=1, u,v; i<n; i++) {
        u=rd(); v=rd();
        tr[u].push_back(v);
        tr[v].push_back(u);
    }
    dfs1(1);
    dfs2(1);
    int cnt = indis[1][0] <= d && indis[1][1] <= d;
    for (int i=2; i<=n; i++)
        cnt += indis[i][0]<=d && updis[i]<=d;
    printf("%d", cnt);
}