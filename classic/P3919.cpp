/**
 * @file P3919.cpp
 * @brief 可持久化数组模板
 * @date 2022-08-16
 * 可持久化线段树 可持久化数组
 */

#include <cstdio>
#include <algorithm>
#include <vector>

template <class T=int>
T rd()
{
    T s=1,n; char c;
    while (c=getchar(), c<'0'||'9'<c)
        if (c=='-') s=-1;
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + c-'0';
    return s*n;
}

constexpr int MAXN=1e6+5, MAXM=1e6+5;

int val[MAXN];

template <class T>
class PersArray
{
protected:
    int cnt{1};
    struct node {
        int ls, rs;
        T v;
    } tr[30000000];
public:
    void build(int l, int r, int rt=1) noexcept
    {
        if (l==r) {
            tr[rt].v = val[l];
            return;
        }
        tr[rt].ls = ++cnt;
        tr[rt].rs = ++cnt;
        int mid = (l+r)>>1;
        build(l, mid, tr[rt].ls);
        build(mid+1, r, tr[rt].rs);
    }
    int modify(int rt, int i, int x, int l, int r) noexcept
    {
        tr[++cnt] = tr[rt];
        rt = cnt;
        if (l==r)
            tr[rt].v = x;
        else {
            int mid = (l+r)>>1;
            if (i<=mid)
                tr[rt].ls = modify(tr[rt].ls, i, x, l, mid);
            else
                tr[rt].rs = modify(tr[rt].rs, i, x, mid+1, r);
        }
        return rt;
    }
    T get(int rt, int i, int l, int r) const noexcept
    {
        if (l==r) return tr[rt].v;
        int mid = (l+r)>>1;
        if (i<=mid)
            return get(tr[rt].ls, i, l, mid);
        else
            return get(tr[rt].rs, i, mid+1, r);
    }
};

int main()
{
    int n=rd(), m=rd();
    std::generate_n(val+1, n, rd<int>);
    PersArray<int> a;
    std::vector<int> vers{1};
    a.build(1, n);

    int v, t, i;
    while (m--)
    {
        v=rd(); t=rd(); i=rd();
        if (t==1) {
            vers.emplace_back(a.modify(vers[v], i, rd(), 1,n));
        }
        else {
            vers.push_back(vers[v]);
            printf("%d\n", a.get(vers[v], i, 1,n));
        }
    }
}