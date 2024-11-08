
#include <iostream>

int main()
{
    using namespace std;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    int n;
    int a;
    while (T--)
    {
        cin >> n;
        int min = 1001, max = 0;
        for (int i=0; i<n; i++)
        {
            cin >> a;
            if (a < min)
                min = a;
            if (a > max)
                max = a;
        }
        cout << (max-min)*(n-1) << '\n';
    }
    cout << flush;
}