#include <cstdio>
#include <algorithm> 

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

bool notprime[100001]{1,1};
int pa[100001];

int getpa(int a)
{
	return a!=pa[a]? pa[a]=getpa(pa[a]):a;
}

inline void merge(int a, int b)
{
	pa[getpa(a)] = getpa(b);
}

int main()
{
	std::lower_bound();
	int a,b,p;
	scanf("%d%d%d", &a,&b,&p);
	int ans = b-a+1;
	for (int i=a; i<=b; ++i)
		pa[i]=i;

	for (int i=2; i<=b; ++i)
		if (!notprime[i]){
			if (i >= p)
				for (int j=i<<1; j<=b; j+=i)
				{	
					notprime[j] = true;
					if (j>=a+i && getpa(i)!=getpa(j)) // 从a+i(或大于)开始并集 
						merge(j-i, j), --ans;
				}
			else
				for (int j=i<<1; j<=b; j+=i)
					notprime[j] = true;
		}

	printf("%d", ans);
} 
