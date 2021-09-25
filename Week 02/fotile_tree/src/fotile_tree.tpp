#include "fotile_tree.h"

namespace skylee {

template<int max_value>
void fotile_tree<max_value>::node::add(const int &b, const int &e, const int &x, const int &d) {
    if(d == -1 && val == 0) return;
    if(b == e) {
        val += d;
        return;
    }
    const int mid = (b + e) / 2;
    if(x <= mid) {
        lson = lson != nullptr ? new node(lson) : new node();
        lson->add(b, mid, x, d);
    } else {
        rson = rson != nullptr ? new node(rson) : new node();
        rson->add(mid + 1, e, x, d);
    }
    val = 0;
    val += lson != nullptr ? lson->val : 0;
    val += rson != nullptr ? rson->val : 0;
}

template<int max_value>
int fotile_tree<max_value>::node::find_by_order(const int &b, const int &e, const int &k) const {
    if(b == e) return b;
    const int mid = (b + e) / 2;
    if(lson == nullptr) {
        return rson->find_by_order(mid + 1, e, k);
    } else if(k > lson->val) {
        return rson->find_by_order(mid + 1, e, k - lson->val);
    } else {
        return lson->find_by_order(b, mid, k);
    }
}

template<int max_value>
fotile_tree<max_value>::node::node()
    : val(0), lson(nullptr), rson(nullptr) {};

template<int max_value>
fotile_tree<max_value>::node::node(const node * const p)
    : val(p->val), lson(p->lson), rson(p->rson) {};

template<int max_value>
void fotile_tree<max_value>::node::insert(const int &x) {
    add(1,max_value,x,1);
}

template<int max_value>
void fotile_tree<max_value>::node::erase(const int &x) {
    add(1,max_value,x,-1);
}

template<int max_value>
int fotile_tree<max_value>::node::find_by_order(const int &k) const {
    return 1 <= k && k <= val ? find_by_order(1,max_value,k) : -1;
}

template<int max_value>
typename fotile_tree<max_value>::node *fotile_tree<max_value>::root() const {
    return roots.top();
}

template<int max_value>
fotile_tree<max_value>::fotile_tree() {
    roots.push(new fotile_tree<max_value>::node());
}

template<int max_value>
void fotile_tree<max_value>::insert(const int &x) {
    roots.push(new fotile_tree<max_value>::node(root()));
    root()->insert(x);
}

template<int max_value>
void fotile_tree<max_value>::erase(const int &x) {
    roots.push(new fotile_tree<max_value>::node(root()));
    root()->erase(x);
}

template<int max_value>
int fotile_tree<max_value>::find_by_order(const int &k) const {
    return root()->find_by_order(k);
}

template<int max_value>
int fotile_tree<max_value>::version() const {
    return roots.size() - 1;
}

template<int max_value>
void fotile_tree<max_value>::rollback(const int &v) {
    while(version() > v) roots.pop();
}

}