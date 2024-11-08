
#include <cstdio>
#include <memory.h>
#include <cmath>
#include <limits>

template <class T>
constexpr T sqr(T x) { return x*x; }

template<typename T>
constexpr void _min(T& a, const T& b)
  { if (b<a) a=b; }

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

/////

int n;
struct {
    double x, y;
} p[16];
double f[15][1<<15];

inline double dist(int a, int b)
{
    return sqrt(sqr(p[a].x-p[b].x)+sqr(p[a].y-p[b].y));
}

double solve()
{
    memset(f, 127, sizeof(f));
    for (int i=0; i<n; ++i)
        f[i][1<<i] = 0;
    for (int s=1; s < (1<<n); ++s)
      for (int i=0; i<n; ++i)
        if (s&(1<<i) && s!=(1<<i))
        {
            for (int j=0; j<n; ++j)
              if (j!=i && s&(1<<j))
              {
                  _min(f[i][s], f[j][s-(1<<i)] + dist(i, j));
              }
        }
    p[n] = {0, 0};
    double ans = std::numeric_limits<double>::infinity();
    for (int i=0; i<n; ++i)
        _min(ans, dist(i, n) + f[i][(1<<n)-1]);
    return ans;
}

int main()
{
    n=rd();
    for (int i=0; i<n; ++i)
        scanf("%lf%lf", &p[i].x, &p[i].y);

    printf("%.2lf", solve());
}