#include <cstdio>
#include <iostream>
#include <algorithm>

template <typename T=int>
T rd()
{
    T n; char c=getchar();
    while (c<'0'||'9'<c) c = getchar();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + c-'0';
    return n;
}

struct Task {
    int s, e;
};

int main()
{
    int n=rd(), k=rd();
    int cnt[10001]{};
    Task task[10001];
    std::for_each(task+1, task+k+1, [&cnt](Task &t)
        {t.s=rd(); t.e = t.s+rd()-1; ++cnt[t.s];}
    );
    std::sort(task+1, task+k+1,
        [](Task a, Task b) { return a.s < b.s; });

    int f[10002]{};
    for (int t=n; t>=1; --t)
        if (cnt[t]==0) f[t] = 1+f[t+1];
        else {
            for (int i=cnt[t]; i; --i)
            {
                auto j = f[task[k--].e+1];
                if (j > f[t])
                    f[t] = j;
            }
        }
    std::cout << f[1] << std::flush;
}