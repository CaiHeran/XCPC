// 01
#include <cstdio>

inline int max(const int& a, const int& b)
  { return a<b? b:a; }

int read()
{
	int n=0; char c = getchar();
	while (c<'0'||'9'<c)
		c = getchar();
	do {
		n = n*10 + (c-'0');
		c = getchar();
	} while ('0'<=c&&c<='9');
	return n;
}

int t, m;
struct {
	int t, v;
}d[101];
int f[1001]{};

int main()
{
	t = read();
	m = read();
	for (int i=0; i<m; ++i)
		d[i].t=read(), d[i].v=read();
	for (int i=0; i<m; ++i)
		for (int j=t; j>=d[i].t; --j)
			f[j] = max(f[j], f[j-d[i].t] + d[i].v);
	printf("%d", f[t]);
} 
