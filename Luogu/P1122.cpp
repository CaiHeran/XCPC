// P1122 最大子树和

#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

template <typename T=int>
T rd()
{
    T f=1, n; char c;
    while (c=getchar(), c<'0'||'9'<c)
        if (c=='-') f=-1;
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + (c-'0');
    return f*n;
}

using std::max;
constexpr int MAXN = 16001;

int n;
int r[MAXN];
int v[MAXN];
std::vector<int> son[MAXN];

void dfs(int c=1, int fa=0)
{
    int &tot = v[c] = r[c];
    for (auto i: son[c])
        if (i != fa)
        {
            dfs(i, c);
            if (!(v[i] >> 31))
                tot += v[i];
        }
}

int main()
{
    n=rd();
    std::for_each(r+1, r+n+1, [](auto &n){n=rd();});

    for (int i=1; i<n; ++i)
    {
        int u=rd(), v=rd();
        son[u].push_back(v);
        son[v].push_back(u);
    }
    dfs();
    std::cout << *std::max_element(v+1, v+n+1);
}