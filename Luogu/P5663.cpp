#include <cstdio>
#include <queue>
#include <memory.h>

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
int cnt=1, hd[maxn]{};
struct {
    int v, nxt=0;
} ed[maxn*2];

void add(int u, int v)
{
    ed[cnt] = {v, hd[u]};
    hd[u] = cnt;
    ++cnt;
}
void adds(int x, int y)
{
    add(x, y);
    add(y, x);
}

struct tup{
    int v, dis;
    bool operator<(const tup& r) const
      { return v>r.v; }
};

int dise[maxn], diso[maxn];
void Dijstra(int s)
{
    memset(dise, 0x3f, sizeof(dise));
    memset(diso, 0x3f, sizeof(diso));
    dise[s]=0;
    bool vise[maxn]{};
    bool viso[maxn]{};

    std::priority_queue<tup> q;
    q.push({s, 0});
    while (q.size())
    {
        auto u = q.top();
        q.pop();
        if (u.dis&1)
        {
            if (viso[u.v]) continue;
            viso[u.v] = true;
            for (int i=hd[u.v]; i; i=ed[i].nxt)
            {
                auto v = ed[i].v;
                if (dise[v] > u.dis+1)
                    dise[v] = u.dis+1,
                    q.push({v, dise[v]});
            }
        }
        else
        {
            if (vise[u.v]) continue;
            vise[u.v] = true;
            for (int i=hd[u.v]; i; i=ed[i].nxt)
            {
                auto v = ed[i].v;
                if (diso[v] > u.dis+1)
                    diso[v] = u.dis+1,
                    q.push({v, diso[v]});
            }
        }
    }
}

int main()
{
    n=rd(), m=rd(), q=rd();
    memset(hd, 0, sizeof(int)*(n+5));
    for (int i=0, x,y; i<m; ++i)
        adds(rd(), rd());
    Dijstra(1);
    int x,y;
    while (q--)
    {
        x=rd(),y=rd();
        if (y&1)
            puts(diso[x]<=y? "Yes":"No");
        else
            puts(dise[x]<=y? "Yes":"No");
    }
}