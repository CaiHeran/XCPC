#include <cstdio>
#include <vector>

template <class T>
constexpr void minen(T &a, const T& b)
    { if (b<a) a=b; }

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
template <class T>
void print(T n)
{
    if (n>9) print(n/10);
    putchar(n%10|48);
}

constexpr int MAXN = 2e4+1, MAXM = 2e5+1;

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
inline void add_eds(int x, int y)
{
    add_ed(x, y);
    add_ed(y, x);
}

unsigned num=0, dfn[MAXN]{}, low[MAXN];
bool is_cut[MAXN]{};

void tarjan_cut(int u, int fa=0)
{
    dfn[u] = low[u] = ++num;
    int children = 0;

    for (int i=hd[u]; i; i=ed[i].nxt)
    {
        int v = ed[i].v;
        if (v == fa) continue;
        if (!dfn[v]) // 树边
        {
            ++children;
            tarjan_cut(v, u);
            minen(low[u], low[v]);

            if (low[v] >= dfn[u]) // u是割点
            {
                is_cut[u] = true;
            }
        }
        else
            minen(low[u], dfn[v]);
    }

    if (fa==0 && children <=1)
        is_cut[u] = false;
}

int main()
{
    int n=rd(), m=rd();
    while (m--)
        add_eds(rd(), rd());

    for (int i=1; i<=n; ++i)
        if (dfn[i]==0) {
            tarjan_cut(i);
        }

    std::vector<unsigned> cuts;
    for (int i=1; i<=n; ++i)
        if (is_cut[i])
            cuts.push_back(i);

    print(cuts.size()); putchar(10);
    for (auto&&n: cuts)
        print(n), putchar(' ');
}