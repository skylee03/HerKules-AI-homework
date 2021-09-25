#include "fotile_tree.h"

#include <stack>
#include <cassert>
#include <iostream>

constexpr int MAXV = 2e7;

void insert_test() {
    std::cout << "insert test" << std::endl;
    skylee::fotile_tree<MAXV> tree;
    tree.insert(10);
    tree.insert(2);
    tree.insert(1);
    tree.insert(19260817);
    tree.insert(4);
    tree.insert(40);

    assert(tree.find_by_order(1) == 1);
    assert(tree.find_by_order(2) == 2);
    assert(tree.find_by_order(3) == 4);
    assert(tree.find_by_order(4) == 10);
    assert(tree.find_by_order(5) == 40);
    assert(tree.find_by_order(6) == 19260817);

    tree.insert(1);
    tree.insert(1);
    tree.insert(4);

    assert(tree.find_by_order(1) == 1);
    assert(tree.find_by_order(2) == 1);
    assert(tree.find_by_order(3) == 1);
    assert(tree.find_by_order(4) == 2);
    assert(tree.find_by_order(5) == 4);
    assert(tree.find_by_order(6) == 4);
    assert(tree.find_by_order(7) == 10);
    assert(tree.find_by_order(8) == 40);
    assert(tree.find_by_order(9) == 19260817);
    std::cout << "pass test" << std::endl << std::endl;
}

void erase_test() {
    std::cout << "erase test" << std::endl;
    skylee::fotile_tree<MAXV> tree;
    tree.insert(10);
    tree.insert(2);
    tree.insert(1);
    tree.insert(19260817);
    tree.insert(4);
    tree.insert(40);

    tree.erase(2);

    assert(tree.find_by_order(1) == 1);
    assert(tree.find_by_order(2) == 4);
    assert(tree.find_by_order(3) == 10);
    assert(tree.find_by_order(4) == 40);
    assert(tree.find_by_order(5) == 19260817);

    //tree.erase(0);
    tree.erase(2);
    tree.erase(233);

    assert(tree.find_by_order(1) == 1);
    assert(tree.find_by_order(2) == 4);
    assert(tree.find_by_order(3) == 10);
    assert(tree.find_by_order(4) == 40);
    assert(tree.find_by_order(5) == 19260817);

    tree.erase(1);
    tree.erase(40);

    assert(tree.find_by_order(1) == 4);
    assert(tree.find_by_order(2) == 10);
    assert(tree.find_by_order(3) == 19260817);

    tree.insert(4);
    tree.insert(10);
    tree.erase(4);
    tree.erase(10);

    assert(tree.find_by_order(1) == 4);
    assert(tree.find_by_order(2) == 10);
    assert(tree.find_by_order(3) == 19260817);

    std::cout << "pass test" << std::endl << std::endl;
}

void rollback_test() {
    std::cout << "rollback test" << std::endl;
    skylee::fotile_tree<MAXV> tree;
    tree.insert(10);         // version 1 {10}
    tree.insert(2);          // version 2 {2, 10}
    tree.insert(1);          // version 3 {1, 2, 10}
    tree.insert(19260817);   // version 4 {1, 2, 10, 19260817}
    tree.insert(4);          // version 5 {1, 2, 4, 10, 19260817}
    tree.insert(40);         // version 6 {1, 2, 4, 10, 40, 19260817}

    tree.rollback(3);     // version 3 {1, 2, 10}

    assert(tree.find_by_order(1) == 1);
    assert(tree.find_by_order(2) == 2);
    assert(tree.find_by_order(3) == 10);

    tree.insert(233);        // version 4 {1, 2, 10, 233}
    tree.insert(3);          // version 5 {1, 2, 3, 10, 233}


    assert(tree.find_by_order(1) == 1);
    assert(tree.find_by_order(2) == 2);
    assert(tree.find_by_order(3) == 3);
    assert(tree.find_by_order(4) == 10);
    assert(tree.find_by_order(5) == 233);

    tree.rollback(5);     // version 5 {1, 2, 3, 10, 233}
    tree.erase(10);       // version 6 {1, 2, 3, 233}

    assert(tree.find_by_order(1) == 1);
    assert(tree.find_by_order(2) == 2);
    assert(tree.find_by_order(3) == 3);

    tree.rollback(5);     // version 5 {1, 2, 3, 10, 233}

    assert(tree.find_by_order(1) == 1);
    assert(tree.find_by_order(2) == 2);
    assert(tree.find_by_order(3) == 3);
    assert(tree.find_by_order(4) == 10);
    assert(tree.find_by_order(5) == 233);

    std::cout << "pass test" << std::endl << std::endl;
}
int main() {
    insert_test();
    erase_test();
    rollback_test();
}