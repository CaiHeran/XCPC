
#include <iostream>

constexpr int MOD{998244353};

int fact(unsigned n)
{
    std::uint_fast64_t s=1;
    while (n)
        s = s*n--%MOD;
    return s;
}

int main()
{
    using namespace std;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t, n, m;
    std::cin >> t;
    while (t--)
    {
        std::cin >> n;
        if (n&1) cout << "0\n";
        else {
            m = fact(n>>1);
            cout << (long long)m*m%MOD << '\n';
        }
    }
    std::cout << std::flush;
}