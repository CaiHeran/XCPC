
#include <cstdio>

int main()
{
    int n, r, t=0, a[20];
    scanf("%d%d", &n, &r);
    printf("%d=", n);
    while (n)
    {
        a[++t] = n % r;
        n /= r;
        if (a[t]<0)
            a[t] -= r,
            ++n;
    }
    do
        if (a[t]<10) printf("%d", a[t]);
        else printf("%c", a[t]-10+'A');
    while (--t);
    printf("(base%d)", r);
}