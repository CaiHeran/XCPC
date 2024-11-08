#include <cstdio>
#include <iostream>
#include <memory.h>

template<typename T=int>
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

template<typename T>
inline T rd(T& n)
{
    return n = rd<T>();
}

int m;
std::int8_t col[1001][1001];
int cost[1001][1001];
bool vis[1001][1001];
void dfs(int fl, int x, int y, std::int8_t co, int cos, bool able);
inline void ttt(int fl, int x, int y, std::int8_t co, int cos, bool able)
{
    if (!vis[x][y] && cos<cost[x][y])
    {
        if (col[x][y]==co)
            vis[x][y]=1, dfs(fl, x, y, co, cos, true), vis[x][y]=0;
        else if (col[x][y])
            vis[x][y]=1, dfs(fl, x, y, col[x][y], cos+1, true), vis[x][y]=0;
        else if (able)
            vis[x][y]=1, dfs(fl, x, y, co, cos+2, false), vis[x][y]=0;
    }
}
void dfs(int fl, int x, int y, std::int8_t co, int cos, bool able)
{
    if (cos>=cost[x][y]) return;
    cost[x][y] = cos;
    if (x==m&&y==m) return;
    if (fl!=1 && x>1)
        ttt(2, x-1, y, co, cos, able);
    if (fl!=2 && x<m) 
        ttt(1, x+1, y, co, cos, able);
    if (fl!=3 && y>1)
        ttt(4, x, y-1, co, cos, able);
    if (fl!=4 && y<m)
        ttt(3, x, y+1, co, cos, able);
}

int main()
{
    rd(m);
    int n=rd();
    for (int x,y, i=0; i<n; ++i)
    {
        rd(x),rd(y);
        col[x][y] = rd()? 1:2;
    }
    vis[1][1]=1;
    memset(cost, 0x3f, sizeof(cost));
    dfs(1, 1, col[1][1], 0, true);
    auto ans = cost[m][m];
    printf("%d", ans<0x3f3f3f3f? ans:-1);
}