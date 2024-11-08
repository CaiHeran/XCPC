
#include <cstdio>

template<typename T=int>
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
template <typename T>
constexpr void print(T n)
{
	if (n>9)
        print(n/10);
	putchar(n%10|48);
}
template <class T>
inline void printl(T n)
    { print(n); putchar(10); }


//* 只支持单点修改的动态开点线段树
template<typename T>
class AutoSegTree
{
public:
    static constexpr int MAXN = 1e6, L = -1e9-1, R = 1e9+1;

    int cnt = 1;
    struct node{
        int ls=0, rs=0;
        T value=0;
    } tree[MAXN];

    void _down(int i)
    {
        if (!tree[i].ls)
            tree[i].ls = ++cnt;
        if (!tree[i].rs)
            tree[i].rs = ++cnt;
    }

public:
    void plus(const int n, const T add, int i=1, int cl=L, int cr=R)
    {
        tree[i].value += add;
        if (cl==cr) return;
        _down(i);
        int mid = (cl+cr-1)/2;
        if (mid>=n)
            plus(n,add, tree[i].ls, cl, mid);
        else
            plus(n,add, tree[i].rs, mid+1, cr);
    }

    T query(int l, int r, int i=1, int cl=L, int cr=R)
    {
        if (l<=cl && cr<=r)
            return tree[i].value;
        _down(i);
        int mid = (cl+cr-1)/2;
        if (mid>=r)
            return query(l,r,tree[i].ls, cl, mid);
        else if (mid<l)
            return query(l,r,tree[i].rs, mid+1, cr);
        else
            return query(l,r,tree[i].ls, cl, mid)
                 + query(l,r,tree[i].rs, mid+1, cr);
    }

    T total() const
      { return tree[1].value; }
};

///* 权值线段树
template<typename T>
class wAutoSegTree
{
public:
    static constexpr int L = AutoSegTree<T>::L, R = AutoSegTree<T>::R;

    AutoSegTree<T> tree_;

    void insert(T n)
        { tree_.plus(n, 1); }

    void remove(T n)
        { tree_.plus(n, -1); }

    int count_pre(T n)
        { return tree_.query(L, n-1); }

    int count_suc(T n)
        { return tree_.query(n+1, R); }

    int rank(T n)
        { return count_pre(n)+1; }

    T pre(T n)
        { return nth(count_pre(n)); }

    T suc(T n)
        { return nth(tree_.total() - count_suc(n) + 1); }

    T nth(int n, int i=1, int cl=L, int cr=R)
    {
        auto &tree = tree_.tree;
        if (cl==cr)
            return cl;
        tree_._down(i);
        int mid = (cl+cr-1)/2;
        if (n<=tree[tree[i].ls].value)
            return nth(n, tree[i].ls, cl, mid);
        else
            return nth(n - tree[tree[i].ls].value, tree[i].rs, mid+1, cr);
    }
};

int main()
{
    int q=rd();
    int max=-2147483647, min=2147483647;
    wAutoSegTree<int> tr;
    while (q--)
    {
    int t=rd(), x=rd();
    switch (t)
    {
    case 1: // 查询x数的排名
        printl(tr.rank(x));
        break;
    case 2: // 查询排名为x的数
        printl(tr.nth(x));
        break;
    case 3: // 求x的前驱
        if (x<=min) puts("-2147483647");
        else printl(tr.pre(x));
        break;
    case 4: // 求x的后继
        if (x>=max) puts("2147483647");
        else printl(tr.suc(x));
        break;
    case 5: // 插入一个数x
        if (x > max) max = x;
        if (x < min) min = x;
        tr.insert(x);
        break;
    }
    }
}