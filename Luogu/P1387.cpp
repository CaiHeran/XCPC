
#include <cstdio>
#include <iostream>
#include <algorithm>

using std::min;

template<class T>
inline void _max(T& a, const T& b)
    { if (a<b) a=b; }

template <typename T=int>
T rd()
{
    char c=getchar();
    while (c<'0'||'9'<c)
        c = getchar();
    return c-'0';
}

int main()
{
    int n, m;
    std::int_fast8_t ma[101][101];
    int dp[101][101]{};
    std::cin >> n >> m;
    for (int i=1; i<=n; ++i)
        for (int j=1; j<=m; ++j)
            ma[i][j] = rd();
    int ans=0;
    for (int i=1; i<=n; ++i)
        for (int j=1; j<=m; ++j) {
            dp[i][j] = ma[i][j]*(1+min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]}));
            _max(ans, dp[i][j]);
        }

    printf("%d", ans);
}