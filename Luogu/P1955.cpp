
#include <cstdio>
#include <vector>
#include <map>

typedef long long ll;

template <typename T=ll>
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

class Set
{
public:
    std::map<ll, ll> m;

    ll fa(int x)
    {
        if (m[x]==0)
            return m[x] = x;
        return x!=m[x]? m[x]=fa(m[x]) : x;
    }
    void merge(int a, int b)
        { m[fa(a)] = fa(b); }
    bool in_same_set(int a, int b)
        { return fa(a)==fa(b); }
};

int main()
{
    int t=rd();
while (t--)
{
    int n=rd();
    Set s;
    std::vector<std::pair<ll,ll>> v;
    while (n--)
    {
        int i=rd(), j=rd(), e=rd();
        if (e) s.merge(i, j);
        else v.emplace_back(i, j);
    }
    for (auto& p: v)
    {
        if (s.in_same_set(p.first, p.second))
        {
            puts("NO");
            goto End;
        }
    }
    puts("YES");
    End: continue;
}
}