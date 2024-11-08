
#include <cstdio>

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

template<class T>
constexpr void _max(T& a, const T& b)
    { if (a<b) a=b; }

int main()
{
    int n=rd(), m[2002][2002];

    for (int i=1; i<=n; ++i)
        for (int j=1; j<=n; ++j)
            m[i][j] = rd();
    
    int p[2002]{};

    for (int i=1; i<=n; ++i)
        p[1] += m[i][i];
    for (int i=1; i<=n; ++i)
        p[n] += m[n-i+1][i];
    for (int i=2; i<n; ++i)
    {
        int x=1, y=i;
        while (y<=n)
            ++x, ++y, p[i] += m[x][y];
        --y; --x;
        do
            ++x, --y, p[i] += m[x][y];
        while (x<=n);
        --x; ++y;
        do
            --x, --y, p[i] += m[x][y];
        while (y>=1);
        ++x, ++y;
        do
            --x, ++y, p[i] += m[x][y];
        while (x>=1);
    }

    auto delta = [&m, n](int x, int y) -> int
    {
        if((y-x)%2) return 0;
        if(x==1&&y==n) return m[(n+1)/2][(n+1)/2];
        if(x==1) return m[(y+1)/2][(y+1)/2]+m[(2*n-y+1)/2][(2*n-y+1)/2];
        if(y==n) return m[(n-x)/2+1][(n+x)/2]+m[(n+x)/2][(n-x)/2+1];
        return m[(x+y)/2][(y-x)/2+1]+m[(y-x)/2+1][(x+y)/2]+m[n-(y-x)/2][n-(x+y)/2+1]+m[n-(x+y)/2+1][n-(y-x)/2];
    };

    int ans=0;
    for (int i=1; i<n; ++i)
        for (int j=i+1; j<=n; ++j)
            _max(ans, p[i]+p[j]-delta(i, j));
    printf("%d", ans);
}