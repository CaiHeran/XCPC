
#include <cstdio>
#include <queue>

template <typename T=int>
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

int main()
{
    using namespace std;
    int n=rd(), a=rd(), b=rd();
    if (a==b) { printf("0"); return 0; }
    int c[201];
    for (int i=1; i<=n; ++i)    
        c[i] = rd();

    bool vis[201]{}; vis[a]=true;
    queue<pair<int,int> > q;
    q.emplace(a, 0);
    while (q.size())
    {
        int s = q.front().first;
        int t = 1+q.front().second;
        q.pop();
        int x;
        if (x=s-c[s], x>=1 && !vis[x]) {
            if (x==b) { printf("%d", t); return 0; }
            vis[x] = true;
            q.emplace(x, t);
        }
        if (x=s+c[s], x<=n && !vis[x]) {
            if (x==b) { printf("%d", t); return 0; }
            vis[x] = true;
            q.emplace(x, t);
        }
    }
    printf("-1");
}