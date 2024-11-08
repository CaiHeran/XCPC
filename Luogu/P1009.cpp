//要使用高精度
#include<iostream>

int main()
{
	unsigned long long i,n,t(1ull),ans(1ull);
	std::cin >> n;
	for (i = 2; i <= n; ++i)
		ans += t*=i;
	std::cout << ans;
}