
#include <cstdio>
#include <cstring>

const int MAXN = 1e6+2;

class KMP
{
public:
    int len;
    char target[MAXN];
    int p[MAXN]{};

    void init()
    {
        len = strlen(target+1);
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

    int find(const char *s) const
    {
        int j=0;
        for (int i=0; s[i+1]; ++i)
        {
            while (j>0 && target[j+1] != s[i+1])
                j = p[j];
            if (target[j+1] == s[i+1])
                ++j;
            if (j == len)
                return true;
        }
        return false;
    }
};

class Trie_AC
{
public:
    int tot=1;
    int word[MAXN]{};
    int next[MAXN]{};
    int tree[MAXN][26]{};

    void insert(const char *pattern)
    {
        int u=1, c;
        for (; *pattern; ++pattern)
        {
            c = *pattern - 'a';
            if (!tree[u][c])
                tree[u][c] = ++tot;
            u = tree[u][c];
        }
        ++word[u];
    }

    void init_next() // BFS
    {
        for (int i=0; i<26; ++i)
            tree[0][i] = 1;

        int u, queue[MAXN]={1};
        next[1] = 0;

        for (int p=0, end=0; p<=end; ++p)
        {
            u = queue[p];
            for (int i=0; i<26; ++i)
                if (!tree[u][i])
                    tree[u][i] = tree[next[u]][i];  //*重点
                else{
                    queue[++end] = tree[u][i],
                    next[tree[u][i]] = tree[next[u]][i];
                }
        }
    }

    int AC_auto(const char *s)  // 一次性函数，默认只有小写字母
    {
        int cnt=0, u=1, c, k;
        for (; *s; ++s)
        {
            c = *s - 'a';
            k = tree[u][c];
            while (k>1){
                cnt += word[k];
                word[k] = 0;    // 不重复计数
                k = next[k];
            }
            u = tree[u][c];
        }
        return cnt;
    }
};

int main()
{
    int n;
    scanf("%d", &n);
    char s[MAXN];
    if (n==1){
        KMP kmp;
        scanf("%s", kmp.target+1);
        kmp.init();
        scanf("%s", s+1);
        printf("%d", kmp.find(s));
    }
    else{
        Trie_AC trac;
        while (n--) {
            scanf("%s", s);
            trac.insert(s);
        }
        trac.init_next();
        scanf("%s", s);
        printf("%d", trac.AC_auto(s));
    }
}