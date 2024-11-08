
#include <cstdio>
#include <iostream>

typedef std::uint64_t ull;

#define int ull

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

template<typename T>
T gcd(T a, T b)
  { return !b? a:gcd(b, a%b); }
template<typename T>
inline T lcm(T a, T b)
  { return a/gcd(a,b)*b; }

constexpr int maxn = 1e6+5;

struct Fact
{
    ull a=0, b=1;
    Fact& operator+=(const Fact r)
    {
        ull c = lcm(b, r.b);
        auto c1=c/b, c2=c/r.b;
        a = a*c1 + r.a*c2,
        b = c;
        c = gcd(a,b);
        a/=c, b/=c;
        return *this;
    }
    Fact operator+(const Fact& r) const
    {
        Fact t = *this;
        return t+=r;
    }
    Fact operator/(ull n) const
    {
        Fact t=*this;
        return t/=n;
    }
    Fact& operator/=(ull n)
    {
        auto g = gcd(a, n);
        a /= g;
        b *= n/g;
        g = gcd(a, b);
        a/=g, b/=g;
        return *this;
    }
};

int qn=1, q2=0, que[maxn];
class Group
{
public:
    int n, m;
    Fact p[maxn];
    int ed[maxn][6];

    void solve()
    {
        int i=1;
        for (; i<=m; ++i)
        {
            int x = que[i];
            Fact sh{1, ed[x][0]};
            for (int j=1; j<=ed[x][0]; ++j)
                p[ed[x][j]] += sh;
        }
        for (; i<n; ++i)
        if (ed[i][0])
        {
            int x = que[i];
            Fact sh = p[x]/ed[x][0];
            for (int j=1; j<=ed[x][0]; ++j)
                p[ed[x][j]] += sh;
        }
    }

    void print()
    {
        for (int i=1; i<=n; ++i)
            if (!ed[i][0])
            printf("%llu %llu\n", p[i].a, p[i].b);
    }
}g;

void topo(Group& g)
{
    bool vis[maxn]{};
    int in[maxn]{};
    for (int i=1; i<=g.n; ++i)
        for (int j=1; j<=g.ed[i][0]; ++j)
            ++in[g.ed[i][j]];

    while (qn<=g.n)
        for (int i=1;i<=g.n; ++i)
            if (!vis[i] && in[i]==0)
            {
                vis[i]=true;
                que[qn]=i; ++qn;
                for (int j=1; j<=g.ed[i][0]; ++j)
                    --in[g.ed[i][j]];
            }
    int q2=1;
    while (g.ed[q2][0])
        ++q2;
    ::q2 = q2;
}
signed main()
{
    // freopen("P7113_9.ans", "w", stdout);
    int n=rd(), m=rd();
    g.n = n;
    g.m = m;
    for (int i=1; i<=n; ++i)
    {
        g.ed[i][0] = rd();
        for (int j=1; j<=g.ed[i][0]; ++j)
            g.ed[i][j] = rd();
    }
    topo(g);
    g.solve();
    g.print();
}