#ifndef BINARYTREE
#define BINARYTREE

#include "BinaryNode.hpp"
#include <vector>
#include <iostream>
#include <list>
#include <cstddef>
#include <queue>

template <typename T>
class BinaryTree {
    public:

        BinaryTree();
        BinaryTree(const BinaryTree& other);
        ~BinaryTree();

        void makeFromInorderPreorder(std::list<T>& inorder, std::list<T>& preorder);

        void makeFromInorderPostorder(std::list<T>& inorder, std::list<T>& preorder);

        void bfs(void (*fun)(const T& value), BinaryNode<T>* node = NULL);
        void dfs(void (*fun)(const T& value), BinaryNode<T>* node = NULL);

        T& getRootValue();

        bool isEmpty();
        int getSize();
        int getHeight();

        void makeSubTreeFromNode(const T& value, BinaryTree<T>& dest);
        void makeSubTreeFromNode(const BinaryNode<T>* node, BinaryTree<T>& dest);
        void makeSubTreeFromLeft(BinaryTree<T>& dest);
        void makeSubTreeFromRight(BinaryTree<T>& dest);
        
        std::vector<BinaryNode<T>*> getLeaves();
        std::vector<BinaryNode<T>*> getGrandsons(BinaryNode<T>* node);

        void clear();

        bool operator==(const BinaryTree<T>& other);
        bool operator!=(const BinaryTree<T>& other);
        BinaryTree& operator=(const BinaryTree<T>& other);

        template <typename S>
        friend std::ostream& operator<<(std::ostream& os, const BinaryTree<S>& binaryTree);

        template <typename S>
        friend std::istream& operator>>(std::istream& is, BinaryTree<S>& binaryTree);

    protected:
        BinaryNode<T>* root;
        int size;
        int height;

        BinaryNode<T>* getNode(const T& value);

        BinaryNode<T>* makeFromInorderPostorder(std::vector<T>& inorder, std::list<T>& preorder, int min, int max, int height);

        BinaryNode<T>* makeFromInorderPreorder(std::vector<T>& inorder, std::list<T>& preorder, int min, int max, int height);

};

namespace BinaryTreeUtils {
    
    template <typename T>
    int indexOf(const T& value, const std::vector<T>& v);

    template <typename T>
    bool isAllNull(std::queue<T>& q);
}


#include "BinaryTree.cpp"

#endif