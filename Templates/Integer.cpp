
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

#if __cpp_lib_print
#include <print>
#endif

class Integer
{
    using digit_t = std::uint32_t;
    using twodigits_t = std::uint64_t;
    constexpr static int Digit10Width = 9;
    constexpr static digit_t Base = 10'0000'0000;
protected:
    std::vector<digit_t> digits;
    //bool sign;
public:
    Integer() {
        digits.push_back(0);
    }
    Integer(std::string_view s)
    {
        size_t len = s.size();
        size_t i = len % Digit10Width;
        digits.resize(len/Digit10Width + (i>0));

        constexpr auto todigit = [](std::string_view s) -> digit_t {
            digit_t res = 0;
            for (char c : s)
                res = res*10 + (c-'0');
            return res;
        };

        if (i)
            digits.back() = todigit(s.substr(0, i));
        for (int di=0; len >= Digit10Width; di++, len-=Digit10Width)
            digits[di] = todigit(s.substr(len-Digit10Width, Digit10Width));
    }

    void load(std::string_view s)
    {
        *this = Integer(s);
    }

    static Integer zero()
    {
        return Integer();
    }
    bool iszero() const
    {
        return digits.size()==1 && digits[0]==0;
    }

#if __cpp_lib_three_way_comparison >= 201907L
    constexpr std::strong_ordering operator<=>(const Integer& rhs) const
    {
        if (digits.size() < rhs.digits.size())
            return std::strong_ordering::less;
        if (digits.size() > rhs.digits.size())
            return std::strong_ordering::greater;
        for (size_t i=digits.size(); i>0; i--)
        {
            if (digits[i-1] < rhs.digits[i-1])
                return std::strong_ordering::less;
            if (digits[i-1] > rhs.digits[i-1])
                return std::strong_ordering::greater;
        }
        return std::strong_ordering::equal;
    }
#endif
    bool operator<(const Integer& rhs) const
    {
        if (digits.size() < rhs.digits.size())
            return true;
        if (digits.size() > rhs.digits.size())
            return false;
        for (size_t i=digits.size(); i>0; i--)
        {
            if (digits[i-1] < rhs.digits[i-1])
                return true;
            if (digits[i-1] > rhs.digits[i-1])
                return false;
        }
        return false;   // equal
    }

    friend Integer operator+(const Integer& lhs, const Integer& rhs)
    {
        Integer res;
        const Integer &o = [&lhs, &rhs, &res]{
            if (lhs.digits.size() < rhs.digits.size()) {
                res = rhs;
                return lhs;
            }
            else {
                res = lhs;
                return rhs;
            }
        }();
        digit_t carry = 0;
        for (size_t i=0; i<o.digits.size(); i++)
        {
            res.digits[i] += o.digits[i] + carry;
            if (res.digits[i] >= Base) {
                res.digits[i] -= Base;
                carry = 1;
            }
            else
                carry = 0;
        }
        for (size_t i=o.digits.size(); i<res.digits.size(); i++)
        {
            res.digits[i] += carry;
            if (res.digits[i] >= Base) {
                res.digits[i] -= Base;
                carry = 1;
            }
            else
                return res;
        }
        if (carry)
            res.digits.push_back(carry);
        return res;
    }
    // requiring lhs >= rhs
    Integer& sub(const Integer& rhs)
    {
        digit_t borrow = 0;
        for (size_t i=0; i<rhs.digits.size(); i++)
        {
            if (digits[i] < rhs.digits[i] + borrow) {
                digits[i] += Base - rhs.digits[i] - borrow;
                borrow = 1;
            }
            else {
                digits[i] -= rhs.digits[i] + borrow;
                borrow = 0;
            }
        }
        for (size_t i=rhs.digits.size(); borrow && i<digits.size(); i++)
        {
            if (digits[i] < borrow) {
                digits[i] += Base - borrow;
                borrow = 1;
            }
            else {
                digits[i] -= borrow;
                borrow = 0;
            }
        }
        trim();
        return *this;
    }

    friend Integer operator*(const Integer &lhs, const Integer &rhs)
    {
        if (lhs.iszero() || rhs.iszero())
            return Integer();
        Integer res;
        res.digits.resize(lhs.digits.size() + rhs.digits.size(), 0);
        for (size_t i=0; i<lhs.digits.size(); i++)
        {
            twodigits_t carry = 0;
            for (size_t j=0; j<rhs.digits.size(); j++)
            {
                twodigits_t tmp = (twodigits_t)lhs.digits[i]*rhs.digits[j] + res.digits[i+j] + carry;
                res.digits[i+j] = tmp % Base;
                carry = tmp / Base;
            }
            res.digits[i+rhs.digits.size()] = carry;
        }
        return res.trim();
    }

