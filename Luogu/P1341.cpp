// Euler
#include <cstdio>

struct {
	int n=0;
	char cpath[1400];
	void push(const char c)
	  { cpath[n++]=c; }
	void print() const
	{
		for (int i=n-1; i>=0; --i)
			putchar(cpath[i]);
	}
}cpath;

bool m[123][123]{};

bool vis[123]{};
void find(char x)
{
	for (int i=65; i<=122; ++i)
    if (m[i][x])
    {
    	m[x][i]=false, m[i][x]=false;
		find(i);
    }
	cpath.push(x);
}

int main()
{
	int n;
	char c[4];
	int deg[123]{};
    scanf("%d", &n);
	for (int i=0; i<n; ++i)
	{
		scanf("%s", c);
		m[c[0]][c[1]]=true,
		m[c[1]][c[0]]=true;
		++deg[c[0]];
		++deg[c[1]];
	}
	int s=0, cnt=0;
	for (int i=122; i>=64; --i)
		if (deg[i]&1)
			s = i, ++cnt;
	if (cnt){
	  if (cnt!=2)
		goto NoSolution;
	}
	else // cnt==0
	  for (int i=64; i<=122; ++i)
		if (deg[i]){
			s = i;
			break;
		}

	find(s);

    if (cpath.n==n+1)
	    cpath.print(); 
    else
	NoSolution:
	printf("No Solution");
}
