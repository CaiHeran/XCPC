
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cout;

template <class CharT = char>
class KMP
{
    int len_;
    const CharT *p;
    std::vector<int> f{};

public:
    void compile(const CharT *s, int lens)
    {
        this->p = s;
        this->len_ = lens;
        f.resize(len_);
        f[0] = -1;
        for (int i=+1, j=-1; s[i]; ++i)
        {
            while (j>=0 && s[j+1] != s[i])
                j = f[j];
            if (s[j+1] == s[i])
                ++j;
            f[i] = j;
        }
    }

    template <class Call_Back>
    unsigned kmp(const CharT *t, Call_Back call_back=nullptr) const noexcept
    {
        int cnt=0, j=-1;
        for (int i=0; t[i]; ++i)
        {
            while (j>=0 && p[j+1] != t[i])
                j = f[j];
            if (p[j+1] == t[i]) {
                ++j;
                if (j+1 == len_) {
                    j=f[j];
                    ++cnt;
                    call_back(i-len_+1);
                }
            }
        }
        return cnt;
    }

    void showf() const noexcept
    {
        for (auto i: f)
            cout << i+1 << ' ';
        cout << std::flush;
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s1, s2;
    std::cin >> s1 >> s2;

    KMP<char> p;
    p.compile(s2.c_str(), s2.size());
    p.kmp(s1.c_str(), [](auto&&n){cout << n+1 << '\n';});
    p.showf();
}