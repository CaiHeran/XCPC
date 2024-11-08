#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

int lena, lenb;
char a[2002], b[2002];

int DP()
{
    int dp[2002][2002];
    memset(dp, 0xcf, sizeof(**dp)*2002*(lena+1));

    for (int i=0; i<=lenb; ++i)
        dp[0][i] = i;
    for (int i=1; i<=lena; ++i)
        dp[i][0] = i;

    using std::min;
    for (int i=1; i<=lena; ++i)
        for (int j=1; j<=lenb; ++j)
            if (a[i]==b[j])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({dp[i][j-1], dp[i-1][j], dp[i-1][j-1]});
    return dp[lena][lenb];
}

int main()
{
    using namespace std;
    scanf("%s %s", a+1, b+1);
    lena = strlen(a+1);
    lenb = strlen(b+1);

    cout << DP() << flush;
}