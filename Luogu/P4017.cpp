#include <cstdio>
#include <queue>
#include <vector>

int read()
{
	int n; char c=getchar();
	while (c<'0'||'9'<c)
		c = getchar();
	n = c-'0';
	while (c = getchar(), '0'<=c&&c<='9')
		n = n*10 + (c-'0');
	return n;
}

int n;
int cnt=0;
int sum[5001]{};
std::vector<int> m[5001];
int in[5001]{};

void topo(std::queue<int>& q)
{
	int num=0;
	bool inque[5001]{};
	
	for (int i=1; i<=n; ++i)
		if (in[i]==0)
			sum[i]=1;
	
	while (true)
	for (int i=1; i<=n; ++i)
		if (in[i]==0 && !inque[i]){
			q.push(i), inque[i]=true;
			++num;
			if (num==n) return;
			for (int& c: m[i])
				--in[c];
		}
}

void bfs()
{
	std::queue<int> q;
	topo(q);
	int x;
	while (!q.empty())
	{
		x=q.front();
		q.pop();
		for (int& c: m[x])
			sum[c] = (sum[c]+sum[x])%80112002;
	}
}

int main()
{
	n=read();
	int t=read();
	for (int a,b, i=0; i<t; ++i)
	{
		a=read(), b=read();
		m[a].push_back(b);
		++in[b];
	}
	std::vector<int> v;	// I'm lazy.
	for (int i=1; i<=n; ++i)
		if (m[i].empty())
			v.push_back(i);
	bfs();
	int ans=0;
	for (int i: v)
		ans = (ans+sum[i])%80112002;
	printf("%d", ans);
}
