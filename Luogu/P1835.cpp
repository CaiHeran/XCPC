#include <cstdio>
#include <cmath>

typedef long long ll;
#define int unsigned

int prime[50000], &cnt = prime[0];
bool notprime[1000002]{};

void findprimes(int n)
{
	bool vis[n+1]{};
	for (int i=2; i<=n; ++i)
	{
		if (!vis[i])
			prime[++cnt] = i;
		for (int j=1; j<=cnt && (ll)i*prime[j]<=n; ++j)
		{
			vis[i*prime[j]] = true;
			if (i%prime[j]==0)
				break;
		}
	}
}

signed main()
{
	int l, r;
	scanf("%d%d", &l, &r);
	findprimes(sqrt(r)+0.5);
	for (int i=1; i<=cnt; ++i){
	    ll j = l/prime[i]*prime[i];
	    if (j<l) j += prime[i];
	    if (j==prime[i])
	        j <<= 1;
		for (; j<=r; j+=prime[i])
			notprime[j-l] = true;
    }
	int ans=0;
	for (int i=l; i<=r; ++i)
		ans += !notprime[i-l];
	if (l==1) --ans; // 务必特判，1不是素数。见P1835_11.in 
	printf("%d", ans);
}