    digit_t didigitsrem(const Integer &o)
    {
        if (o.iszero())
            throw std::domain_error("didigitsision by zero");
        //TODO
        return o.digits[0];
    }

    std::string to_string()
    {
        std::string s;
        s.reserve(digits.size() * Digit10Width);
        s.append(std::to_string(digits.back()));
        for (size_t i=digits.size()-1; i>0; i--)
        {
            std::string tmp = std::to_string(digits[i-1]);
            s.append(Digit10Width-tmp.size(), '0');
            s.append(tmp);
        }
        return s;
    }

    friend std::istream& operator>>(std::istream &is, Integer &o)
    {
        std::string s;
        is >> s;
        o = Integer(s);
        return is;
    }
#if __cpp_lib_print
    void print() const
    {
        std::print("{}", digits.back());
        for (size_t i=digits.size()-1; i>0; i--)
            std::print("{:09}", digits[i-1]); // 9==Digit10Width
    }
#endif

protected:
    digit_t& get(int index)
    {
        return digits.at(index);
    }
    digit_t get(int index) const
    {
        return digits.at(index);
    }
    Integer& trim()
    {
        while (!iszero() && digits.back()==0)
            digits.pop_back();
        return *this;
    }
    Integer sub_mul(const Integer &b, int mul, int offset)
    {
        if (mul == 0) return *this;
        int borrow = 0;
        // 与减法不同的是，borrow可能很大，不能使用减法的写法
        for (size_t i = 0; i < b.digits.size(); ++i) {
            borrow += digits[i + offset] - b.digits[i] * mul - Base + 1;
            digits[i + offset] = borrow % Base + Base - 1;
            borrow /= Base;
        }
        // 如果还有借位就继续处理
        for (size_t i = b.digits.size(); borrow; ++i) {
            borrow += digits[i + offset] - Base + 1;
            digits[i + offset] = borrow % Base + Base - 1;
            borrow /= Base;
        }
        return *this;
    }

public:
    Integer divrem(const Integer &b, Integer &r) const
    {
        Integer d;
        r = *this;
        if (*this < b)
            return d;
        d.digits.resize(digits.size() - b.digits.size() + 1);
        // 提前算好除数的最高三位+1的倒数，若最高三位是a3,a2,a1
        // 那么db是a3+a2/Base+(a1+1)/Base^2的倒数，最后用乘法估商的每一位
        // 此法在base<=32768时可在int32范围内用
        // 但即使使用int64，那么也只有base<=131072时可用（受double的精度限制）
        // 能保证估计结果q'与实际结果q的关系满足q'<=q<=q'+1
        // 所以每一位的试商平均只需要一次，只要后面再统一处理进位即可
        // 如果要使用更大的base，那么需要更换其它试商方案
        double t = (b.get(b.digits.size() - 2) +
                    (b.get(b.digits.size() - 3) + 1.0) / Base);
        double db = 1.0 / (b.digits.back() + t / Base);
        for (size_t i = digits.size() - 1, j = d.digits.size() - 1; j <= digits.size();) {
            int rm = r.get(i + 1) * Base + r.get(i);
            int m = std::max((digit_t)(db * rm), r.get(i + 1));
            r.sub_mul(b, m, j);
            d.digits[j] += m;
            if (!r.get(i + 1))  // 检查最高位是否已为0，避免极端情况
                --i, --j;
        }
        r.trim();
        // 修正结果的个位
        int carry = 0;
        while (!(r<b)) {
            r.sub(b);
            ++carry;
        }
        // 修正每一位的进位
        for (size_t i = 0; i < d.digits.size(); ++i) {
            carry += d.digits[i];
            d.digits[i] = carry % Base;
            carry /= Base;
        }
        return d.trim();
    }
    Integer operator/(const Integer& rhs)
    {
        Integer r;
        return divrem(rhs, r);
    }
};

int main()
{
    Integer a;
    Integer b;

    while (std::cin >> a >> b)
    {
        std::cout << (a/b).to_string() << '\n';
    }

    return 0;
}