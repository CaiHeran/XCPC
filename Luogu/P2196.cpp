#include <iostream>
#include <array>

int t, n, ans=0;
int num[21];
bool vis[21]{};
bool m[21][21];
int len, path[21], anspath[21];

void dfs(int x, int sum=0, int fl=0)
{
	sum += num[x];
	path[fl] = x;
	bool no=true;
	for (int i=1; i<=n; ++i)
		if (m[x][i] && !vis[i]){
			no = false;
			vis[i] = true;
			dfs(i, sum, fl+1);
			vis[i] = false;
		}
	if (no && sum>ans){
		ans = sum;
		len = fl;
		for (int i=1; i<=fl; ++i)
			anspath[i] = path[i];
		return;
	}
}

int main()
{
	using std::cin;
	using std::cout;
	cin >> n;
	for (int i=1; i<=n; ++i)
		cin >> num[i];
	for (int i=1; i<n; ++i)
		for (int j=i+1; j<=n; ++j)
			cin >> m[i][j];

	for (int i=1; i<=n; ++i)	// 构造“开始节点” 
		m[0][i] = true;
	dfs(0);
	for (int i=1; i<len; ++i)
		cout << anspath[i] << ' ';
	cout << anspath[len] << '\n' << ans;
}
