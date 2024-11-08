
#include <iostream>
#include <algorithm>
#include <vector>
#include <print>

using uint = unsigned int;
using int32 = std::int32_t;
using int64 = std::int64_t;

template <class T=int>
T rd()
{
    using std::cin;
    char c = cin.get();
    while (c<'0'||'9'<c)
        c = cin.get();
    T n = c^'0';
    while (c=cin.get(), '0'<=c&&c<='9')
        n = n*10 + (c^'0');
    return n;
}

int main()
{
    using namespace std;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = rd();
    while (T--)
    {
        int n = rd();
        vector<int> a(n);
        for (int i=0; i<n; ++i)
            a[i] = rd();

        int ans = 200000;
        for (int i=0; i<n; i++)
        {
            if (i && a[i] == a[i-1])
                continue;
            
            int cnt = 0;
            for (int j=i+1; j<n; j++)
                cnt += a[j] > a[i];
            
            ans = min(ans, cnt + i);
        }

        println("{}", ans);
    }

}