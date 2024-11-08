
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

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

constexpr int SIZE = 5001;
int tot, t;
int fa[SIZE][20], dep[SIZE], dist[SIZE];
int vs, ver[2*SIZE], verv[2*SIZE], nxt[4*SIZE], edge[4*SIZE], head[SIZE];

int n, p[SIZE*2];
void add_edge(int x, int y, int z)
{
    ++tot;
    ver[tot]=y;
    edge[tot]=z;
    nxt[tot]=head[x];
    head[x]=tot;
}
void add_edge_ver(int x, int y, int z)
{
    ++vs;
    verv[vs] = z;
    add_edge(vs, x, 1);
    add_edge(x, vs, 1);
    add_edge(vs, y, 1);
    add_edge(y, vs, 1);
    p[x] = vs;
    p[y] = vs;
}

void init_set(int n)
{
    for (int i=0; i<=n; i+=2)
        p[i]=i, p[i|1]=i|1;
}
int pa(int x)
{
    return x==p[x]?
        x : (p[x]=pa(p[x]));
}

struct Edge{
    int u, v, w;
    bool operator<(const Edge &e) const
        { return w < e.w; }
};

void Kruskal_tree(const Edge *edges, int en)
{
    init_set(n*2);
    for (int i=0; i<en; ++i)
    {
        int fa1=pa(edges[i].u), fa2=pa(edges[i].v);
        if (fa1!=fa2)
            add_edge_ver(fa1, fa2, edges[i].w);
    }
}

typedef std::pair<int,int> pii;

int ans[SIZE];
// query[x][i].first表示有一个求LCA(x, query[x][i].first)的询问
// query[x][i].second表示这个询问的答案存储在ans[query[x][i].second]
std::vector<pii> query[SIZE];
enum {
	none=0,
	one,
	two
}vis[SIZE]{};

void tarjan(int r)
{
	vis[r] = one;
	for (int i=head[r]; i; i=nxt[i])
	{
		int y = ver[i];
		if (vis[y]) continue;
		tarjan(y);
        p[y] = r;
	}
	for (auto [y, id]: query[r])
		if (vis[y]==two)
			ans[id] = pa(y);
	vis[r] = two;
}

int main()
{
	int n=read(), m=read();
    vs = n;
	Edge e[m];
	for (int i=0; i<m; ++i)
		e[i] = {read(),read(),read()};
	std::sort(e, e+m);
	Kruskal_tree(e, m);
	for (int i=0, x,y; i<m; ++i)
	{
		x=read(); y=read();
		if (x==y) {
			ans[i] = 0;
			continue;
		}
		query[x].push_back(std::make_pair(y,i));
		query[y].push_back(std::make_pair(x,i));
	}
	init_set(n*2);
	for (int i=1; i<=n; ++i)
		if (i==p[i])
			tarjan(i);
	for (int i=0; i<m; ++i)
		printf("%d\n", verv[ans[i]]);
    for (int i=0; i<=2*n; ++i)
        printf("%d ", verv[i]);
}
