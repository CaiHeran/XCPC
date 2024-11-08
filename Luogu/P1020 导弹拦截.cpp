#include <cstdio>
#include <algorithm>
#include <functional>

void read();
int q1();
int q2();

int n, a[100001];

int main()
{
    read();
    printf("%d\n%d", q1(), q2());
}

void read()
{
    char c;
    while(true)
    {
        while (c=getchar(), true)
            if (c==EOF||c=='\n')
                return;
            else if ('0'<=c && c<='9')
                break;
        a[n] = c - '0';
        while ((c=getchar())>='0' && c<='9')
            a[n] = a[n]*10 + (c-'0');
        ++n;
        if (c==EOF||c=='\n')
            break;
    }
}
int dp1[100001], dp2[100001];
//*最长不上升子序列
int q1()
{
    int Len=0;
    dp1[0] = a[0];
    for (int i=1; i<n; ++i)
    {
        if (a[i]<=dp1[Len])
            dp1[++Len] = a[i];
        else
            *std::upper_bound(dp1, dp1+Len, a[i], std::greater<int>()) = a[i];
    }
    return Len+1;
}
//*
int q2()
{
    int Len=0;
    dp2[0] = a[0];
    for (int i=1; i<n; ++i)
    {
        if (a[i]>dp2[Len])
            dp2[++Len] = a[i];
        else
            *std::lower_bound(dp2, dp2+Len, a[i]) = a[i];
    }
    return Len+1;
}