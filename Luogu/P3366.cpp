
#include <cstdio>
#include <algorithm>

struct Edge
{
    int start, target, weight;
    bool operator<(const Edge &e)const
      { return weight < e.weight; }
};

int n, m;
int p[5002]={0,1};     // 并查集
Edge edge[200002];

int pa(const int &x){
    return p[x] == x?
        x : p[x] = pa(p[x]);
}

int Kruskal()
{
    int Ans=0, v=1;
    int pa1, pa2;
    // 初始化并查集
    for (int i=2; i<=n; i+=2)
        p[i] = i, p[i|1] = i|1;
    for (int i=0; i<m; ++i)
    {
        pa1 = pa(edge[i].start),
        pa2 = pa(edge[i].target);
        if (pa1 != pa2)
        {
            p[pa2] = pa1; // merge
            Ans += edge[i].weight;
            ++v;
            if (v==n) return Ans;
        }
    }
    if (v<n)     // 若图不连通
        throw "orz";
    return Ans;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i=0; i<m; ++i)
        scanf("%d%d%d", &edge[i].start,&edge[i].target,&edge[i].weight);
    std::sort(edge, edge+m);

    try{ printf("%d", Kruskal()); }
    catch(const char *s){ puts(s); }
}