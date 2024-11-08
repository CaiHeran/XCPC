
#include <iostream>
#include <string>

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
        std::string s;
        cin >> n >> s;
        int n0=s[0]=='0', n1=s[0]=='1';
        for (int i=1; i<n; i++)
        {
            n0 += s[i] == '0' && s[i-1] == '1';
            n1 += s[i] == '1';
        }
        cout << (n1 >= n0 ? "YES" : "NO") << '\n';
    }
    cout << flush;
}