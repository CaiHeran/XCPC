
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <map>

template <typename T=int>
T rd()
{
    T n; char c=getchar();
    while (c<'0'||'9'<c)
        c = getchar();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + c-'0';
    return n;
}
inline void nl() { putchar(10); }
template <typename T>
void print(T n)
{
    if (n>9)
        print(n/10);
    putchar(n%10|48);
}
template<class T>
inline void printl(T n)
    { print(n); nl(); }

template <class T>
void ranks(T a, T p, int len)
{
    std::sort(a, a+len);
    auto end = std::unique(a, a+len);
    for (int i=0; i<len; ++i)
        p[i] = std::upper_bound(a, end, a[i]) - a;
}

template<typename T>
constexpr T lowbit(T n)
    { return n&-n; }

template<class _Type>
class BIT
{
public:
    int _size;
    _Type _c[10001]{};

    BIT(int size)
        :_size(size){}

    void plus(int p, const _Type& k)
    {
        for (; p<=_size; p+=lowbit(p))
            _c[p] += k;
    }
    _Type sum(int x) const
    {
        _Type s = 0;
        for (; x; x-=lowbit(x))
            s += _c[x];
        return s;
    }
    _Type sum(const int &l, const int &r) const
      { return sum(r) - sum(l-1); }
};

int main()
{
    int q=rd();
    struct {
        char t;
        int x;
    } ope[10002];
    for (int i=1; i<=q; ++i)
        ope[i] = {rd<char>(), rd()};

    std::vector<int> num;
    for (int i=1; i<=q; ++i)
        if (ope[i].t==5)
            num.push_back(ope[i].x);
    std::vector<int> p(num.size());
    ranks(num, p, num.size());
    std::map<int, int> ma;
    for (int i=num.size()-1; i>=0; --i)
        ma[p[i]] = i;

    std::multiset<int> set;
    BIT<int> tr(num.size());

    for (int i=1; i<=q; ++i)
    {
        int x = ope[i].x;
        switch (ope[i].t)
        {
        case 1: // x的排名
            printl(tr.sum(ma[x]));
            break;
        case 2: // 排名为x的数
            int l=0, r=num.size(), mid;
            while (l<=r)
            {
                mid = (l+r)>>1;
                if (tr.sum(mid) < x)
                    l = mid;
                else if (tr.sum(mid) > x)
                    r = mid;
                else break;
            }
            printl(p[mid]);
            break;
        case 3:
            printl(*--set.upper_bound(x));
            break;
        case 4:
            printl(*++set.upper_bound(x));
            break;
        case 5:
            tr.plus(x, 1);
            set.insert(x);
            break;
        }
    }
}