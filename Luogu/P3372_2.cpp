#include <iostream>
#include <cstdio>

long long readN()
{
    long long n; char c=getchar();
    while (c<'0'||'9'<c)
        c = getchar();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + (c-'0');
    return n;
}
template<typename T>
void printN(T n)
{
    if (n>9) printN(n/10);
    putchar((n%10)|48);
}

constexpr int MAXN = 1e5+1;

long long val[MAXN];

template<typename T>
class SegmentTree
{
protected:
    struct {
        T sum=0, plus=0;
    } tree[MAXN*4];

    void up(T rt)
    {
        tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
    }
    void down(int rt, int cl, int cr)
    {
        if (tree[rt].plus) {
            T plus = tree[rt].plus;
            tree[rt].plus = 0;
            int L=rt<<1, R=rt<<1|1;
            int mid = (cl+cr)>>1;
            tree[L].sum += (mid-cl+1)*plus;
            tree[L].plus += plus;
            tree[R].sum += (cr-mid)*plus;
            tree[R].plus += plus;
        }
    }

public:
    const int N;
    SegmentTree(int n) : N(n) {};
    void build() { build(1, N, 1); }
    void build(int cl, int cr, int rt)
    {
        if (cl==cr) {
            tree[rt].sum = val[cl];
            return;
        }
        int mid = (cl+cr)>>1;
        build(cl, mid, rt<<1);
        build(mid+1, cr, rt<<1|1);
        up(rt);
    }

    void plus(int l, int r, T add)
      { plus(l, r, add, 1, N, 1); }
    void plus(int l, int r, T add, int cl, int cr, int rt)
    {
        if (l==cl && r==cr){
            tree[rt].sum += (cr-cl+1)*add;
            tree[rt].plus += add;
            return;
        }
        down(rt, cl, cr);
        int mid = (cl+cr)>>1;
        if (r<=mid) plus(l, r, add, cl, mid, rt<<1);
        else if (l>mid) plus(l, r, add, mid+1, cr, rt<<1|1);
        else plus(l, mid, add, cl, mid, rt<<1),
            plus(mid+1, r, add, mid+1, cr, rt<<1|1);
        up(rt);
    }

    T query(int l, int r)
      { return query(l, r, 1, N, 1); }
    T query(int l, int r, int cl, int cr, int rt)
    {
        if (l==cl && r==cr)
            return tree[rt].sum;
        down(rt, cl, cr);
        int mid = (cl+cr)>>1;
        if (r<=mid) return query(l, r, cl, mid, rt<<1);
        if (l>mid) return query(l, r, mid+1, cr, rt<<1|1);
        return query(l, mid, cl, mid, rt<<1) + query(mid+1, r, mid+1, cr, rt<<1|1);
    }
};

int main()
{
    int n=readN(), m=readN();
    SegmentTree<long long> st(n);
    for (int i=1; i<=n; ++i)
        val[i] = readN();
    st.build();
    int f, x, y;
    while (m--)
    {
        f=readN(), x=readN(), y=readN();
        if (f==2)
            printN(st.query(x, y)), putchar(10);
        else
            st.plus(x, y, readN());
    }
}