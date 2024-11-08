/**
 * @file P3901.cpp
 * @brief solution to P3901 数列找不同
 * @date 2022-08-18
 * 普通莫队 思维题
 * 莫队能过，但也有O(n+q)的方法。
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

template <class T=int>
T rd() {
    char c=getchar();
    while (c<'0'||'9'<c) c = getchar();
    T n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + c-'0';
    return n;
}

constexpr int MAXN=1e5+5, MAXQ=1e5+5;

int n, qn, len;
int a[MAXN];
struct Query {
    int l, r, id;
    bool operator<(const Query& q) const noexcept
    {
        if (l/len!=q.l/len) return l/len < q.l/len;
        return (l/len)&1? r < q.r : r > q.r;
    }
} q[MAXQ];

bool ans[MAXQ];
int ucnt=0, cnt=0, buc[MAXN]{};

void add(int x)
{
    cnt++;
    ucnt += !buc[x]++;
}
void del(int x)
{
    ucnt -= !--buc[x];
    cnt--;
}

int main()
{
    n=rd(); qn=rd();
    len = sqrt(n)+0.5;
    std::generate_n(a+1, n, rd<int>);
    for (int i=1; i<=qn; ++i)
        q[i] = {rd(), rd(), i};
    std::sort(q+1, q+qn+1);

    int l=1, r=0;
    for (int i=1; i<=qn; ++i)
    {
        while (l < q[i].l) del(a[l++]);
        while (l > q[i].l) add(a[--l]);
        while (r < q[i].r) add(a[++r]);
        while (r > q[i].r) del(a[r--]);
        ans[q[i].id] = ucnt==cnt;
    }
    for (int i=1; i<=qn; ++i)
        puts(ans[i]? "Yes":"No");
}