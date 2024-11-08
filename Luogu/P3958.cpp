
#include <cstdio>

typedef long long ll;

int n,h,r;
ll r2;
int pa_[1005];
struct hole{
    int x,y,z;
} ho[1005];

int pa(int n)
{
    return n==pa_[n]?
        n : (pa_[n]=pa(pa_[n]));
}

inline void merge(int a, int b)
{
    pa_[pa(a)] = pa(b);
}

inline bool check(const hole &a, const hole &b)
{
    return ll(a.x-b.x)*(a.x-b.x) + ll(a.y-b.y)*(a.y-b.y)
        + ll(a.z-b.z)*(a.z-b.z) <= r2;
}

int main()
{
    int T;
    scanf("%d", &T);
while (T--)
{
    scanf("%d%d%d", &n,&h,&r);
    r2 = 4ll*r*r;
    for (int i=0; i<n; ++i)
        scanf("%d%d%d", &ho[i].x, &ho[i].y, &ho[i].z);

    for (int i=0; i<=n; i+=2)
        pa_[i]=i, pa_[i+1]=i+1;
    pa_[n+1] = n+1;

    for (int i=0; i<n; ++i)
    {
        if (ho[i].z <= r)
            merge(i, n);
        if (ho[i].z + r >= h)
            merge(i, n+1);
    }

    for (int i=0; i<n; ++i)
      for (int j=i+1; j<n; ++j)
        if (check(ho[i], ho[j])){
            merge(i, j);
            if (pa(n)==pa(n+1)){
                puts("Yes");
                goto end;
            }
        }

    puts(pa(n)==pa(n+1)? "Yes":"No");
    end: continue;
}
}