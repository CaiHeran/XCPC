// 使用数组模拟的垃圾写法
#include <iostream>
#include <bitset>

int main()
{
    bool flag=false;
    std::size_t n, rest, a, now=0;
    std::bitset<40001> bits;
    std::cin >> n;
    rest = n*n;
    while (rest){
        std::cin >> a;
        rest -= a;
        if (flag)
            while (a--)
                bits.set(++now);
        else
            now += a;
        flag = !flag;
    }
    uint_fast16_t i=1, j;
    while (i <= now){
        for (j=0; j<n; ++j)
            std::cout << bits[i+j];
        std::cout << std::endl;
        i += n;
    }
}