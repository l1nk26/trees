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
        void makeFromInorderPostorder(std::list<T>& inorder, std::list<T>& postorder);

        bool isEmpty();
        T& rootValue();
        int getSize();
        int height();
        void clear();

        BinaryTree<T> leftChild();
        BinaryTree<T> rightChild();

        std::vector<T> preorder();
        std::vector<T> inorder();
        std::vector<T> postorder();
        std::vector<T> byLevels();
        
        std::list<T> leaves();

        bool exists(const T& value);

        T lowestCommonAncestor(const T& value1, const T& value2);
        BinaryTree<T> mirror();

        std::list<T> pathTo(const T& value);
        T parentOf(const T& value);
        T grandParentOf(const T& value);
        std::list<T> cousinsOf(const T& value);
        std::list<T> siblingsOf(const T& value);
        T leftChilddOf(const T& value);
        T rightChilddOf(const T& value);
        int levelOf(const T& value);

        bool haveParent(const T& value);
        bool haveGrandParent(const T& value);

        std::list<T> level(int index);
        std::list<std::list<T> > allLevels();

        bool isomorphic(const BinaryTree<T>& other);

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

        BinaryNode<T>* makeFromInorderPostorder(std::vector<T>& inorder, std::list<T>& postorder, int min, int max, int height);
        BinaryNode<T>* makeFromInorderPreorder(std::vector<T>& inorder, std::list<T>& preorder, int min, int max, int height);

        BinaryTreeNodeMetaData<T>& getBinaryTreeNodeMetaData(const T& value);
        void getBinaryTreeNodeMetaData(
            const T& value, 
            BinaryTreeNodeMetaData<T>& metaData,
            bool& isFound,
            BinaryTreeNode<T>* ptr,
            BinaryTreeNode<T>* parent = NULL,
            BinaryTreeNode<T>* grandParent = NULL,
            int level = 0
        );

        void leaves(BinaryTreeNode<T>* node, std::list<T>& result);

        void preorder(BinaryTreeNode<T>* node, std::vector<T>& result);
        void inorder(BinaryTreeNode<T>* node, std::vector<T>& result);
        void postorder(BinaryTreeNode<T>* node, std::vetor<T>& result);

        BinaryTreeNode<T>* mirror(BinaryTreeNode<T>* ptr);

        void getPathTo(const T& value, BinaryTreeNode<T>* ptr, std::list<T>& path, bool& isFound);

        bool isomorphic(BinaryTreeNode<T>* ptr, BinaryTreeNode<T>* ptrOther);

        void makeTreeFromMap(BinaryTreeNode<T>* parent, std::list<T>& children, std::unordered_map<T, std::list<T> >& nodes);

        void height(BinaryTreeNode<T>* ptr, int depth, int& maxDepth);

        void copyNodes(BinaryTreeNode<T>* source, BinaryTreeNode<T>*& destination, int& size);
        void destroyNodes(BinaryTreeNode<T>* ptr, int& size);
};

namespace BinaryTreeUtils {
    
    template <typename T>
    bool isAllNull(std::queue<T>& q);

    template <typename T>
    unordered_map<T> mapVector(const std::vector<T>& v);
}

#include "BinaryTree.cpp"

#endif
