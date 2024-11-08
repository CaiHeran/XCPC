// 没有上司的舞会
// 树形DP

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

template <typename T=int>
T rd()
{
    T f=1, n; char c;
    while (c=getchar(), c<'0'||'9'<c)
        if (c=='-') f=-1;
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + (c-'0');
    return f*n;
}

using std::max;

constexpr int MAXN = 6e3+1;

int n;
std::vector<int> tr[MAXN];
int r[MAXN];

int dp[MAXN][2];

void DP(int p)
{
    dp[p][0] = 0;
    dp[p][1] = r[p];
    for (int i: tr[p])
    {
        DP(i);
        dp[p][0] += max(dp[i][0], dp[i][1]);
        dp[p][1] += dp[i][0];
    }
}

int main()
{
    n = rd();
    std::for_each(r+1, r+n+1, [](auto &n){n=rd();});

    int root;
    {
    bool not_root[MAXN]{};
    for (int l,k, i=n+2; i<=2*n; ++i)
    {
        l=rd(); k=rd(); // l的直接上司是k
        not_root[l] = true;
        tr[k].push_back(l);
    }
    for (int i=1; i<=n; ++i)
        if (!not_root[i]) {
            root = i;
            break;
        }
    }
    DP(root);
    std::cout << max(dp[root][0], dp[root][1]) << std::flush;
}