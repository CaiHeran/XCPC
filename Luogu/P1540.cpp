
#include <cstdio>
#include <queue>
#include <set>

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

int main()
{
    int cnt=0;
    int m=rd(), n=rd(), t;
    typedef std::pair<short, short> pii;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
    std::set<short> s;

    for (int i=0; i<n; ++i)
    {
        t = rd();
        if (s.count(t))
            continue;
        if (q.size()>=m) {
            s.erase(q.top().second);
            q.pop();
        }
        ++cnt;
        s.insert(t);
        q.emplace(i, t);
    }
    printf("%d", cnt);
}