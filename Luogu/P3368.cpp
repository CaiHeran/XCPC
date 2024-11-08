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
        { return sum(r) - sum(l-1); }
};

void print(int x){
	if (x>9) print(x/10);
	putchar(48|(x%10));
}

int main()
{
    int n,m, f,x,y,k;
    scanf("%d%d%d", &n,&m, &x);
    BIT<int> a(n);
    a.plus(1, x);
    for (int i=2; i<=n; ++i)
    {
        scanf("%d", &y);
        a.plus(i, y-x);
        x=y;
    }
    while (m--)
    {
        scanf("%d%d", &f,&x);
        switch(f){
        case 1:
            scanf("%d%d", &y,&k);
            a.plus(x, k),
            a.plus(y+1, -k);
            break;
        case 2:
            print(a.sum(x));
            putchar(10);
            break;
        }
    }
}