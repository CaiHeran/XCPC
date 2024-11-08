
#include <cstdio>
#include <cstring>

int len;
char s[105];
int lo[105]{};

void solve()
{
    int top=0;
    struct ttt {
        char c;
        int x;
    } stack[105];
    for (int i=1; i<=len; ++i)
    {
        char t;
        switch (s[i]) {
        case '(':
        case '[':
            stack[++top] = {s[i], i};
            continue;
        case ')':
            t = '(';
            break;
        case ']':
            t = '[';
        }
        if (top<1 || stack[top].c!=t)
            continue;
        lo[stack[top].x] = i,
        lo[i] = stack[top].x;
        --top;
    }
}

int main()
{
    scanf("%s", s+1);
    len = strlen(s+1);
    solve();

    for (int i=1; i<=len; ++i)
        if (lo[i]) putchar(s[i]);
        else
            if (s[i]=='('||s[i]==')')
                printf("()");
            else printf("[]");
}