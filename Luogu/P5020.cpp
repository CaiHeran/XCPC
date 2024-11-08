#include <cstdio>
#include <memory.h>
#include <algorithm>

int readN()
{
    int n; char c=getchar();
    while (c<'0'||'9'<c)
        c = getchar();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + (c-'0');
    return n;
}

int gcd(int a, int b)
{
    return b? a:gcd(b, a%b);
}

int main()
{
    int T=readN();
    int n;
    int a[101];
    bool f[25005];
    while (T--)
{
    n=readN();
    memset(f, 0, n);
    f[1] = 1;
    for (int i=0; i<n; ++i)
        a[i] = readN();
    std::sort(a, a+n);
    int ans=0;
    for (int i=1; i<n; ++i) 
    {
        if (!f[i]) ++ans;
        for (int j=a[i]; j<=a[n-1]; ++j)
            f[j] |= f[j-a[i]];          
    }
    printf("%d", ans);
}
}