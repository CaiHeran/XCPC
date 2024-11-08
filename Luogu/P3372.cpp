
#include <cstdio>
#include <iostream>
#include <stdint.h>

typedef long long ll;

const uint32_t StartAt = 1;

int *val;

struct
{
    int l,r;
    ll sum,add=0ll;
}a[100002*4];

/** @brief 构建线段树
 * 使用方法：build(1,1,n)
 */
void build(const int l, const int r, const uint32_t i=StartAt) // i: 当前点编号
{
    a[i].l = l,
    a[i].r = r;
    if (l==r){
        a[i].sum = val[l];
        return;
    }
    int mid = (l+r)>>1;
    build(l, mid, i<<1);
    build(mid+1, r, i<<1|1);
    a[i].sum = a[i<<1].sum + a[i<<1|1].sum;
}

/**
 * @note 在修改和查询时，只要进入子节点，就一定要`down`
 */
inline void down(const uint32_t i)
{
    if (a[i].add){
        ll &x = a[i].add;
        a[i<<1].add += x;
        a[i<<1|1].add += x;
        a[i<<1].sum += (a[i<<1].r -a[i<<1].l +1)*x;
        a[i<<1|1].sum += (a[i<<1|1].r -a[i<<1|1].l +1)*x;

        a[i].add = 0;
    }
}

inline void up(const uint32_t i)
{
    a[i].sum = 0;
    if (a[i<<1].l)
        a[i].sum += a[i<<1].sum;
    if (a[i<<1|1].l)
        a[i].sum += a[i<<1|1].sum;
}

/** @brief 区间修改
 * @param l 左端点（起始位置）
 * @param r 右端点（终止位置）
 * @param add 变化量
 */
void updata(const int l, const int r, const ll add, const uint32_t i=StartAt)
{
    if (a[i].l==l && a[i].r==r){
        a[i].sum += (a[i].r - a[i].l +1) * add;
        a[i].add += add;
        return;
    }
    down(i);
    int mid = (a[i].l + a[i].r) >> 1;
    if (mid >= r)
        updata(l, r, add, i<<1);
    else if (mid < l)
        updata(l, r, add, i<<1|1);
    else
        updata(l, mid, add, i<<1),
        updata(mid+1, r, add, i<<1|1);
    up(i);
}

/** @brief 区间查询
 * @param l 所查询区间的左端点
 * @param r 所查询区间的右端点
 */
ll query(const int l, const int r, const uint32_t i=StartAt)
{
    if (a[i].l==l && a[i].r==r)
        return a[i].sum;

    down(i);
    int mid = (a[i].l + a[i].r) >> 1;
    if (mid >= r)
        return query(l, r, i<<1);
    else if (mid < l)
        return query(l, r, i<<1|1);

    return query(l, mid, i<<1)
          +query(mid+1, r, i<<1|1);
}


int main()
{
    using namespace std;
    freopen("data/P3372_1.in", "r", stdin);
    int n,m, c,x,y;
    ll k;
    cin >> n >> m;
    val = new int[n+2];
    for (int i=1; i<=n; ++i)
        cin >> val[i];
    build(1,n);
    delete val;

    while (m--){
        cin >> c >> x >> y;
        if (c==1){
            cin >> k;
            updata(x, y, k, 1);
        }
        else{
            cout << query(x, y) << endl;
        }
    }
}