#include <cstdio>
#include <iostream>
#include <memory>
#include <deque>

using std::cout;

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

int main()
{
    struct node {
        int n, id;
        node(int n_, int id_)
            :n(n_), id(id_){}
    };
    int n=rd(), k=rd();

    std::deque<node> q;

    for (int i=1; i<=n; ++i)
    {
        int v = rd();
        while (!q.empty() && q.back().n<=v)
            q.pop_back();
        q.emplace_back(v, i);
        if (q.front().id <= i-k)
            q.pop_front();
        if (i>=k)
            cout << q.front().n << '\n';
    }
    cout << std::endl;
}