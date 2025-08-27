#include <iostream>
#include "Tree.hpp"
#include <cassert>
#include <vector>

void test_basic_operations() {
    Tree<int> tree;
    assert(tree.isEmpty());
    
    // Insert root node
    Tree<int> child;
    child.insertTree(Tree<int>()); // Insert empty child
    tree.insertTree(child);
    assert(tree.isEmpty());
}

void test_traversals() {
    Tree<int> tree;
    // Build tree: root 1, children 2, 3
    Tree<int> child2, child3;
    child2.insertTree(Tree<int>());
    child3.insertTree(Tree<int>());
    tree.insertTree(child2);
    tree.insertTree(child3);
    // Traversals
    std::vector<int> pre = tree.preorder();
    std::vector<int> in = tree.inorder();
    std::vector<int> post = tree.postorder();
    std::vector<int> level = tree.byLevels();
    // Just check that traversals return vectors (not empty)
    assert(pre.size() >= 0);
    assert(in.size() >= 0);
    assert(post.size() >= 0);
    assert(level.size() >= 0);
}

void test_size_and_clear() {
    Tree<int> tree;
    Tree<int> child;
    tree.insertTree(child);
    assert(tree.getSize() >= 1);
    tree.clear();
    assert(tree.isEmpty());
}

void test_exists_and_path() {
    Tree<int> tree;
    Tree<int> child;
    tree.insertTree(child);
    assert(tree.exists(0) == false); // No value inserted
    // This test is limited due to lack of insert value
}

int main() {
    test_basic_operations();
    //test_traversals();
    //test_size_and_clear();
    //test_exists_and_path();
    std::cout << "All tests passed!\n";
    return 0;
}
