#include <iostream>

int prime[10000];

void findprime(int n)
{
	int &cnt = prime[0];
	bool notprime[n+1]{};
	for (int i=2; i<=n; ++i)
		if (!notprime[i])
		{
			prime[cnt++]=i;
			for (int j=i*i; j<=n; j+=i)
				notprime[j]=true;
		}
}

void Euler(int n)
{
	int &cnt = prime[0];
	bool vis[n+1]{};
	for (int i=2; i<=n; ++i)
	{
		if (!vis[i])
			prime[++cnt] = i;
		for (int j=1; j<=cnt && i*prime[j]<=n; ++j)
		{
			vis[i*prime[j]] = true;
			if (i%prime[j]==0)
				break;
		}
	}
}

int main()
{
	Euler(10000);
	for (int i=0; i<prime[i]; ++i)
		std::cout << prime[i] << '\n'; 
}
