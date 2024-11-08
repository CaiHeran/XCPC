
#include <iostream>
#include <vector>
#include <print>

struct pair2
{
    int a, b;
    constexpr bool operator<(const pair2 o) const noexcept
    {
        return a+b < o.a+o.b || (a+b == o.a+o.b && a < b && o.a > o.b);
    }
};

int main()
{
    using namespace std;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        vector<pair2> a(n);
        for (int i=0, a1,a2; i<n; i++)
        {
            cin >> a1 >> a2;
            a[i] = {a1, a2};
        }
        std::sort(a.begin(), a.end());
        for (auto [a1, a2] : a)
            cout << a1 << ' ' << a2 << ' ';
        cout << '\n';
    }
    
    cout << flush;
}