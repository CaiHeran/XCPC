// P3369 【模板】普通平衡树
// [template] pbds tree multitree

#include <cstdio>
#include <iostream>
#include <unordered_map>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

namespace pbds = __gnu_pbds;

template <typename T=int>
T rd()
{
    T n; char c;
    while (c=getchar(), c<'0'||'9'<c)
        if (c=='-') return -rd();
    n = c-'0';
    while (c=getchar(), '0'<=c&&c<='9')
        n = n*10 + (c-'0');
    return n;
}

int main()
{
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    struct pair {
        int n, uuid;
        bool operator<(const pair& p) const
            { return n<p.n || (n==p.n && uuid<p.uuid); }
    };

    pbds::tree<pair, pbds::null_type, std::less<pair>, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>
        tr;

    int n=rd();
    int uuid=0;

    while (n--)
    {
        int opt=rd(), x=rd();
        switch (opt)
        {
        using std::cout;
        case 1: // insert
            tr.insert({x,++uuid});
            break;
        case 2: // delete
            tr.erase(tr.lower_bound({x,0}));
            break;
        case 3: // get order
            cout << tr.order_of_key({x,0})+1 << '\n';
            break;
        case 4: // find by order
            cout << tr.find_by_order(x-1)->n << '\n';
            break;
        case 5: // find prev
            cout << (--tr.lower_bound({x,0}))->n << '\n';
            break;
        case 6: // find suc
            cout << tr.lower_bound({x+1,0})->n << '\n';
            break;
        }
    }
    std::cout << std::flush;
}