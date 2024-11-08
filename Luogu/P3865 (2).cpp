
#include <cstdio>
#include <iostream>

using std::max;

template <typename T=int>
T rd()
{
    T n; char c=getchar();
    while (c<'0'||'9'<c)
        c = getchar();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + (c-'0');
    return n;
}
template <typename T>
void print(T n)
{
    if (n>9)
        print(n/10);
    putchar(n%10|48);
}

constexpr int MAXN = 1e5+2;

int Log2[MAXN];

void init_Log2(int n)
{
    Log2[1] = 0;
    for (int i=2; i<=n; ++i)
        Log2[i] = Log2[i>>1] + 1;
}

template<typename T>
class ST
{
protected:
    int n;
    T st_[18][MAXN]{}; //$2^17 = 131072$
public:
    ST(int _n) :n(_n) {}
    T& operator[](int x)
        { return st_[0][x]; }
    void init()
    {
        for (int k=1; k<18; ++k)
            for (int i=1; i+(1<<k)-1<=n; ++i)
                st_[k][i] = max(st_[k-1][i], st_[k-1][i+(1<<(k-1))]);
    }
    T query(int l, int r) const
    {
        auto k = Log2[r-l+1];
        return max(st_[k][l], st_[k][r-(1<<k)+1]);
    }
};

int main()
{
    int n=rd(), m=rd();
    ST<int> st(n);

    for (int i=1; i<=n; ++i)
        st[i] = rd();
    st.init();
    init_Log2(n);
    while (m--)
    {
        int l=rd(), r=rd();
        print(st.query(l, r));
        putchar(10);
    }
}