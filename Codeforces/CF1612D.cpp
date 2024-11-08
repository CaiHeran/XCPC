//*@date: 2022-03-27
// CF1612D

#include <cstdio>
#include <iostream>

typedef std::int_fast64_t int64;

template <typename T=int64>
T rd()
{
    T n; char c=getchar();
    while (c<'0'||'9'<c) c = getchar();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + c-'0';
    return n;
}

bool check(int64 a, int64 b, int64 x)
{
    if (x>a || !b) return false;
    if ((a-x)/b*b == a-x) return true;
    return check(b, a%b, x);
}

int main()
{
    int t=rd();
    while (t--)
    {
        int64 a=rd(), b=rd(), x=rd();
        if (a < b) std::swap(a, b);
        puts(check(a, b, x)? "YES":"NO");
    }
}