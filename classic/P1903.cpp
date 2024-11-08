/**
 * @file P1903.cpp
 * @brief solution to P1903 [国家集训队] 数颜色 / 维护队列
 * @date 2022-08-18
 * 带修改莫队
 */

#include <cstdio>
#include <cmath>
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

constexpr int MAXN{133333+6}, MAXM{133333+6}, MAX=1e6+2;

int n, m, len;
int c[MAXN];
int ans[MAXM];

struct Query {
    int l, r, t, id;
    bool operator<(const Query& q) const noexcept
    {
        if (l/len!=q.l/len) return l < q.l;
        if (r/len!=q.r/len) return (l/len)&1? r<q.r : r>q.r;;
        return t < q.t;
    }
};
struct Replace {
    int p, col;
};
std::vector<Query> q;
std::vector<Replace> rp;
int ucnt=0, buc[MAX]{}; // 可以离散化

inline void add(int x)
    { ucnt += !buc[c[x]]++; }
inline void del(int x)
    { ucnt -= !--buc[c[x]]; }
void replace(int ri, int l, int r)
{
    int p=rp[ri].p;
    if (l<=p && p<=r) {
        ucnt -= !--buc[c[p]];
        ucnt += !buc[rp[ri].col]++;
    }
    std::swap(c[p], rp[ri].col); //*
}

int main()
{
    n=rd(); m=rd();
    q.reserve(m);
    std::generate_n(c+1, n, rd<int>);
    for (int i=1; i<=m; ++i)
    {
        char t;
        do t=getchar(); while(t!='Q'&&t!='R');
        if (t=='Q')
            q.emplace_back(Query{rd(),rd(),rp.size()-1,q.size()+1});
        else
            rp.emplace_back(Replace{rd(),rd()});
    }
    len = n/std::cbrt(m)+1;  //
    std::sort(q.begin(), q.end());

    int l=1, r=0, t=-1;
    for (Query& q: ::q)
    {
        while (l<q.l) del(l++);
        while (l>q.l) add(--l);
        while (r<q.r) add(++r);
        while (r>q.r) del(r--);
        while (t<q.t) replace(++t, q.l, q.r);
        while (t>q.t) replace(t--, q.l, q.r);
        ans[q.id] = ucnt;
    }
    for (int i=1; i<=q.size(); ++i)
        printf("%d\n", ans[i]);
}