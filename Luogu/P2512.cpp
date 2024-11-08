// HAOI2008 糖果传递
#include <cstdio>
#include <algorithm>

typedef long long ll;

const int MAX = 1000001;

ll sum, mid, Ans=0;
int n, ave, a[MAX];
ll c[MAX];

int main()
{
    scanf("%d", &n);
    for (int i=1; i<=n; ++i){
        scanf("%d", a+i);
        sum += a[i];
    }
    ave = sum/n;
    for (int i=1; i<=n; ++i)
        c[i] = c[i-1] + (a[i] - ave);
    std::nth_element(c+1, c+(n>>1)+1, c+n+1);
    mid = c[(n>>1)+1];
    for (int i=1; i<=n; ++i)
        Ans += abs(c[i] - mid);
    printf("%lld", Ans);
}