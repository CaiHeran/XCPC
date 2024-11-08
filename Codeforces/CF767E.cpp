
#include <cstdio>
#include <queue>

const int MAX = 100001;

struct change{
    int w, day;
    const bool operator<(const change &t)const
        { return w > t.w; }
};

int n, m;
int c[MAX], w[MAX];
std::priority_queue<change> q;

long long Ans=0ll;
int Hundred[MAX], Change[MAX];

int main()
{
    scanf("%d%d", &n,&m);
    for (int i=1; i<=n; ++i)
        scanf("%d", c+i);
    for (int i=1; i<=n; ++i)
        scanf("%d", w+i);

    for (int i=1; i<=n; ++i){
        Hundred[i] = c[i]/100;
        c[i] %= 100;
    }

    for (int i=1; i<=n; ++i)
    {
        if (c[i])
            q.push(change{w[i]*(100-c[i]), i});
        m -= c[i];
        Change[i] = c[i];
        if (m < 0){
            ++Hundred[q.top().day];
            Change[q.top().day] = 0;
            m += 100;
            Ans += q.top().w;
            q.pop();
        }
    }
    printf("%lld\n", Ans);
    for (int i=1; i<=n; ++i)
        printf("%d %d\n", Hundred[i], Change[i]);
}