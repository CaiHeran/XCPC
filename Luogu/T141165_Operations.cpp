
#include <iostream>
#include <algorithm>

int main()
{
    using std::cout;
    int a,b, c,d;
    std::cin >> a >> b >> c >> d;
    if (!a) {
        cout << (b? d:0);
    }
    else if (a==b && c==1){
        cout << c;
    }
    else if (c==1){
        cout << (a+b)/2 + d;
    }
    else
        cout << c+d;
}