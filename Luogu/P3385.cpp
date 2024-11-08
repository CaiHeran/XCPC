// SPFA 判断负环
#include <cstring>
#include <cstdio>

#include <queue>
#include <bitset>

template <typename T=int>
T rd()
{
    T f=1, n; char c;
    while (c=getchar(), c<'0'||'9'<c)
        if (c=='-') f=-1;
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + (c-'0');
    return f*n;
}

constexpr int MAXN = 2e4+2, MAXM = 6e4+2;

class Graph
{
public:
    struct Edge{
        int v, w, nxt=0;
        bool operator<(const Edge &e) const
          { return w < e.w; }
        bool operator>(const Edge &e) const
          { return w > e.w; }
// # if __cplusplus >=202002L
# if __cpp_impl_three_way_comparison >= 201907L
        auto operator<=>(const Edge& e) const
          { return w<=>e.w; }
# endif
    };
    int vn=0, en=0, hd[MAXN]{};
    Edge ed[MAXN];

    void add_edge(int u, int v, int w)
    {
        ++en;
        ed[en] = {v, w, hd[u]};
        hd[u] = en;
    }
    void add_edges(int x, int y, int w)
    {
        add_edge(x, y, w);
        add_edge(y, x, w);
    }

};

int dist[MAXN];

bool SPFA(Graph& G, int s)
{
    auto &ed = G.ed;
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    std::queue<int> q;
    //bool inq[MAXN]{};
    std::bitset<MAXN> inq{};
    std::int_fast16_t cnt[MAXN]{};
    q.push(s);
    inq[s] = 1;
    cnt[s] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for (int i=G.hd[u]; i; i=G.ed[i].nxt)
        {
            int v = G.ed[i].v;
            if (dist[v] > dist[u] + ed[i].w) {
                dist[v] = dist[u] + ed[i].w;
                if (!inq[v]) {
                    if (++cnt[v] >= G.vn)
                        return false; // 有负环
                    q.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
    return true;
}

int main()
{
    int T = rd();
    while (T--)
    {
    Graph g;
    g.vn = rd();
    int en = rd();
    for (int i=0, u,v,w; i<en; ++i) {
        u = rd(); v = rd(); w = rd();
        if (w >= 0)
            g.add_edges(u, v, w);
        else
            g.add_edge(u, v, w);
    }
    puts(SPFA(g, 1)? "NO":"YES");
    }
}