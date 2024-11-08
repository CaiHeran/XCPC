
#include <iostream>
#include <print>
#include <vector>
#include <algorithm>

int main()
{
    using namespace std;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        int n, k;
        cin >> n >> k;
        std::vector<int> a(n+1);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        std::sort(a.begin()+1, a.end());
        int l = 1;
        int take = 0;
        int press = 0;
        int loop=0;

        while (true)
        {
            while (a[l] <= loop)
                l++, press++;
            int need = k - take;
            int needloop = need / (n+1-l);

            if (a[l] - loop <= needloop)
            {
                take += (n+1-l) * (a[l] - loop);
                press += (n+1-l) * (a[l] - loop);
                loop = a[l];
                if (take == k)
                    break;
                continue;
            }
            else {
                loop += needloop;
                press += k - take;
                break;
            }
        }
        cout << press << '\n';
    }
    cout << flush;
}