
/*
  一个含有 n 项的数列，求出每一项前的 m 个数到它这个区间内的最小值。
若前面的数不足 m 项则从第 1 个数开始，若前面没有数则输出 0。

$ 1≤m≤n≤2×10^6, 1≤a_i≤3×10^7, 1<a_i<3*10^7, 1≤a_i​≤3×10^7 $
*/

#include <cstdio>
#include <deque>
#include <algorithm>

template <typename T=int>
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
void print(T n)
{
    if (n>9)
        print(n/10);
    putchar(n%10|48);
}
template <class T>
inline void printl(T n)
    { print(n); putchar(10); }


constexpr int MAXN = 2e6+2;

int n, m;
int a[MAXN];

struct vx {
    int v, x;
};
void solve()
{
    std::deque<vx> q;
    printl(0);
    for (int i=1; i<n; ++i)
    {
        while (!q.empty() && q.back().v >= a[i])
            q.pop_back();
        q.push_back({a[i], i});
        while (!q.empty() && q.front().x <= i-m)
            q.pop_front();
        printl(q.front().v);
    }
}

int main()
{
    n=rd(); m=rd();
    std::for_each(a+1, a+n+1, [](int& n){n=rd();});
    solve();
}