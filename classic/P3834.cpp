/**
 * @file P3834.cpp
 * @brief solution to P3834 【模板】可持久化线段树 2
 * @date 2022-08-16
 * 可持久化线段树
 */

#include <cstdio>
#include <algorithm>
#include <vector>

template <class T=int>
T rd() {
    T s=1,n; char c;
    while (c=getchar(), c<'0'||'9'<c)
        if (c=='-') s=-1;
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + c-'0';
    return s*n;
}

constexpr int MAXN=2e5+5, MAXM=2e5+5;

namespace pst
{
int cnt{1};
struct node {
    int cnt=0;
    int ls, rs;
} tr[10'000'000];

void build(int l, int r, int rt=1)
{
    tr[rt].cnt=0;
    if (l==r) return;
    int mid = (l+r)>>1;
    tr[rt].ls = ++cnt;
    tr[rt].rs = ++cnt;
    build(l, mid, tr[rt].ls);
    build(mid+1, r, tr[rt].rs);
}
int update(int rt, int i, int l, int r)
{
    tr[++cnt] = tr[rt];
    rt = cnt;
    tr[rt].cnt++;
    if (l < r)
    {
        int mid = (l+r)>>1;
        if (i<=mid) tr[rt].ls = update(tr[rt].ls, i, l, mid);
        else tr[rt].rs = update(tr[rt].rs, i, mid+1, r);
    }
    return rt;
}
//*利用可减性
int query(int u, int v, int k, int l, int r)
{
    if (l==r) return l;
    int mid = (l+r)>>1;
    int s = tr[tr[v].ls].cnt - tr[tr[u].ls].cnt;
    if (k<=s)
        return query(tr[u].ls, tr[v].ls, k, l, mid);
    else
        return query(tr[u].rs, tr[v].rs, k-s, mid+1, r);
}
} // pst

int n, m;
std::vector<int> u;
int a[MAXN];

int main()
{
    n=rd(); m=rd();
    std::generate_n(a+1, n, rd<int>);

    u.resize(n);
    std::copy(a+1, a+n+1, u.data());
    std::sort(u.begin(), u.end());
    u.erase(std::unique(u.begin(),u.end()), u.end());
    u.shrink_to_fit();

    std::vector<int> root{1};
    pst::build(1, u.size(), 1);

    for (int i=1; i<=n; ++i) {
        int re = std::upper_bound(u.begin(),u.end(),a[i]) - u.begin();
        root.emplace_back(pst::update(root[i-1], re, 1,u.size()));
    }
    while (m--) {
        int l=rd(), r=rd(), k=rd();
        printf("%d\n", u[pst::query(root[l-1],root[r],k, 1,u.size())-1]);
    }
}