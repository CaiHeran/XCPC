
#include <iostream>
#include <string>
#include <vector>
#include <set>

int main()
{
    using namespace std;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;

    int n, q;
    int p[200002];
    bool s[200002];

    while (T--)
    {
        cin >> n >> q;
        char c;
        std::vector<unsigned char> need(n+1, 0), has(n+1, 0);
        for (int i=1; i<=n; i++)
        {
            cin >> p[i];
        }
        for (int i=1; i<=n; i++)
        {
            cin >> c;
            s[i] = c == 'R';
            // L==false, R==true
        }
        for (int i=1, r=1; i<n; i++)
        {
            if (p[i] > i && p[i] > r) {
                if (r < i)
                    r = i;
                do {
                    need[r] = 1;
                    r++;
                } while (p[i] > r);
            }
        }

        for (int i=1; i<=n; i++)
        {
            if (s[i])// R
                has[i]++;
            else    // L
                has[i-1]++;
        }

        std::set<int> gap;

        for (int i=1; i<n; i++)
        {
            if (need[i] > has[i])
                gap.insert(i);
        }

        for (int i=0, x; i<q; i++)
        {
            cin >> x;
            if (s[x])// R
            {
                s[x] = false;
                has[x]--;
                if (has[x] < need[x])
                    gap.insert(x);
                has[x-1]++;
                if (has[x-1]==1 && need[x-1])
                    gap.erase(x-1);
            }
            else    // L
            {
                s[x] = true;
                has[x-1]--;
                if (has[x-1] < need[x-1])
                    gap.insert(x-1);
                has[x]++;
                if (has[x]==1 && need[x])
                    gap.erase(x);
            }
            cout << (gap.empty() ? "YES" : "NO") << '\n';
        }
    }
    cout << flush;
}