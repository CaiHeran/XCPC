
#include <cstdio>
#include <queue>

int n, t, t2, ans=0;
std::priority_queue<int, std::vector<int>, std::greater<int> > q;

int main()
{
    scanf("%d", &n);
    for (int i=0; i<n ;++i)
    {
        scanf("%d", &t);
        q.push(t);
    }
    while(--n)
    {
        t = q.top();
        q.pop();
        t2 = q.top();
        q.pop();
        ans += t + t2;
        q.push(t+t2);
    }
    printf("%d", ans);
}