#include <iostream>
#include <string>
#include <queue>
#include <set>

using std::string;
int  n=0;
string f, o;
string pat[6], rep[6];
std::set<string> set;
struct Struct{
	string str;
	int step;
}t;

int search_bfs()
{
	string::size_type p;
	std::queue<Struct> q;
	q.push({f,0});
	while (!q.empty())
	{
		t = q.front();
		q.pop();
		if (t.step>10) goto NoAnswer;
		++t.step;
		for (int i=0; i<n; ++i)
		{
		  std::set<string::size_type> pset;
		  for (decltype(p) j=0; j<=t.str.size(); ++j)
			if (p=t.str.find(pat[i], j), p!=string::npos && !pset.count(p))
			{
				pset.insert(p);
				string s=t.str;
				s.replace(p, pat[i].size(), rep[i]);
				if (!set.count(s)){
					if (s==o) return t.step;
					set.insert(s), q.push({s, t.step});
				}
			}
		}
	}
	NoAnswer:
	throw "NO ANSWER!";
}

int main()
{
	std::cin >> f >> o;
	while (std::cin>>pat[n]>>rep[n])
		++n;
	try{std::cout << search_bfs();}
	catch(const char* s)
	  { std::cout << s; }
}
