
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using std::min;
typedef std::int64_t int64;

template <class T>
void _max(T &a, const T &b)
    { if (a<b) a=b; }

template <typename T=int64>
T rd()
{
    T n; char c=getchar();
    while (c<'0'||'9'<c)
        c = getchar();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + c-'0';
    return n;
}

constexpr int MAXN = 5e3+5;

int n, w, s;
int64 a[MAXN];

int64 dp[MAXN][MAXN]; // 放入第x种原料，炉内的原料总数为y时，最大坚固值

void DP()
{
    memset(dp, 0xcf, sizeof dp);
    dp[0][0]=0;
    for (int i=1; i<=n; ++i)
        for (int j=min(i, w); j>=0; --j)
        {
            for (int k=min(w, j+s-1); k>=j-1; --k)
                _max(dp[i][j], dp[i-1][k]);
            dp[i][j] += a[i] * j;
        }
}

int main()
{
    n=rd(), w=rd(), s=rd();
    for (int i=1; i<=n; ++i)
        a[i] = rd();

    DP();
    int64 ans=INT64_MIN;
    for (int i=0; i<=w; ++i)
        _max(ans, dp[n][i]);
    printf("%lld", ans);
}