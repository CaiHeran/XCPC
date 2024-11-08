
#include <cstdlib>
#include <cstdint>
#include <memory>
#include <random>
#include <algorithm>
#include <print>
#include <iostream>

namespace SkipList
{

using int32 = std::int32_t;
using uint32 = std::uint32_t;

/**
 * May unify the SkipList and SkipArray into a single class.
 * 
 * The spans stored in SkipList seem to be redundant,
 * and they are only useful in SkipArray (for the index functions) (haha).
 * That's why I say maybe they should be unified.
 * Or maybe I should just remove the spans in SkipList.
 */

constexpr static int MAX_LEVEL = 32;
constexpr static float P = 0.25;

int _randomlevel()
{
    thread_local std::mt19937 gen(std::random_device{}());
    thread_local std::bernoulli_distribution d(P);
    int level = 1;
    while (d(gen))
        level++;
    return std::max(level, MAX_LEVEL);
}

template <typename Tk, typename Tv>
struct Node
{
    using type = Node<Tk, Tv>;
    using pointer = type*;

    Tk key;
    Tv value;
    pointer back;     // backword
    struct Level {
        pointer fore; // forward
        std::uint32_t span;
    } levels[];

    template <typename T_k, typename T_v>
    static pointer Create(int level, T_k&& key = Tk{}, T_v&& value = Tv{})
    {
        pointer node = (pointer)malloc(sizeof(type) + level * sizeof(Level));
        new (&node->key) Tv(std::forward<T_k>(key));
        new (&node->value) Tv(std::forward<T_v>(value));
        node->back = nullptr;
        for (int i = 0; i < level; i++)
        {
            node->levels[i].fore = nullptr;
            node->levels[i].span = 0;
        }
        return node;
    }
    static void Destroy(pointer node)
    {
        if constexpr (std::is_destructible_v<Tk>)
            node->key.~Tk();
        if constexpr (std::is_destructible_v<Tv>)
            node->value.~Tv();
        free(node);
    }
};

template <typename Tv>
struct Node<void, Tv>
{
    using type = Node<void, Tv>;
    using pointer = type*;

    Tv value;
    pointer back;
    struct Level {
        pointer fore;
        std::uint32_t span;
    } levels[];

    template <typename T>
    static pointer Create(int level, T&& value = Tv{})
    {
        pointer node = (pointer)malloc(sizeof(type) + level * sizeof(Level));
        new (&node->value) Tv(std::forward<T>(value));
        node->back = nullptr;
        for (int i = 0; i < level; i++)
        {
            node->levels[i].fore = nullptr;
            node->levels[i].span = 0;
        }
        return node;
    }
    static void Destroy(pointer node)
    {
        if constexpr (std::is_destructible_v<Tv>)
            node->value.~Tv();
        free(node);
    }
};

template <typename Tk, typename Tv>
class SkipList
{
private:
    using Node = Node<Tk, Tv>;
    int level, length; // level: level of the list. length: number of elements in the list
    Node *head, *tail;

public:
    SkipList() : level(1), length(0)
    {
        head = Node::Create(MAX_LEVEL, Tk{}, Tv{});
        tail = nullptr;
        head->back = nullptr;
        for (int i = 0; i < MAX_LEVEL; i++)
        {
            head->levels[i].fore = nullptr;
            head->levels[i].span = 0;
        }
    }

    Tv& get(Tk key)
    {
        Node *x = head;
        for (int i = level - 1; i >= 0; i--)
        {
            while (x->levels[i].fore && x->levels[i].fore->key < key)
                x = x->levels[i].fore;
        }
        x = x->levels[0].fore;
        if (x && x->key == key)
            return x->value;
        return head->value;
    }

    // modify if key exists (return false), otherwise insert (return true)
    bool update(Tk key, Tv value)
    {
        Node *x = head;
        uint32 rank[MAX_LEVEL];
        Node *update[MAX_LEVEL];
        for (int i = level - 1; i >= 0; i--)
        {
            rank[i] = i==(level-1) ? 0 : rank[i+1];
            while (x->levels[i].fore && x->levels[i].fore->key < key)
            {
                rank[i] += x->levels[i].span;
                x = x->levels[i].fore;
            }
            update[i] = x;
        }
        x = x->levels[0].fore;
        if (x && x->key == key)
        {
            x->value = value;
            return false;
        }

        int newLevel = _randomlevel();
        if (newLevel > level)
        {
            for (int i = level; i < newLevel; i++)
            {
                rank[i] = 0;
                update[i] = head;
                update[i]->levels[i].span = length;
            }
            level = newLevel;
        }
        x = Node::Create(newLevel, key, value);
        for (int i = 0; i < newLevel; i++)
        {
            x->levels[i].fore = update[i]->levels[i].fore;
            update[i]->levels[i].fore = x;

            x->levels[i].span = update[i]->levels[i].span - (rank[0] - rank[i]);
            update[i]->levels[i].span = (rank[0] - rank[i]) + 1;
        }
        for (int i = newLevel; i < level; i++)
        {
            update[i]->levels[i].span++;
        }
        x->back = (update[0] == head) ? nullptr : update[0];
        if (x->levels[0].fore)
            x->levels[0].fore->back = x;
        else
            tail = x;
        length++;
        return true;
    }

