#include <iostream>

typedef __int128 int128_t;
typedef long long ll;

template <typename T>
T qpow(T x, T n, T mod)
{
	T ans=1, res=x;
	while (n)
	{
		if (n&1)
			ans = (int128_t)ans*res%mod;
		res = (int128_t)res*res%mod;
		n >>= 1;
	}
	return ans;
}

template<typename T>
T ctz(T n)
{
	T cnt=0;
	while (!(n&1))
		n>>=1, ++cnt;
	return cnt;
}

template<typename T>
constexpr bool is_even(const T& n)
    { return !(n&1); }

bool Miller_Rabin(long long n)
{
	if (n==2) return true;
	if ( n<=1 || is_even(n) )
		return false;
    // 2, 325, 9375, 28178, 450775, 9780504, 1795265022
	static constexpr long long primes[]{2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	//static constexpr int primes[]{2, 7, 61};
	long long crz=ctz(n-1), e=(n-1)>>crz;

	for (auto p: primes)
	{
		ll v = qpow(p, e, n);
		if (v<=1 || v==n-1)
			continue;
		for (ll i=1; i<=crz; ++i)
		{
			v = (ll)v*v%n;
			if (v==n-1 && i!=crz)
			{
				v = 1;
				break;
			}
			if (v==1)
				return false;
		}
		if (v!=1)
			return false;
	}
	return true;
}

int main()
{
    int n;
    ll x;
    // std::cin >> n;
    for (int i=0; std::cin>>x; ++i) 
    {
        puts(Miller_Rabin(x)? "Prime":"Not prime");
    }
}