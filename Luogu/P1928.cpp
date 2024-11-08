#include <cstdio>
#include <string>
#include <cstring>
using std::string;

int i=0;
char s[20002];
string unfold()
{
	int n = s[++i]-'0';
	if ('0'<=s[i+1]&&s[i+1]<='9')
		n = n*10 + (s[++i]-'0');
	++i;
	string str;
	for (; s[i]; ++i)
		if (s[i]=='[')
			str += unfold();
		else if (s[i]==']'){
			string stra;
			while (n--)
				stra += str;
			return stra;
		}
		else
			str += s[i];
}

int main()
{
	scanf("%s", s);
	for (; s[i]; ++i)
	{
		while (s[i] && s[i]!='[')
			putchar(s[i]), ++i;
		printf("%s", unfold().c_str());
	}
}
