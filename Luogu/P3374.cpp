// BIT
#include <cstdio>

const int MAXN = 500002;

template<typename T>
constexpr T lowbit(T n)
    { return n&-n; }

template<class Type>
class BIT
{
public:
    int size_;
    Type _c[MAXN]={};

    BIT(const int &size)
        :size_(size){}

    void plus(int p, const Type k)
    {
        for (; p<=size_; p+=lowbit(p))
            _c[p] += k;
    }

    Type sum(int x)const
    {
        Type s = 0;
        for (; x; x-=lowbit(x))
            s += _c[x];
        return s;
    }

    Type sum(int l, int r)const
    {
        return sum(r) - sum(l-1);
    }
};

int main()
{
    int n,m,f,a,b;
    scanf("%d%d", &n,&m);
    BIT<int> t(n);
    for (int i=1; i<=n; ++i){
        scanf("%d", &a);
        t.plus(i, a);
    }
    while (m--)
    {
        scanf("%d%d%d", &f,&a,&b);
        if (f==1)
            t.plus(a, b);
        else
            printf("%d\n", t.sum(a,b));
    }
}