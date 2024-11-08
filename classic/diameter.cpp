
#include "general.hpp"
#include <cstdio>
#include <iostream>

constexpr int MAXN = 101, MAXM = 201;

struct Edge {
    int v, nxt=0;
};
int en=0, hd[MAXN]{};
Edge ed[MAXM]{};

inline void add_ed(int u, int v)
{
    ++en;
    ed[en] = {v, hd[u]};
    hd[u] = en;
}
inline void add_eds(int x, int y)
{
    add_ed(x, y);
    add_ed(y, x);
}

int maxlen=0, dia;
void dfs(int u=1, int fa=0, int dist=0)
{
    if (dist > maxlen)
        maxlen = dist, dia = u;
    for(int i=hd[u]; i; i=ed[i].nxt) {
        int v = ed[i].v;
        if (v != fa)
            dfs(v, u, dist+1);
    }
}

int main()
{
    int n=rd();
    for (int i=1; i<n; ++i)
        add_eds(rd(), rd());

    dfs(1);
    int x = dia;
    maxlen = 0;
    dfs(x);
    int y = dia;
    std::cout << x << ' ' << y << ' ' << maxlen;
}