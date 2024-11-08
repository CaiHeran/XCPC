// 二分答案 单调队列
#include <cstdio>
#include <deque>

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

constexpr int MAXN = 100005;
constexpr double eps = 1e-4;

int n, s, t;
int a[MAXN];

double sum[MAXN];

bool check(double m)
{
	sum[0] = 0.0;
    std::deque<int> q;
	for (int i=1;i<=n;i++)
        sum[i] = sum[i-1] - m + a[i];

	for (int i=s; i<=n; ++i)
	{
		while (!q.empty() && sum[q.back()] > sum[i-s])
            q.pop_back();
		q.push_back(i-s);
		if (i - q.front() > t)
            q.pop_front();
		if (sum[i]-sum[q.front()] >= 0.0)
            return true;
	}
	return false;
}

int main()
{
	n=rd(); s=rd(); t=rd();
	for (int i=1; i<=n; ++i)
        a[i] = rd();

	double l=-1e4, r=1e4, mid;
	while (r-l > eps)
	{
		mid = (l+r)/2.0;
		if (check(mid))
            l = mid;
		else r = mid;
	}
	printf("%.3lf", l);
}