#include "BinaryTree.hpp"
#include "doctest.h"
using namespace ariel;

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

const int max_rand = 1000;
const int div_factor = 100;

double NextDouble() {
    return (double)((unsigned int)rand() % max_rand) / div_factor;
}

int NextInt() {
    return (rand() % max_rand);
}

bool RandomBool() {
    return rand() % 2 == 0;
}

enum class _order {
    inorder,
    postorder,
    preorder,
};

template <typename T>
BinaryTree<T> create_dummy(int adder = 0) {
    BinaryTree<T> tree;

    // create the following tree
    //                    1
    //              2          3
    //         4        5
    //               10   11
    //             20       23
    tree.add_root(1 + adder);
    tree.add_left(1 + adder, 2 + adder);
    tree.add_right(1 + adder, 3 + adder);
    tree.add_left(2 + adder, 4 + adder);
    tree.add_right(2 + adder, 5 + adder);
    tree.add_left(5 + adder, 10 + adder);
    tree.add_right(5 + adder, 11 + adder);
    tree.add_left(10 + adder, 20 + adder);
    tree.add_right(11 + adder, 23 + adder);

    return tree;
}

template <typename T>
bool isEqual(BinaryTree<T> &tree, vector<T> const &v2, _order order) {
    auto end = tree.end_preorder();
    if (order == _order::inorder) {
        end = tree.end_inorder();
        auto pair = std::mismatch(tree.begin_inorder(), tree.end_inorder(), v2.begin());
        return (pair.first == end && pair.second == v2.end());
    } else if (order == _order::postorder) {
        end = tree.end_postorder();
        auto pair = std::mismatch(tree.begin_postorder(), tree.end_postorder(), v2.begin());
        return (pair.first == end && pair.second == v2.end());
    }
    auto pair = std::mismatch(tree.begin_preorder(), tree.end_preorder(), v2.begin());
    return (pair.first == end && pair.second == v2.end());
}

TEST_CASE("check normal order = inorder") {
    BinaryTree<int> tree = create_dummy<int>();

    auto pair = std::mismatch(tree.begin_inorder(), tree.end_inorder(), tree.begin());
    CHECK(((pair.first == tree.end_inorder()) && (pair.second == tree.end())));
}

TEST_CASE("TEST binary on ints simple") {
    srand(time(nullptr));
    // create the following tree on i = 0
    //                    1
    //              2          3
    //         4        5
    //               10   11
    //             20       23

    // inorder : 4, 10, 5, 11, 2, 1, 3
    vector<int> inorder = {4, 10, 5, 11, 2, 1, 3};
    //postorder : 4, 20, 10, 23, 11, 5, 2, 3, 1
    vector<int> postorder = {4, 20, 10, 23, 11, 5, 2, 3, 1};
    //preorder : 1, 2, 4, 5, 10, 20, 11, 23, 3
    vector<int> preorder = {1, 2, 4, 5, 10, 20, 11, 23, 3};

    // Test inorder preorder postorder with match.
    for (int i = 0; i < 10; i++) {
        BinaryTree<int> tree = create_dummy<int>(i);

        CHECK(isEqual(tree, inorder, _order::inorder));

        CHECK(isEqual(tree, preorder, _order::preorder));

        CHECK(isEqual(tree, postorder, _order::postorder));

        transform(inorder.begin(), inorder.end(), inorder.begin(), [](int val) { return val + 1; });
        transform(preorder.begin(), preorder.end(), preorder.begin(), [](int val) { return val + 1; });
        transform(postorder.begin(), postorder.end(), postorder.begin(), [](int val) { return val + 1; });
    }
}

TEST_CASE("TEST binary transofmations") {
    // create the following tree on i = 0
    //                    1
    //              2          3
    //         4        5
    //               10   11
    //             20       23

    auto f = [](int val, int add) {
        return val + add;
    };

    // Test inorder preorder postorder with match.
    for (int i = 1; i < 15; i++) {
        // inorder : 4, 10, 5, 11, 2, 1, 3
        vector<int> inorder = {4, 10, 5, 11, 2, 1, 3};
        //postorder : 4, 20, 10, 23, 11, 5, 2, 3, 1
        vector<int> postorder = {4, 20, 10, 23, 11, 5, 2, 3, 1};
        //preorder : 1, 2, 4, 5, 10, 20, 11, 23, 3
        vector<int> preorder = {1, 2, 4, 5, 10, 20, 11, 23, 3};

        int val = NextInt();
        BinaryTree<int> tree = create_dummy<int>();

        auto f2 = std::bind(f, placeholders::_1, val);
        transform(tree.begin(), tree.end(), tree.begin(), f2);

        transform(inorder.begin(), inorder.end(), inorder.begin(), f2);
        transform(preorder.begin(), preorder.end(), preorder.begin(), f2);
        transform(postorder.begin(), postorder.end(), postorder.begin(), f2);

        CHECK(isEqual(tree, inorder, _order::inorder));
        CHECK(isEqual(tree, preorder, _order::preorder));
        CHECK(isEqual(tree, postorder, _order::postorder));
    }
}

