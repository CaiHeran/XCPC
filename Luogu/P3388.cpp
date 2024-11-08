#include <memory.h>
#include <cstdio>

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

template<class T>
constexpr void _min(T& a, const T& b)
    { if (a>b) a=b; }

constexpr int MAXN = 2e4+9, MAXM = 1e5+9;

int n;
int root;
int _cnt=0, hd[MAXN];
struct Edge {
    int v, nxt=-1;
} ed[2*MAXM];

void add_ed(int u, int v)
{
    ed[_cnt] = {v, hd[u]};
    hd[u] = _cnt;
    ++_cnt;
}
void add_eds(int x, int y)
{
    if (x!=y)
        add_ed(x, y),
        add_ed(y, x);
}

int num=0, dfn[MAXN]{}, low[MAXN];
bool is_cut[MAXN]{};
void tarjan_cut(int x)
{
    dfn[x] = low[x] = ++num;
    int flag=0;
    for (int i=hd[x]; ~i; i=ed[i].nxt)
    {
        int v = ed[i].v;
        if (!dfn[v])
        {
            tarjan_cut(v);
            _min(low[x], low[v]);
            if (dfn[x] <= low[v])
            {
                ++flag;
                if (x!=root || flag>1)
                    is_cut[x] = true;
            }
        }
        else _min(low[x], dfn[v]);
    }
}

int main()
{
    memset(hd, -1, sizeof(hd));

    n = rd();
    int m = rd();
    while (m--)
        add_eds(rd(), rd());

    for (int i=1; i<=n; ++i)
        if (!dfn[i])
            root=i, tarjan_cut(i);

    int cnt_cut=0;
    for (int i=1; i<=n; ++i)
        cnt_cut += is_cut[i];
    printf("%d\n", cnt_cut);

    for (int i=1; i<=n; ++i)
        if (is_cut[i])
            printf("%d ", i);
}