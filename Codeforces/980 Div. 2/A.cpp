
#include <iostream>
#include <print>

int main()
{
    using namespace std;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        int a, b;
        cin >> a >> b;
        if (a >= b)
            cout << a << '\n';
        else{
            int x = b - a;
            if (x >= a)
                cout << "0\n";
            else 
                cout << a - x <<'\n';
        }
    }
}