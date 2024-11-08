
#include <cstdio>

inline char getflag()
{
    char c=getchar();
    while (c!='1'&&c!='2')
        c=getchar();
    return c;
}

inline int read()
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

const int MAXN = 5e4;

int pa[MAXN*3+5];

int findpa(int n){
    return n==pa[n]?
        n : (pa[n] = findpa(pa[n]));
}

inline void merge(int a, int b)
  { pa[findpa(a)] = findpa(b); }

inline bool query(int a, int b)
  { return findpa(a)==findpa(b); }

int main()
{
    int cnt=0;
    char f;
    int n=read(), k=read(), x, y;
    int n2=n<<1;
    for (int n3=n+n2,i=0; i<=n3; i+=2)
        pa[i]=i, pa[i|1]=i|1;
    while (k--)
    {
        f=getflag(), x=read(), y=read();
        if (x>n || y>n)
            { ++cnt; continue; }
        if (f=='1')
        {
            if (query(x, y+n) || query(x, y+n2))
                { ++cnt; continue; }
            merge(x, y);
            merge(x+n, y+n);
            merge(x+n2, y+n2);
        }
        else
        {
            if (query(x, y) || query(x, y+n2))
                { ++cnt; continue; }
            merge(x, y+n);
            merge(x+n, y+n2);
            merge(x+n2, y);
        }
    }
    printf("%d", cnt);
}