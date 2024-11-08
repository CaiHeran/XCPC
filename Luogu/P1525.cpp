
#include <cstdio>
#include <algorithm>

int read()
{
    int n=0; char c=getchar();
    while (c<'0'||'9'<c)
        c = getchar();
    do {
        n = n*10 + (c-'0');
        c = getchar();
    } while ('0'<=c&&c<='9');
    return n;
}

int pa_[40002];
struct di{
    int a,b,c;
    bool operator<(const di& d) const
      { return c > d.c; }
} d[100002];

int pa(int n)
{
    return n==pa_[n]?
        n : (pa_[n] = pa(pa_[n]));
}

int main()
{
    int n=read(), m=read();
    for (int i=0; i<m; ++i)
        d[i].a=read(), d[i].b=read(), d[i].c=read();

    std::sort(d, d+m);

    for (int i=1; i<=2*n; i+=2)
        pa_[i]=i, pa_[i+1]=i+1;

    for (int i=0; i<m; ++i)
    {
        if (pa(d[i].a)==pa(d[i].b)){
            printf("%d", d[i].c);
            return 0;
        }
        pa_[pa(d[i].a)] = pa(d[i].b+n);
        pa_[pa(d[i].b)] = pa(d[i].a+n);
    }
    printf("0");
}