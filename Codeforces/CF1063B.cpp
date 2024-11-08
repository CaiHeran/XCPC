/**
 * @file CF1063B.cpp
 * @brief solution to CF1063B Labyrinth
 * @date 2022-10-11
 * 0/1BFS
 */

#include <cstdio>
#include <algorithm>
#include <bitset>
#include <queue>

template <class T=int>
T rd() {
    char c;
    while (c=getchar(), c<'0'||'9'<c);
    T n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + c-'0';
    return n;
}
template <class T>
constexpr void _min(T& a, const T& b)
    { if (b<a) a=b; }

constexpr int MAXN{2001}, MAXM{2001};

std::bitset<MAXM> ma[MAXN+1];
int dist[MAXN+1][MAXM+1];

int main()
{
    int n=rd(),m=rd(),x0=rd(),y0=rd(),l=rd(),r=rd();
    for (int i=1; i<=n; i++) {
        char s[MAXM+2];
        scanf("%s", s+1);
        for (int j=1; j<=m; j++)
            ma[i][j] = s[j]=='.';
    }
    std::fill(dist[1], dist[n+1], 0x7ffffff0);
    dist[x0][y0] = 0;
    std::deque<std::pair<short,short> >q;
    q.emplace_back(x0, y0);
    while (!q.empty())
    {
        constexpr std::pair<int,int> trans[4]{{0,-1},{0,1},{-1,0},{1,0}};
        int x1=q.front().first, y1=q.front().second;
        q.pop_front();
        for (int t=0; t<4; t++)
        {
            int x=x1+trans[t].first, y=y1+trans[t].second;
            if (x<1||x>n||y<1||y>m||ma[x][y]==0) continue;
            if (t==0) {
                if (dist[x][y] > dist[x1][y1]+1) {
                    dist[x][y] = dist[x1][y1]+1;
                    q.emplace_back(x, y);
                }
            }
            else
            if (dist[x][y] > dist[x1][y1]) {
                dist[x][y] = dist[x1][y1];
                q.emplace_front(x, y);
            }
        }
    }
    int cnt{0};
    for (int x=1; x<=n; x++)
        for (int y=1; y<=m; y++)
        {
            int l1=dist[x][y], r1=l1+y-y0;
            cnt += l1<=l && r1<=r;
        }
    printf("%d", cnt);
}