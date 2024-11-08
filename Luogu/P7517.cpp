
#include <cstdio>
#include <algorithm>
#include <memory>

template <typename T=int>
T rd()
{
    T n; char c=getchar();
    while (c<'0'||'9'<c)
        c = getchar();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + (c-'0');
    return n;
}

int main()
{
    int n=rd();
    int a[200002];
    for (int i=0; i<n; ++i)
        a[i] = rd();
    std::sort(a, a+n);

    int cnt[500002]{};
    for (int i=0; i<n; ++i)
    {
        for (int j=1; j*j<=a[i]; ++j)
            if (a[i]/j*j==a[i])
            {
                ++cnt[j];
                ++cnt[a[i]/j];
            }
    }
    int ans=0;
    for (int i=0; i<n; ++i)
        ans += cnt[a[i]];
    printf("%d", ans);
}