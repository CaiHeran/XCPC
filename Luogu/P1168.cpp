
/*
  给出一个长度为N的非负整数序列A_i​，对于所有1≤k≤(N+1)/2, 1≤k≤(N+1)/2，
输出A_1,A_1∼A_3,…,A_1∼A_{2k−1}​的中位数。即前1,3,5,…个数的中位数。

对于100%的数据，N≤100000。
*/

#include <cstdio>

template <typename T=int>
T rd()
{
    T n; char c=getchar();
    while (c<'0'||'9'<c)
        c = getchar();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + (c-'0');
    return n;
}
template <typename T>
void print(T n)
{
    if (n>9)
        print(n/10);
    putchar(n%10|48);
}
template<class T>
inline void printl(T n)
    { print(n); putchar(10); }

#include <queue>

int main()
{
    int n = rd();
    std::priority_queue<int> le;
    std::priority_queue<int, std::vector<int>, std::greater<int>> gr;
    int a=rd();
    le.push(a);
    printl(a);
    for (int i=3; i<=n; ++i)
    {
        if (a<=le.top())
            le.push(a);
        else
            gr.push(a);
        if (i&1)
        {
            while (le.size()-1 > gr.size())
                gr.push(le.top()), le.pop();
            while (le.size() < gr.size())
                le.push(gr.top()), gr.pop();
            printl(le.top());
        }
    }
}