// water?

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

template <typename T=int>
T rd()
{
    T n; char c;
    while (c=getchar(), c<'0'||'9'<c)
        if (c=='-') return -rd();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + (c-'0');
    return n;
}

int main()
{
    int n=rd();
    std::vector<int> a;
    a.resize(n);
    std::for_each(a.begin(), a.end(), [](int&n){n=rd();});

    std::int64_t min=INT32_MAX<<5, ans=INT32_MIN<<5;
    for (int i: a)
    {
        ans = std::max(ans, i-min);
        if (i < min)
            min = i;
    }

    std::cout << ans << std::flush;
}