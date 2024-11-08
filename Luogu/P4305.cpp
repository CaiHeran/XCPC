
#include <cstdio>
#include <unordered_map>

template <typename T=int>
T rd()
{
    T f=1, n; char c;
    while (c=getchar(), c<'0'||'9'<c)
        if (c=='-') f=-1;
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + (c-'0');
    return n;
}

int main()
{
    int T=rd();
    while (T--)
    {
    int n=rd(), x;
    std::unordered_map<int, bool> m;
    while (n--)
    {
        x = rd();
        if (!m[x])
            printf("%d ", x);
        m[x] = true;
    }
    putchar(10);
    }
}