#include <iostream>
#include <string>

inline int map(char c)
{
	if ('0'<=c&&c<='9')
		return c-'0';
	if ('A'<=c&&c<='Z')
		return c-'A'+10;
	if ('a'<=c&&c<='z')
		return c-'a'+10;
}

std::string turn(std::string sn, int b1, int b2)
{
	static char m[]="0123456789ABCDEF";
	int n=0;
	for (char c: sn)
		n = n*b1 + map(c);

	std::string s;
	while (n)
	{
		s += m[n%b2];
		n /= b2;
	}
	for (auto it = s.rbegin(); it!=s.rend(); ++it)
		std::cout << *it;
}

int main()
{
	using namespace std;
	int b1, b2;
	string s;
	cin >> b1 >> s >> b2;
	turn(s, b1, b2);
}
