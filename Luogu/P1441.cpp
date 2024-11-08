//
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <bitset>

template <class T>
constexpr void maxen(T& a, const T& b)
    { if (a<b) a=b; }

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

int n, m;
int ans=0;
int a[22];
bool rem[22]{}; // remove

void DP()
{
    std::bitset<2002> dp{};
    dp[0] = true;
    for (int i=1; i<=n; ++i)
        if (!rem[i])
            dp |= dp<<a[i]; // ???
    maxen(ans, (int)dp.count()-1);
}

void dfs(int p, int c)
{
    if (c > m || n-p+c+1 < m) return;
    if (p == n) {
        if (c == m)
            DP();
        return;
    }
    rem[p] = true;
    dfs(p+1, c+1);
    rem[p] = false;
    dfs(p+1, c);
}

int main()
{
    using namespace std;
    n = rd(); m = rd();
    for_each(a+1, a+n+1, [](auto &n){ n=rd(); });
    sort(a+1, a+n+1);
    dfs(1, 0);
    cout << ans;
}