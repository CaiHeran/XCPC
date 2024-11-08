
#include <cstdio>

int n, m, ans;
int a[100001];

bool check(int num)
{
    int m = 1, rest = num;
    for (int i=1; i<=n; ++i)
    {
        if (a[i] > num)
            return false;
        if (rest < a[i]){
            ++m,
            rest = num;
        }
        rest -= a[i];
    }
    return m<=::m;
}

int main()
{
    scanf("%d%d", &n,&m);
    for (int i=1; i<=n; ++i)
        scanf("%d", a+i);

//*二分答案
    int l=0, r=1e9, mid;
    while (l<r)
    {
        mid = (l+r)>>1;

        if (check(mid))
            r = mid;
        else
            l = mid+1;
    }
    printf("%d", l);
}