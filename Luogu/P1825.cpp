
#include <cstdio>
#include <memory.h>
#include <iostream>
#include <queue>

int n, m;
struct Pos_ti {
    int x=0, y, t=0;
    constexpr Pos_ti(int x_=0, int y_=0, int t_=0)
        :x(x_), y(y_), t(t_) {}
    bool operator==(const Pos_ti& p) const
        { return x==p.x && y==p.y; }
    Pos_ti operator+(const Pos_ti p) const
        { return {x+p.x, y+p.y, t+p.t}; }
}tra[57], S, T;

char ma[302][302];
int t[302][302];

inline bool yes(Pos_ti p)
    { return 1<=p.x&&p.x<=n&&1<=p.y&&p.y<=m && ma[p.x][p.y]!='#'; }
void bfs()
{
    constexpr Pos_ti mov[4]{{1,0,0},{0,1,0},{-1,0,0},{0,-1,0}};

    memset(t, 0x3f, sizeof(t));
    t[S.x][S.y] = 0;
    
    std::queue<Pos_ti> q;
    q.emplace(S.x, S.y, 0);

    while (q.size())
    {
        Pos_ti cur = q.front();
        q.pop();
        if (cur.t > t[cur.x][cur.y])
            continue;
        int ct = cur.t + 1;
        if (std::int8_t n=ma[cur.x][cur.y]-'A'; 0<=n&&n<=25)
            cur = tra[n*2 + (tra[n*2]==cur)];
        cur.t=ct;
        for (auto mv: mov)
        {
            auto p = cur + mv;
            if (yes(p) && ct < t[p.x][p.y]) {
                t[p.x][p.y] = ct;
                q.push(p);
            }
        }
    }
}

int main()
{
    std::cin >> n >> m;
    for (int i=1; i<=n; ++i)
        for (int j=1; j<=m; ++j)
        {
            std::cin >> ma[i][j];
            char c = ma[i][j];
            if (c == '@')
                S = {i, j};
            else if (c == '=')
                T = {i, j};
            else if ('A'<=c && c<='Z') {
                tra[(c-'A')*2 + bool(tra[(c-'A')*2].x)] = {i, j};
            }
        }
    bfs();
    std::cout << t[T.x][T.y];
}