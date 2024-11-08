// P4942
// math
// @date 2021-09-25

#include <iostream>

/*
 sum l..r = (l+r)*(r-l+1)/2;
*inv(1/2)==5

 2*x=1(mod 9)
 x=5
*/

int main()
{
	int T;
	std::cin >> T;
	while (T--)
	{
		long long l, r;	// l<=r<=1e12
		std::cin >> l >> r;
		std::cout << (l+r)%9*(r-l+1)%9*5%9 << '\n';
	}
}
