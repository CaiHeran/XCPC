// 这篇代码写得太烂
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <stack>
#include <vector>
#include <queue>

#ifdef DEBUG
# define DB(eq) eq
#else
# define DB(eq)
#endif

using std::cout;
using std::min;
using std::max;
using std::uint32_t;

static constexpr int MAXN = 10002, MAXM = 200002;

int wei[MAXN];
int w[MAXN]{};
uint32_t dfn[MAXN], low[MAXN];

std::vector<int> rb[MAXN];
std::vector<std::vector<int> > scc;
uint32_t sccno[MAXN]{};

class Graph
{
public:

    struct Edge {
        int u, v;
    };
    int n;
    int hd[MAXN]{};
    struct {
        int v, nxt=0;
    } ed[MAXM];

    inline void add_ed(int u, int v)
    {
        static int cnt=0;
        ++cnt;
        ed[cnt] = {v, hd[u]};
        hd[u] = cnt;
    }

// 每个点只属于一个强连通分量

void tarjan_scc(const int u) // 强连通分量
{
    static uint32_t num{0};
    static std::stack<int> S;

    dfn[u] = low[u] = ++num;
    S.emplace(u);

    for (int i=hd[u]; i; i=ed[i].nxt)
    {
        int v = ed[i].v;
        if (!dfn[v])
        {
            tarjan_scc(v);
            low[u] = min(low[u], low[v]);
        }
        else if (!sccno[v]) // 不要考虑已确定强连通分量编号的点
        {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (low[u] == dfn[u])
    {
        std::vector<int> c;
        const uint32_t No = 1 + scc.size();
        int v;
        do {
            v = S.top(); S.pop();
            sccno[v] = No;
            c.emplace_back(v);
            w[No] += wei[v]; //
        } while (v != u);
        scc.emplace_back(std::move(c));
    }
}

void search_scc()
{
    for (int i=1; i<=n; ++i)
        if (!sccno[i])
            tarjan_scc(i);
}

int topo()
{
    bool vis[MAXN]{};
    uint32_t in[MAXN]{};
    std::queue<int> que, q;
    for (int i=1; i<=n; ++i)
        for (int it=hd[i]; it; it=ed[it].nxt)
            ++in[ed[it].v];

    for (int i=1; i<=n; ++i)
        if (!in[i])
            vis[i]=true, que.emplace(i);

    while (!que.empty())
    {
        int u = que.front();
        que.pop();
        q.emplace(u);
        for (int j=hd[u]; j; j=ed[j].nxt)
        {
            int v = ed[j].v;
            if (vis[v] || !in[v]) continue;
            --in[v];
            if (in[v]==0)
                que.emplace(v);
        }
    }
    // return q;
    int ans[MAXN]{};
    while(!q.empty())
    {
        int v = q.front(); q.pop();
        DB(cout << ' '<< v << '\n';)
        int maxw=0;
        for (auto u: rb[v])
            maxw = max(maxw, ans[u]);
        ans[v] = maxw + w[v];
        DB(cout << ans[v] << '\n';)
    }
    return *std::max_element(ans+1, ans+n+1);
}

};

template <typename T=int>
T rd()
{
    T n; char c=getchar();
    while (c<'0'||'9'<c)
        c = getchar();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + c-'0';
    return n;
}

int main()
{
    DB(freopen("P3387.in", "r", stdin);)
    Graph g;
    int n=rd(), m=rd();
    std::for_each(wei+1, wei+n+1, [](auto&n){n=rd();});
    for (int x, y; m--;)
    {
        x=rd(); y=rd();
        g.add_ed(x, y);
    }

    g.n = n;
    g.search_scc();

    if (scc.size() == 1) {
        cout << w[1];
        return 0;
    }
#ifdef DEBUG
    DB(cout << "scc: " << scc.size() << '\n';)
    for (int i=scc.size()-1; i>=0; --i)
    {
        for (auto i: scc[i]) {
            DB(cout << i <<' ';)
        }
        DB(cout << w[i+1] << '\n';)
    }
#endif

    Graph g2;
    g2.n = scc.size();

    for (int u=1; u<=n; ++u)
        for (int i=g.hd[u]; i; i=g.ed[i].nxt)
        {
            int v = g.ed[i].v;
            if (sccno[u] != sccno[v]) {
                g2.add_ed(sccno[u], sccno[v]),
                rb[sccno[v]].emplace_back(sccno[u]);
                DB(cout << sccno[u] << "-->" << sccno[v] << '\n';)
            }
        }
    auto ans = g2.topo();
    std::cout << ans;
    DB(fclose(stdin);)
}