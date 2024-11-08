// LCA
#include <cstdio>
#include <vector>
#include <memory.h>

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
void printN(int n)
{
	if (n>9) printN(n/10);
	putchar((n%10)|48);
}
template<typename T>
inline void _min(T& a, const T& b)
  { if (b<a) a=b; }


typedef std::pair<int,int> pii;

constexpr int SIZE = 500005;

int pa[SIZE];
void init_set(int n)
{
    for (int i=0; i<=n; i+=2)
        pa[i]=i, pa[i|1]=i|1;
}
int fa(int x) {
	return x!=pa[x]?
		pa[x]=fa(pa[x]) : x;
}

int cnt=0, head[2*SIZE]{};
struct {
	int ver, nxt=0;
}ed[SIZE];
void add_edge(int a, int b)
{
	++cnt;
	ed[cnt] = {b, head[a]};
	head[a] = cnt;
}

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
	for (int i=head[r]; i; i=ed[i].nxt)
	{
		int y = ed[i].ver;
		if (vis[y]) continue;
		tarjin(y);
        pa[y] = r;
	}
	for (auto [y, id]: query[r])
		if (vis[y]==two)
			ans[id] = fa(y);
	vis[r] = two;
}

int main()
{
	int n=read(), m=read(), s=read();
    init_set(n);
	for (int i=1, x,y; i<n; ++i){
		x=read(); y=read();
		add_edge(x, y);
		add_edge(y, x);
	}
	for (int i=0, x,y; i<m; ++i)
	{
		x=read(); y=read();
		if (x==y) {
			ans[i] = x;
			continue;
		}
		query[x].push_back(std::make_pair(y,i));
		query[y].push_back(std::make_pair(x,i));
	}
	tarjan(s);
	for (int i=0; i<m; ++i)
		printN(ans[i]), putchar(10);
}
