/**
 * @file P3402.cpp
 * @brief solution to P3402 可持久化并查集
 * @date 2022-08-17
 * 可持久化并查集
 */
#include <cstdio>
#include <algorithm>
#include <vector>

template <class T=int>
T rd() {
    char c=getchar();
    while (c<'0'||'9'<c) c = getchar();
    T n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + c-'0';
    return n;
}

constexpr int MAXN=1e5+5, MAXM=2e5+5;

namespace PerUFSet
{
int N, cnt{1};
struct node {
    int ls, rs;
} tr[5'000'000];
struct data {
    int fa, rank;
} d[5'000'000];

namespace detail
{
void build(int l, int r, int rt=1)
{
    if (l==r) {
        d[rt]= {l, 1};
        return;
    }
    tr[rt] = {++cnt, ++cnt};
    int mid = (l+r)>>1;
    build(l, mid, tr[rt].ls);
    build(mid+1, r, tr[rt].rs);
}

int clone(int i)
{
    ++cnt;
    tr[cnt] = tr[i];
    d[cnt] = d[i];
    return cnt;
}
[[nodiscard]] int modifyfa(int rt, int i, int x, int l, int r)
{
    rt = clone(rt);
    if (l==r)
        d[rt].fa = x;
    else {
        int mid = (l+r)>>1;
        if (i<=mid)
            tr[rt].ls = modifyfa(tr[rt].ls, i, x, l, mid);
        else
            tr[rt].rs = modifyfa(tr[rt].rs, i, x, mid+1, r);
    }
    return rt;
}
/**
 * @param nl 记录modifyfa之前的cnt。若要访问的node的id<=nl，则该node是以前版本的，需要复制。
 */
void updaterank(int rt, int i, int nl, int l, int r)
{
    if (l==r) {
        d[rt].rank++;
        return;
    }
    int mid = (l+r)>>1;
    if (i<=mid) {
        if (tr[rt].ls<=nl) tr[rt].ls = clone(tr[rt].ls);
        updaterank(tr[rt].ls, i, nl, l, mid);
    }
    else {
        if (tr[rt].rs<=nl) tr[rt].rs = clone(tr[rt].rs);
        updaterank(tr[rt].rs, i, nl, mid+1, r);
    }
}

int getid(int rt, int i, int l, int r)
{
    if (l==r) return rt;
    int mid = (l+r)>>1;
    if (i<=mid)
        return getid(tr[rt].ls, i, l, mid);
    else
        return getid(tr[rt].rs, i, mid+1, r);
}
} // namespace detail

void build(int n) { N = n; detail::build(1, n, 1); }

int find(int rt, int x)
{
    int fid = detail::getid(rt, x, 1,N);
    return x==d[fid].fa? fid : find(rt, d[fid].fa);
}
[[nodiscard]] int merge(int rt, int u, int v)
{
    int fuid=find(rt, u), fvid=find(rt, v);
    if (fuid==fvid) return rt;
    if (d[fuid].rank > d[fvid].rank)
        std::swap(fuid, fvid);
    int nl = cnt;
    int new_rt = detail::modifyfa(rt, d[fuid].fa, d[fvid].fa, 1,N);
    detail::updaterank(new_rt, d[fvid].fa, nl, 1,N);
    return new_rt;
}
} // PerUFSet

int main()
{
    int n=rd(), m=rd();
    std::vector<int> vers{1};
    vers.reserve(m+1);
    using namespace PerUFSet;
    build(n);
    while (m--)
    {
        switch (rd()) {
        case 1: // merge
            vers.push_back(merge(vers.back(), rd(), rd()));
            break;
        case 2: // rollback
            vers.push_back(vers[rd()]);
            break;
        case 3: // query
            vers.push_back(vers.back());
            printf("%d\n",find(vers.back(),rd())==find(vers.back(),rd()));
            break;
        }
    }
}