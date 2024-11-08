
#include <cstdio>
#include <iostream>
#include <string>

template <typename T=int>
T rd()
{
    T n; char c=getchar();
    while (c<'0'||'9'<c) c = getchar();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + c-'0';
    return n;
}

void solve()
{
    int n=rd();
    int f=0, m=0;
    int cnt=0;
    std::string s;
    std::cin >> s;
    for (int i=0; i<n-1; ++i)
    {
        if (s[i]=='0')
            if (s[i+1]=='0')
                cnt+=2;
            else if (i+2<n && s[i+2]=='0')
                cnt+=1;
    }
    std::cout << cnt << '\n';
}

int main()
{
    int t=rd();
    while (t--)
    {
        solve();
    }
}