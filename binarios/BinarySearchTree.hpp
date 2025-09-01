#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE
#include "BinaryTree.hpp"

template <typename T>
class BinarySearchTree : public BinaryTree<T> {

    public:

        void insert(T value);

        bool contains(T value);

        void remove(T value);
};

#include "BinarySearchTree.cpp"

#endif
