#include <iostream>
#include <cstdio>

int Log2[100002];

namespace init
{
    void Log2(const int n)
    {
        for (int i=2; i<=n; ++i)
            ::Log2[i] = ::Log2[i>>1] +1;
    }
}

template<class _Type>
class ST
{
public:
    int n;
    _Type st[18][100001]{}; //$2^17 = 131072$

    _Type& operator[](int n)
      { return st[0][n]; }

    void init()
    {
        for (int j=1; j<18; ++j)
            for (int i=1; i+(1<<j)-1 <= n ; ++i)
                st[j][i] = std::max(st[j-1][i], st[j-1][i+(1<<(j-1))]);
    }

    _Type query(const int &l, const int &r)
    {
        const auto &k = Log2[r-l+1];
        return std::max(st[k][l], st[k][r -(1<<k) +1]);
    }
};

int read()
{
	int x=0, ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') { x=x*10+ch-48; ch=getchar(); }
	return x;
}
void writeN(int x){
	if (x>9) writeN(x/10);
	putchar(48|(x%10));
}

int main()
{
    int n=read(), m=read();
    ST<int> st;
    st.n = n;
    for (int i=1; i<=n; ++i)
        st[i] = read();

    init::Log2(n);
    st.init();

    do{
        int &&l=read(), &&r=read();
        writeN(st.query(l,r));
        putchar(10);
    } while (--m);
}