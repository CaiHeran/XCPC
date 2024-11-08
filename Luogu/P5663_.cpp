#include <cstdio>
#include <queue>

int rd()
{
    int n; char c=getchar();
    while (c<'0'||'9'<c)
        c = getchar();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + (c-'0');
    return n;
}

constexpr int maxn=1e5+9;

int n, m, q;
int cnt=0, hd[maxn]{};
struct {
    int v, nxt=0;
} ed[maxn*2];

void add(int u, int v)
{
    ed[cnt] = {v, hd[u]};
    hd[u] = cnt;
    ++cnt;
}

struct tup{
    int v, dis;
};

int dis[maxn]{};
void Dijstra(int s)
{
    memset(dis, 0x3f, sizeof (dis));
    bool vis[maxn]{};
    
    std::priority_queue<tup> q;
    q.push({s, 0});
    while (q.size())
    {
        auto u = q.top();
        q.pop();
        if (vis[u.v]) continue;
        vis[u.v] = true;
        for (int i=hd[u.v]; ~i; i=ed[i].nxt)
            if (!vis[ed[i].v] && dis[ed[i].v]>u.dis+1)
            {
                dis[ed[i].v] = u.dis+1;
                q.push({u.dis+1, dis[ed[i].v]});
            }
    }
}

int main()
{
    n=rd(), m=rd(), q=rd();
    memset(hd, 0xff, sizeof(int)*(n+5));
    for (int i=0; i<m; ++i)
        add(rd(), rd());
    Kruskal(1);
    while (q--)
    {
        puts(dis[rd()]<rd()? "Yes":"No");
    }
}