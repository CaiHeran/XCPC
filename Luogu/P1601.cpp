
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char a[1005], b[1005];
    char s[3000];
    while (scanf("%s%s", a, b) != EOF)
    {
        //sprintf(s, "python -c ", a, b);
        //system(s);
        execl("python", "-c", "\"print(%s + %s)\"", NULL);
    }
}