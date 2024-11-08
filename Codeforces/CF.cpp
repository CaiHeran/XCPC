#include <map>
#include <set>
#include <queue>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
using lnt = long long;

const int mxn = 100005;
const int mxm = 105;

int n, m, p, d[mxn];
lnt a[mxn];
lnt s[mxn];
lnt f[mxm][mxn];

signed main() {
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 2; i <= n; ++i)
        scanf("%d", d + i), d[i] += d[i - 1];
    for (int i = 1; i <= m; ++i) {
        int h, t;
        scanf("%d%d", &h, &t);
        a[i] = t - d[h];
    }
    sort(a + 1, a + m + 1);
    for (int i = 1; i <= m; ++i)
        s[i] = s[i - 1] + a[i];
    p = min(p, m);
    for (int i = 1; i <= p; ++i) {
        if (i == 1) {
            f[i][0] = 0;
            for (int j = 1; j <= m; ++j)
                f[i][j] = a[j] * j - s[j];
        } else {
            static int q[mxn];
            static lnt x[mxn], y[mxn];
            for (int j = 0; j <= m; ++j) {
                x[j] = j;
                y[j] = f[i-1][j] + s[j];
            }
            int l = 0, r = 0;
            q[r++] = 0;
            for (int j = 1; j <= m; ++j) {
                while (r - l > 1) {
                    int u = q[l];
                    int v = q[l + 1];
                    lnt fu = y[u] - a[j] * x[u];
                    lnt fv = y[v] - a[j] * x[v];
                    if (fu >= fv)
                        l++;
                    else
                        break;
                }
                int k = q[l];
                f[i][j] = a[j] * j - s[j] + y[k] - a[j] * x[k];
                while (r - l > 1) {
                    int u = q[r - 2];
                    int v = q[r - 1];
                    int w = j;
                    if ((y[u] - y[v]) * (x[v] - x[w]) >= (y[v] - y[w]) * (x[u] - x[v]))
                        r--;
                    else
                        break;
                }
                q[r++] = j;
            }
        }
    }
    printf("%lld\n", f[p][m]);
	return 0;
}