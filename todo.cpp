
#include<vector>
#include<algorithm>
#include<queue>
#include<cstdio>

int read()
{
    int n; char c=getchar();
    while (c<'0'||'9'<c)
        c = getchar();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + (c-'0');
    return n;
}

constexpr int maxn = 200010;
int n,m,cnt;
bool vis[maxn];
struct Edge {
    int u, v, dis;
    bool operator>(const Edge& e) const
      { return dis > e.dis; }
} edge[maxn];
struct Edg { int v, nxt; } ed[maxn];
int head[maxn], tot;
int verval[maxn], sf[maxn];
int fa[maxn], top[maxn], son[maxn];
int size[maxn], dep[maxn];

void add(int u, int v)
{
    ed[++tot].nxt = head[u];
    ed[tot].v = v;
    head[u] = tot;
}

int pa(int x)
{
    return x==sf[x]? x : (sf[x]=pa(sf[x]));
}

void dfs1(int u)
{
    size[u]=1; vis[u]=true;
    for(int i=head[u]; i; i=ed[i].nxt)
    {
        int v=ed[i].v;
        if(v==fa[u]) continue;
        dep[v] = dep[u]+1;
        fa[v] = u;
        dfs1(v);
        size[u] += size[v];
        if(size[v] > size[son[u]])
            son[u] = v;
    }
}

void dfs2(int u,int tp)
{
    top[u] = tp;
    if(son[u]) dfs2(son[u],tp);
    for(int i=head[u]; i; i=ed[i].nxt)
    {
        int v=ed[i].v;
        if(v==fa[u]||v==son[u])continue;
        dfs2(v,v);
    }
}

void Kruskal()
{
    sort(edge, edge+m, std::greater<Edge>());
    for(int i=0; i<=n; i+=2)
        sf[i]=i, sf[i|1]=i|1;
    for(int i=0;i<m;++i)
    {
        int fu=pa(edge[i].u), fv=pa(edge[i].v);
        if(fu!=fv)
        {
            verval[++cnt] = edge[i].dis;
            sf[cnt] = sf[fu] = sf[fv]=cnt;
            add(fu,cnt); add(cnt,fu);
            add(fv,cnt); add(cnt,fv);
        }
    }
    for(int i=1; i<=cnt; ++i)//注意图可能是个森林
        if(!vis[i])
        {
            int f=pa(i);
            fa[f] = 0;
            dfs1(f); dfs2(f, f);
        }
}

int LCA(int u, int v)
{
    while(top[u]!=top[v])
    {
        if(dep[top[u]] > dep[top[v]])
            u=fa[top[u]];
        else v=fa[top[v]];
    }
    return dep[u]<dep[v]? u:v;
}

int main()
{
    n=read(); m=read(); cnt=n;
    for(int i=0; i<m; i++)
        edge[i] = {read(), read(), read()};

    Kruskal();
    int q = read();
    while (q--)
    {
        int u=read(),v=read();
        if (pa(u)!=pa(v)) puts("-1");
        else printf("%d\n", verval[LCA(u,v)]);
    }
}