    bool erase(Tk key)
    {
        Node *x = head;
        Node *update[MAX_LEVEL];
        for (int i = level - 1; i >= 0; i--)
        {
            while (x->levels[i].fore && x->levels[i].fore->key < key)
                x = x->levels[i].fore;
            update[i] = x;
        }
        x = x->levels[0].fore;
        if (!x || x->key != key)
            return false;
        for (int i = 0; i < level; i++)
        {
            if (update[i]->levels[i].fore == x)
            {
                update[i]->levels[i].span += x->levels[i].span - 1;
                update[i]->levels[i].fore = x->levels[i].fore;
            }
            else
            {
                update[i]->levels[i].span--;
            }
        }
        if (x->levels[0].fore)
            x->levels[0].fore->back = x->back;
        else
            tail = x->back;
        Node::Destroy(x);
        while (level > 1 && !head->levels[level-1].fore)
            level--;
        length--;
        return true;
    }

    ~SkipList()
    {
        Node *x = head;
        do {
            Node *next = x->levels[0].fore;
            Node::Destroy(x);
            x = next;
        } while (x);
    }
};

/**
 * SkipArray<Tv> can be seen as SkipList<void, Tv>
 */

template <typename Tv>
class SkipArray
{
private:
    using Node = Node<void, Tv>;
    int level, length; // level: level of the list. length: number of elements
    Node *head, *tail;

public:
    SkipArray() : level(1), length(0)
    {
        head = Node::Create(MAX_LEVEL, Tv{});
        tail = nullptr;
        head->back = nullptr;
        for (int i = 0; i < MAX_LEVEL; i++)
        {
            head->levels[i].fore = nullptr;
            head->levels[i].span = 0;
        }
    }

    Tv& operator[](uint32 index)
    {
        // Expects(index <= length);
        uint32 rank = 0;
        Node *x = head;
        for (int i = level - 1; i >= 0; i--)
        {
            while (x->levels[i].fore && rank + x->levels[i].span <= index)
            {
                rank += x->levels[i].span;
                x = x->levels[i].fore;
            }
        }
        return x->value;
    }

    bool insert(uint32 index, Tv value)
    {
        // Expects(index <= length);
        Node *x = head;
        uint32 rank[MAX_LEVEL];
        Node *update[MAX_LEVEL];
        for (int i = level - 1; i >= 0; i--)
        {
            rank[i] = i==(level-1) ? 0 : rank[i+1];
            while (x->levels[i].fore && rank[i] + x->levels[i].span < index)
            {
                rank[i] += x->levels[i].span;
                x = x->levels[i].fore;
            }
            update[i] = x;
        }

        int newLevel = _randomlevel();
        if (newLevel > level)
        {
            for (int i = level; i < newLevel; i++)
            {
                rank[i] = 0;
                update[i] = head;
                update[i]->levels[i].span = length;
            }
            level = newLevel;
        }
        x = Node::Create(newLevel, value);
        for (int i = 0; i < newLevel; i++)
        {
            x->levels[i].fore = update[i]->levels[i].fore;
            update[i]->levels[i].fore = x;

            x->levels[i].span = update[i]->levels[i].span - (rank[0] - rank[i]);
            update[i]->levels[i].span = (rank[0] - rank[i]) + 1;
        }
        for (int i = newLevel; i < level; i++)
        {
            update[i]->levels[i].span++;
        }
        x->back = (update[0] == head) ? nullptr : update[0];
        if (x->levels[0].fore)
            x->levels[0].fore->back = x;
        else
            tail = x;
        length++;
        return true;
    }

    template <typename T>
    void push_back(T&& value)
    {
        insert(length, std::forward<T>(value));
    }

    void erase(uint32 index)
    {
        // Excpects(index < length);
        uint32 rank = 0;
        Node *x = head;
        Node *update[MAX_LEVEL];
        for (int i = level - 1; i >= 0; i--)
        {
            while (x->levels[i].fore && rank + x->levels[i].span < index)
                x = x->levels[i].fore, rank += x->levels[i].span;
            update[i] = x;
        }
        x = x->levels[0].fore;
        rank++;
        for (int i = 0; i < level; i++)
        {
            if (update[i]->levels[i].fore == x)
            {
                update[i]->levels[i].span += x->levels[i].span - 1;
                update[i]->levels[i].fore = x->levels[i].fore;
            }
            else
            {
                update[i]->levels[i].span--;
            }
        }
        if (x->levels[0].fore)
            x->levels[0].fore->back = x->back;
        else
            tail = x->back;
        Node::Destroy(x);
        while (level > 1 && !head->levels[level-1].fore)
            level--;
        length--;
    }

    ~SkipArray()
    {
        Node *x = head;
        do {
            Node *next = x->levels[0].fore;
            Node::Destroy(x);
            x = next;
        } while (x);
    }
};

}

int main()
{
    SkipList::SkipList<int, int> list;
    list.update(1, 1);
    list.update(2, 2);
    list.update(2, 3);

    // std::println("{}", list.get(2));

    SkipList::SkipArray<int> arr;
    arr.insert(0, 1);
    arr.insert(1, 2);
    arr.insert(2, 3);
    arr.erase(1);

    std::println("{}", arr[1]);
}