/**
 * @file P4513.cpp
 * @brief solution to P4513
 * @date 2022-07-24
 * 线段树
 */

#include <cstdio>
#include <vector>
#include <algorithm>

using std::max;

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

constexpr int MAXN = 5e5+2;
int n;
std::vector<int> sgo;

class SegTree
{
protected:
    struct node{
        int sum, max, maxl, maxr;
    } tr[MAXN<<2];
    void up(node &o, node& l, node& r) const noexcept
    {
        o.sum = l.sum + r.sum;
        o.maxl = max(l.maxl, l.sum+r.maxl);
        o.maxr = max(r.maxr, r.sum+l.maxr);
        o.max = max({l.max, r.max, o.maxl, o.maxr, l.maxr+r.maxl});
    }
public:
    void init(int l, int r, int rt=1) noexcept
    {
        if (l==r) {
            tr[rt] = {sgo[l], sgo[l], sgo[l], sgo[l]};
            return;
        }
        int mid = (l+r)>>1;
        const int L = rt<<1, R = rt<<1|1;
        init(l, mid, L);
        init(mid+1, r, R);
        up(tr[rt], tr[L], tr[R]);
    }

    void modify(int p, int s, int l, int r, int i=1) noexcept
    {
        if (l==r) {
            tr[i] = {s, s, s, s};
            return;
        }
        int mid = (l+r)>>1;
        const int L = i<<1, R = i<<1|1;
        if (p<=mid)
            modify(p, s, l, mid, L);
        else
            modify(p, s, mid+1, r, R);
        up(tr[i], tr[L], tr[R]);
    }

    node query(int l, int r, int cl, int cr, int i=1) const noexcept
    {
        if (l<=cl&&cr<=r) {
            return tr[i];
        }
        int mid = (cl+cr)>>1;
        if (r<=mid) return query(l, r, cl, mid, i<<1);
        if (l>mid) return query(l, r, mid+1, cr, i<<1|1);
        node nl=query(l, mid, cl, mid, i<<1), nr=query(l, r, mid+1, cr, i<<1|1);
        node t; up(t, nl, nr);
        return t;
    }
};

int main()
{
    n = rd();
    int m=rd();
    sgo.resize(n+1);
    for (int i=1; i<=n; ++i)
        sgo[i] = rd();
    SegTree tr;
    tr.init(1, n);

    while (m--) {
        int k=rd(), a=rd(), b=rd();
        if (k==1) {
            if (a>b) std::swap(a, b);
            printf("%d\n", tr.query(a, b, 1, n).max);
        }
        else {
            tr.modify(a, b, 1, n);
        }
    }
}