
#include <iostream>

int main()
{
    using namespace std;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    int n;
    while (T--)
    {
        cin >> n;
        cout << '1';
        for (int i=1; i<n; i++)
            cout << '0';
        cout << '\n';
    }
    cout << flush;
}