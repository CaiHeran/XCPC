
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <atomic>
#include <vector>
#include <thread>

using u32 = std::uint32_t;
using u64 = std::uint64_t;

constexpr u32 powmod(u32 x, u32 n, u32 mod) noexcept
{
	u32 ans=1, res=x;
	while (n)
	{
		if (n&1)
			ans = (u64)ans*res%mod;
		res = (u64)res*res%mod;
		n >>= 1;
	}
	return ans;
}

#ifdef __GNUC__
constexpr int ctz(unsigned int n) noexcept
	{ return __builtin_ctz(n); }
constexpr int ctz(unsigned long n) noexcept
	{ return __builtin_ctzl(n); }
constexpr int ctz(unsigned long long n) noexcept
	{ return __builtin_ctzll(n); }
#endif
template<typename T>
constexpr int ctz(T n) noexcept
{
	int cnt=0;
	while (!(n&1))
		n>>=1, ++cnt;
	return cnt;
}

bool Miller_Rabin(std::uint32_t n) noexcept
{
	if (!(n&1) || n<=1)
		return n==2;
	constexpr uint32_t primes[]{2, 7, 61};
	// {2,325,9375,28178,450775,9780504,1795265022}
	const std::uint32_t crz=ctz(n-1), e=(n-1)>>crz;
	
	for (auto p: primes)
	{
		u32 v = powmod(p, e, n);
		if (v<=1u || v==n-1u)
			continue;

		unsigned i = crz;
		do {
			v = (std::uint64_t)v*v%n;
			if (v==n-1)
				goto NextLoop;
			if (v==1)
				return false;
		} while (--i);
		if (v!=1)
			return false;
		NextLoop:;
	}
	return true;
}

std::atomic_int ans=0;
int main()
{
	int n=50000000;
	std::cin >> n;
	constexpr int Nums=3000000;
	std::vector<std::thread> threads;
	if (n%Nums)
		threads.emplace_back(std::thread([n]{[](int i){
			int cnt=0;
			for (int j=2; j<=i; j++)
				cnt += Miller_Rabin(j);
			ans += cnt;
		}(n%Nums);})
	);
	for (int i=n; i>=Nums; i-=Nums)
	{
		threads.emplace_back(std::thread([i]{
			int cnt=0;
			for (int j=i-Nums+1; j<=i; j++)
				cnt += Miller_Rabin(j);
			ans += cnt;
		})
		);
	}
	
	for (auto &t: threads)
		t.join();
	
	std::cout << ans << std::endl;
}