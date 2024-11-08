// 最短路
#include <cstdio>
#include <cstring>
#include <queue>

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

constexpr int MAXN = 1000002, MAXM = 2000002;
constexpr int MOD = 100003;

int n, m;
int en, hd[MAXN]{};
struct Edge {
    int v, nxt;
} ed[MAXM*2];

void add_ed(int u, int v)
{
    ++en;
    ed[en] = {v, hd[u]};
    hd[u] = en;
}
void add_eds(int x, int y)
{
    add_ed(x, y);
    add_ed(y, x);
}

int dis[MAXN];
int cnt[MAXN]{};

void solve(int s=1)
{
    memset(dis, 0x3f, sizeof(int)*(n+1));
    dis[s] = 0;
    cnt[s] = 1;

    std::queue<int> q;
    q.push(s);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        int d = dis[u] + 1;
        for (int i=hd[u], v; i; i=ed[i].nxt)
        {
            v=ed[i].v;
            if (d < dis[v])
            {
                dis[v] = d;
                cnt[v] = cnt[u];
                q.push(v);
            }
            else if (d == dis[v])
            {
                cnt[v] += cnt[u];
                if (cnt[v] >= MOD)
                    cnt[v] -= MOD;
            }
        }
    }
}

int main()
{
    n=rd(); m=rd();
    while (m--)
        add_eds(rd(), rd());

    solve();

    for (int i=1; i<=n; ++i)
        printf("%d\n", cnt[i]);
}
/*
input:
5 7
1 2
1 3
2 4
3 4
2 3
4 5
4 5
output:
1
1
1
2
4
*/