
#include <cstdio>
#include <cstdint>

int main()
{
    int n, q;
    uint64_t m, max=0ull, ans, sum, arr[100000];
    scanf("%d", &n);
    for (int i=0; i<n; ++i){
        scanf("%llu", arr+i);
        if (arr[i] > max)
            max = arr[i];
    }
    scanf("%d", &q);

    while (q--){
        scanf("%llu", &m);
        if (m < max){
            printf("-1\n");
            continue;
        }
        for (ans=m; ans>=max; --ans){
            sum = 0ull;
            for (int b=0; b<n; ++b)
                sum += arr[b] ^ ans;
            if (sum <= m)
                break;
        }
        printf("%llu\n", ans);
    }
}