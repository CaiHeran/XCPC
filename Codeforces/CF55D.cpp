/**
 * @file CF55D.cpp
 * @brief solution to CF55D Beautiful numbers
 * @date 2022-09-08
 * 数位DP
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <numeric>

// 千万记得开int64
using ll = std::int_fast64_t;
using std::lcm; // 开优化时更快

template <class T=ll>
T rd() {
    char c=getchar();
    while (c<'0'||'9'<c) c = getchar();
    T n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + c-'0';
    return n;
}

constexpr int MAXT{10}, MOD{2520};
constexpr std::int64_t MAXR = 9e18;

int nn[20];
int lcmap[MOD+1];
ll dp[20][2520][49];

void init()
{
    int num{0};
    for (int i=1; i<=MOD; ++i)
        if (MOD%i==0)
            lcmap[i] = num++;
    memset(dp, -1, sizeof(dp));
}
/**
 * @param pos 第pos位
 * @param mod 当前数对MOD的余数
 * @param lc 已有数位的lcm
 * @param mx 当前数位是否在最大边界
 */
ll dfs(int pos, int mod, int lc, bool mx)
{
    if (pos==-1) return mod%lc==0;
    if (!mx&&dp[pos][mod][lcmap[lc]]!=-1)
        return dp[pos][mod][lcmap[lc]];
    int mp = mx? nn[pos] : 9;
    ll cnt{0};
    for (int i=0; i<=mp; ++i)
    {
        int n_mod = (mod*10 +i)%MOD;
        int n_lcm = i? lcm(lc, i) : lc;
        cnt += dfs(pos-1, n_mod, n_lcm, mx&&i==mp);
    }
    if (!mx) dp[pos][mod][lcmap[lc]] = cnt; // dp数组对多组数据可以重复利用
    return cnt;
}

ll solve(ll n)
{
    int ln=0;
    for (ll i=n; i; i/=10)
        nn[ln++] = i%10;
    return dfs(ln-1, 0, 1, true);
}

int main()
{
    init();
    int t=rd();
    while (t--)
    {
        ll l=rd(), r=rd();
        printf("%lld\n", solve(r)-solve(l-1));
    }
}