TEST_CASE("Test random permutation") {
    const int tsize = 50;
    vector<double> randomVals(tsize);
    auto random_unique_double = []() {
        static double n = 1;
        double v = (double)((unsigned int)rand() % 100) / 100;
        n++;
        return n + v;
    };

    auto print = [](double n) { cout << ", " << n; };
    // for_each(randomVals.begin(), randomVals.end(), print);

    for (int i = 0; i < 5; i++) {
        generate(randomVals.begin(), randomVals.end(), random_unique_double);
        // for_each(randomVals.begin(), randomVals.end(), print);

        // transform(begin(v1), end(v1), begin(v2), back_inserter(v3),
        BinaryTree<double> tree;
        tree.add_root(randomVals[0]);

        // generate random tree, but with values that in the vector we created
        // this new tree inorder, postorder and preorder should be a permutation of the vector!
        for (unsigned int i = 1; i < randomVals.size(); i++) {
            if (RandomBool()) {
                tree.add_left(randomVals[i - 1], randomVals[i]);
            } else {
                tree.add_right(randomVals[i - 1], randomVals[i]);
            }
        }

        vector<double> copied(tsize);
        unsigned int j = 0;
        for (auto it = tree.begin_preorder(); it != tree.end_preorder(); ++it, j++) {
            copied[j] = *it;
        } // prints: 1 2 4 5 3
        CHECK(is_permutation(copied.begin(), copied.end(), randomVals.begin(), randomVals.end()));

        j = 0;
        for (auto it = tree.begin_inorder(); it != tree.end_inorder(); ++it, j++) {
            copied[j] = *it;
        } // prints: 4 2 5 1 3
        CHECK(is_permutation(copied.begin(), copied.end(), randomVals.begin(), randomVals.end()));

        j = 0;
        for (auto it = tree.begin_postorder(); it != tree.end_postorder(); ++it, j++) {
            copied[j] = *it;
        } // prints: 4 5 2 3 1
        CHECK(is_permutation(copied.begin(), copied.end(), randomVals.begin(), randomVals.end()));
    }
}

class myString {
public:
    string val;
    myString(int a) {
        val = std::to_string(a);
    }

    myString &operator+(const myString &other) {
        val += other.val;
        return *this;
    }

    myString &operator+(double other) {
        val += to_string(other);
        return *this;
    }

    bool operator==(const myString &other) {
        return this->val == other.val;
    }

    friend std::ostream &operator<<(std::ostream &os, const myString &c) {
        return (os << c.val);
    }
};

TEST_CASE("test castume class") {
    srand(time(nullptr));
    // create the following tree on i = 0
    //                    1
    //              2          3
    //         4        5
    //               10   11
    //             20       23

    // inorder : 4, 10, 5, 11, 2, 1, 3
    vector<myString> inorder = {4, 10, 5, 11, 2, 1, 3};
    //postorder : 4, 20, 10, 23, 11, 5, 2, 3, 1
    vector<myString> postorder = {4, 20, 10, 23, 11, 5, 2, 3, 1};
    //preorder : 1, 2, 4, 5, 10, 20, 11, 23, 3
    vector<myString> preorder = {1, 2, 4, 5, 10, 20, 11, 23, 3};

    // auto print = [](myString n) { cout << ", " << n; };
    // for_each(preorder.begin(), preorder.end(), print);

    // Test inorder preorder postorder with match.
    for (int i = 0; i < 10; i++) {
        BinaryTree<myString> tree = create_dummy<myString>(i);

        CHECK(isEqual(tree, inorder, _order::inorder));

        CHECK(isEqual(tree, preorder, _order::preorder));

        CHECK(isEqual(tree, postorder, _order::postorder));

        transform(inorder.begin(), inorder.end(), inorder.begin(), [](myString val) { return val + 1; });
        transform(preorder.begin(), preorder.end(), preorder.begin(), [](myString val) { return val + 1; });
        transform(postorder.begin(), postorder.end(), postorder.begin(), [](myString val) { return val + 1; });
    }
}

TEST_CASE("throws") {

    const int max_val = 20;
    BinaryTree<myString> tree;

    CHECK_THROWS(tree.add_left(0, 5));
    CHECK_THROWS(tree.add_left(0, 10));

    for (int j = 0; j < 30; j++) {
        BinaryTree<myString> tree2;
        tree2.add_root(0);
        for (int i = 2; i < max_val; i += 2) {
            if (RandomBool()) {
                tree2.add_left(i - 2, i);
            } else {
                tree2.add_right(i - 2, i);
            }
        }

        int val = (unsigned int)rand() % max_val;
        if (val % 2 == 0) {
            CHECK_NOTHROW(tree2.add_left(val, 1));
        } else {
            CHECK_THROWS(tree2.add_right(val, 1));
        }
    }
}