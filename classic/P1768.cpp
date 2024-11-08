/**
 * @file P1768.cpp
 * @brief solution to P1768 天路
 * @date 2022-10-13
 * 0/1分数规划 判负环
 */

#include <cstdio>
#include <bitset>
#include <queue>
#include <vector>

template <class T=int>
T rd() {
    char c;
    while (c=getchar(), c<'0'||'9'<c);
    T n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + c-'0';
    return n;
}

constexpr int MAXN{7001}, MAXM{20001};

int n, m;
struct EdgeInfo {
    short to, v, p;
};
std::vector<EdgeInfo> g[MAXN+1];

void add_ed(short s, short t, short v, short p)
{
    g[s].push_back({t, v, p});
}

std::bitset<MAXN+1> inq;
short cnt[MAXN+1];
double dist[MAXN+1];

bool check(double x)
{
    inq.reset();
    std::fill_n(cnt, n+1, 0);
    std::fill_n(dist+1, n, 2e8);
    std::queue<short> q;
    q.push(0);
    inq[0] = 1;
    dist[0] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for (auto& e: g[u])
        {
            int t = e.to;
            double w = x*e.p - e.v;
            if (dist[t] > dist[u] + w) {
                dist[t] = dist[u] + w;
                if (!inq[t]) {
                    cnt[t] = 1+cnt[u];
                    if (cnt[t] > n)
                        return false;
                    inq[t] = 1;
                    q.push(t);
                }
            }
        }
    }
    return true;
}

int main()
{
    n=rd(); m=rd();
    for (int i=1; i<=n; i++)
        g[0].emplace_back(i, 0, 0);
    for (int i=1; i<=m; i++)
    {
        short a=rd(), b=rd(), v=rd(), p=rd();
        g[a].emplace_back(b, v, p);
    }

    double l=0, r=200., mid;
    while (l < r-0.01)
    {
        mid = (l+r)/2;
        if (check(mid))
            r = mid;
        else
            l = mid;
    }
    if (!l) printf("-1");
    else printf("%.1lf", r);
}