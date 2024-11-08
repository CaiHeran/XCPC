// 二叉苹果树
#include <cstdio>

inline void _max(int &a, const int &b)
  { if (a<b) a=b; }

enum {L,R};

int n,q;
int amount[101];
int tree[101][2];
int f[101][101];
int map[101][101];

void maketree(const int r)
{
    for (int f=0,i=1; i<=n; ++i)
      if (map[r][i]>=0){
        amount[i] = map[r][i],
        tree[r][f] = i;
        ++f;
        map[i][r]=map[r][i]=-1;
        maketree(i);
        if (f>2) break;
      }
}

int dp(int r, int x)
{
    if (!x) return 0;
    if (f[r][x]>0) return f[r][x];
    if (!tree[r][L] && !tree[r][R])  // 叶
        return f[r][x]=amount[r];

    for (int k=0; k<x; ++k)
        _max(f[r][x], dp(tree[r][L], k) + dp(tree[r][R], x-k-1));
    return f[r][x]+=amount[r];
}

int main()
{
    scanf("%d%d", &n,&q);
    for (int i=0; i<=n; ++i)
        for (int j=0; j<=n; ++j)
            map[i][j]=-1;
    for (int a,b,s,i=1; i<n; ++i){
        scanf("%d%d%d", &a,&b,&s);
        map[b][a]=map[a][b]=s;
    }
    maketree(1);
    printf("%d", dp(1, q+1));
}