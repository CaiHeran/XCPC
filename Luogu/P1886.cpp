
#include <cstdio>
#include <deque>
#include <functional>

template <typename T=int>
T rd()
{
    T t=1, n; char c;
    while (c=getchar(), c<'0'||'9'<c)
        if (c=='-') t = -1;
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + (c-'0');
    return t*n;
}

constexpr int MAXN = 1e6+2;

template<bool T>
auto op();
template<>
auto op<false>()
    { return std::greater_equal<int>(); }
template<>
auto op<true>()
    { return std::less_equal<int>(); }


int n=rd(), k=rd();
int a[MAXN];

struct vx {
    int v, x; // value, place
    vx(){}
    vx(int v_, int x_):v(v_),x(x_){}
};
template<bool T>
void solve()
{
    auto op = ::op<T>();
    std::deque<vx> q;
    for (int i=1; i<=n; ++i)
    {
        while (!q.empty() && op(q.back().v, a[i]))//将因值而永远不会取到的元素弹出-
            q.pop_back();                       //-如，若求最小值，则弹出大于等于该数的
        q.emplace_back(a[i], i);                //在队尾加入当前元素
        while (!q.empty() && q.front().x <= i-k) //将因位置而永远不会取到的元素弹出
            q.pop_front();                       //在此为弹出超过区间范围的
        if (i>=k)
            printf("%d ", q.front().v);     //得出当前元素的答案
    }
}

int main()
{
    for (int i=1; i<=n; ++i)
        a[i] = rd();
    std::deque<vx> q;
    solve<false>();
    putchar(10);
    solve<true>();
}