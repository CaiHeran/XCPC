#include <cstdio>

inline int _max(int& a, const int& b)
  { if (a<b) a=b; }

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

int n, m;
short cn[61]{};
struct {
	int w, v;
}t, d[61][3];
int f[32001]{};

int main()
{
	n = read()/10;
	m = read();
	for (int w,v,p,i=1; i<=m; ++i){
		w = read()/10, v = w*read(), p = read();
		if (p>0)
			d[p][cn[p]] = {w,v}, ++cn[p];
		else
			d[i][0] = {w,v}, cn[i]=1;
	}
	for (int i=1; i<=m; ++i)
	if (cn[i])
	  for (int j=n; j>=d[i][0].w; --j){
		_max(f[j], f[j-d[i][0].w]+d[i][0].v);
		if (cn[i]>1 && j-d[i][0].w-d[i][1].w>=0)
			_max(f[j], f[j-d[i][0].w-d[i][1].w] + d[i][0].v + d[i][1].v);
		if (cn[i]==3 && j-d[i][0].w-d[i][2].w>=0){
			_max(f[j], f[j-d[i][0].w-d[i][2].w] + d[i][0].v+d[i][2].v);
		  if (j-d[i][0].w-d[i][1].w-d[i][2].w>=0)
			_max(f[j], f[j-d[i][0].w-d[i][1].w-d[i][2].w] + d[i][0].v+d[i][1].v+d[i][2].v);
		}
	  }
	printf("%d", f[n]*10);
}
