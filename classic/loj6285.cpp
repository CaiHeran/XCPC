/**
 * @file LOJ6285.cpp
 * @brief
 * @date 2022-08-18
 * 分块
 */

#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

template <class T=int>
T rd() {
    T s=-1,n; char c;
    while (c=getchar(), c<'0'||'9'<c)
        if (c=='-') s=1;
    n = '0'-c;
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 - (c-'0');
    return s*n;
}

constexpr int MAXN=100005, MAXL=320;

int n, us;
std::vector<int> pos[MAXN];
int a[MAXN];
int u[MAXN];
int h[MAXN];

int len;
int lm[MAXL];
struct {
    int operator[](int x) const noexcept
        { return (x-1)/len+1; }
} bel;

int f[MAXL][MAXL]; // f[i][j] = 块i..j的最小众数
int g[MAXL][MAXN]; // g[i][j] = 前i块中j的出现次数

void init()
{
    // discretize
    std::copy(a+1, a+n+1, u);
    std::sort(u, u+n);
    us = std::unique(u, u+n) - u;
    for (int i=1; i<=n; ++i)
        h[i] = std::upper_bound(u, u+us, a[i]) - u;

    for (int i=1; i<=n; ++i)
        pos[h[i]].push_back(i);

    len = std::sqrt(n);
    for (int i=1; i<=bel[n]; ++i)
        lm[i] = (i-1)*len+1;
    lm[bel[n]+1] = n+1;
}

int count(int l, int r, int x)
{
    return std::upper_bound(pos[x].begin(), pos[x].end(), r)
         - std::lower_bound(pos[x].begin(), pos[x].end(), l);
}

void initfg()
{
    for (int i = 1; i <= bel[n]; ++i)
      for (int j = 1; j <= us; ++j)
        g[i][j] = std::upper_bound(pos[j].begin(), pos[j].end(), lm[i+1]-1) - pos[j].begin();

    for (int i=1; i<=bel[n]; ++i)
    for (int j=i; j<=bel[n]; ++j)
    {
        int mm=0, mcnt=0; // min mode
        for (int k=lm[j]; k<lm[j+1]; ++k) {
            int cnt = g[j][h[k]] - g[i-1][h[k]];
            if (cnt>mcnt || (cnt==mcnt && h[k]<mm))
                mcnt = cnt, mm = h[k];
        }
        if (j > i) {
            int cnt = g[j][f[i][j-1]] - g[i-1][f[i][j-1]];
            if (cnt>mcnt || (cnt==mcnt && f[i][j-1]<mm))
                mm = f[i][j-1];
        }
        f[i][j] = mm;
    }
}

int query(int l, int r)
{
    int mm=0, mcnt=0, cnt;
    if (bel[l]==bel[r]) {
        for (int i=l; i<=r; ++i) {
            cnt = count(l, r, h[i]);
            if (cnt>mcnt || (cnt==mcnt && h[i]<mm))
                mm=h[i], mcnt=cnt;
        }
        return mm;
    }
    // 处理边角块
    for (int i=l; i<lm[bel[l]+1]; ++i) {
        cnt = count(l, r, h[i]);
        if (cnt>mcnt || (cnt==mcnt && h[i]<mm))
            mm=h[i], mcnt=cnt;
    }
    for (int i=lm[bel[r]]; i<=r; ++i) {
        cnt = count(l, r, h[i]);
        if (cnt>mcnt || (cnt==mcnt && h[i]<mm))
            mm=h[i], mcnt=cnt;
    }
    // 处理大整块
    if (bel[r]-bel[l] > 1) {
        int fm = f[bel[l]+1][bel[r]-1];
        cnt = count(l, r, fm);
        if (cnt>mcnt || (cnt==mcnt && fm<mm))
            mm = fm;
    }
    return mm;
}

int main()
{
    n=rd();
    std::generate_n(a+1, n, rd<std::int64_t>);
    init();
    initfg();
    for (int m=n, l,r; m--;)
    {
        l=rd(); r=rd();
        printf("%d\n", u[query(l, r)-1]);
    }
}