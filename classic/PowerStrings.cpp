
#include <cstdio>
#include <cstring>

int len;
char target[1000002];
int p[1000002];

void pre()
{
    p[1] = 0;
    int j = 0;
    for (int i=1; i<len; ++i)
    {
        while (j>0 && target[j+1]!=target[i+1])
            j = p[j];
        if (target[j+1]==target[i+1])
            ++j;
        p[i+1] = j;
    }
}

int main()
{
    while (true)
    {
        scanf("%s", target+1);
        len = strlen(target+1);

        if (len==1 && target[1]=='.')   // 结束标志依题意有所不同
            return 0;

        pre();
        printf("%d\n", len%(len-p[len])? len: len/(len-p[len]));
    }
}