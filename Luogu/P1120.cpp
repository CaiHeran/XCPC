
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <numeric>

template <typename T=int>
T rd()
{
    char c=getchar();
    while (c<'0'||'9'<c) c = getchar();
    T n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + c-'0';
    return n;
}

constexpr int MAXN = 65;

int n, l, num, cnt;
bool used[MAXN+1]{};
int next[MAXN+1];
int a[MAXN+1];

void dfs(int len, int i=0)
{
    // while (a[i] > len) ++i;
    i = std::lower_bound(a+i, a+n, len, std::greater<int>{}) - a;
    for (; i<n; ++i)
        if (!used[i])
        {
            used[i] = true;
            if (a[i]==len) {
                if (++cnt == num)
                    throw true;
                try { dfs(l, 0); }
                catch(bool) {
                    used[i] = false;
                    throw true;
                }
                --cnt;
                used[i] = false;
                return;
            }
            else
                dfs(len-a[i], i+1);

            used[i] = false;
            if (l==len) //
                return;

            i = next[i]; // 考虑for末尾++i的影响，见 Ln68
        }
}

int main()
{
    n = rd();
    std::for_each(a, a+n, [](int&n){n=rd();});
    std::sort(a, a+n, std::greater<int>{});
    auto sum = std::accumulate(a, a+n, 0);

    a[n] = a[n-1];
    for (int nxt=n, i=n-1; i>=0; --i)
    {
        if (a[i] != a[i+1])
            nxt = i;    // 不"+1"，见 Ln53
        next[i] = nxt;
    }

    for (int i=a[0]; i<=(sum>>1); ++i)
        if (sum/i*i == sum)
        {
            num = sum/i;
            cnt = 0;
            l = i;

            try{ dfs(l); }
            catch (bool flag) {
                printf("%d", i);
                return 0;
            }
        }
    printf("%d", sum);
}