#include <cstdio>
#include <queue>

const int INF = 0x3f3f3f3f;

struct toy{
    int rest, toy_number;
    const bool operator<(const toy &t)const
        { return rest < t.rest; }
};

void solve()
{
    int n,k,p, Ans=0;
    std::priority_queue<toy> Floor;
    bool on_floor[100001];
    int a[500001];
    int next[500001], t[500001];
// 读入
    scanf("%d%d%d", &n,&k,&p);
    for (int i=1; i<=p; ++i)
        scanf("%d", a+i);
// 采用倒序遍历，O(n)处理下一次同一玩具出现的位置
    for (int i=p; i; --i){
        next[i] = t[a[i]]? t[a[i]] : INF;
        t[a[i]] = i;
    }
// 处理（模拟）
    for (int i=1; i<=p; ++i)
    {
        if (on_floor[a[i]]) // 由于优先队列不好更新，且旧的数据不会影响新的数据，
            ++k;            // 采用增加堆大小的方式
        else{
            // 仅当堆满时弹出数据
            if (Floor.size()==k){
                on_floor[Floor.top().toy_number] = false;
                Floor.pop();
            }
            on_floor[a[i]] = true;
            ++Ans;
        }
        Floor.push(toy{next[i], a[i]}); // 放入
    }
    printf("%d\n", Ans);
}
int main()
{
    int H;
    scanf("%d", &H);
    while(H--)
        solve();
}