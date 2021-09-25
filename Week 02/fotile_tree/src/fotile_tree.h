#ifndef SKYLEE_FOTILE_TREE_H_
#define SKYLEE_FOTILE_TREE_H_

#include <stack>

namespace skylee {

template<int>
class fotile_tree {
    private:
        class node {
            private:
                void add(const int &, const int &, const int &, const int &);
                int find_by_order(const int &, const int &, const int &) const;
            public:
                int val;
                node *lson, *rson;
                node();
                node(const node * const);
                void insert(const int &);
                void erase(const int &);
                int find_by_order(const int &) const;
        };
        std::stack<node *> roots;
        node *root() const;
    public:
        fotile_tree();
        void insert(const int &);
        void erase(const int &);
        int find_by_order(const int &) const;
        int version() const;
        void rollback(const int &);
};
}

#include "fotile_tree.tpp"

#endif // SKYLEE_FOTILE_TREE_H_