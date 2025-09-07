#ifndef BINARYTREE
#define BINARYTREE

#include "BinaryNode.hpp"
#include <vector>
#include <iostream>
#include <list>
#include <cstddef>
#include <queue>
#include <unordered_map>
#include <BinaryNodeMetaData.hpp>

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

        std::list<T> pathTo(const T& value);
        T parentOf(const T& value);
        T grandParentOf(const T& value);
        std::vector<T> cousinsOf(const T& value);
        T siblingOf(const T& value);
        T leftChildOf(const T& value);
        T rightChildOf(const T& value);
        int levelOf(const T& value);

        bool haveParent(const T& value);
        bool haveGrandParent(const T& value);

        std::list<T> level(int index);
        std::list<std::list<T> > allLevels();

        bool isomorphic(const BinaryTree<T>& other);
        T lowestCommonAncestor(const T& value1, const T& value2);
        BinaryTree<T> mirror();

        bool operator==(const BinaryTree<T>& other);
        bool operator!=(const BinaryTree<T>& other);
        BinaryTree& operator=(const BinaryTree<T>& other);

        template <typename S>
        friend std::ostream& operator<<(std::ostream& os, BinaryTree<S>& binaryTree);

        template <typename S>
        friend std::istream& operator>>(std::istream& is, BinaryTree<S>& binaryTree);

    protected:
        BinaryNode<T>* root;
        int size;

        BinaryNode<T>* makeFromInorderPostorder(
            std::vector<T>& inorder, std::list<T>& postorder, int min, int max, int height, std::unordered_map<T, int>& inorderMap
        );
        BinaryNode<T>* makeFromInorderPreorder(
            std::vector<T>& inorder, std::list<T>& preorder, int min, int max, int height,std::unordered_map<T, int>& inorderMap
        );

        BinaryNodeMetaData<T>& getBinaryNodeMetaData(const T& value);
        void getBinaryNodeMetaData(
            const T& value, 
            BinaryNodeMetaData<T>& metaData,
            bool& isFound,
            BinaryNode<T>* ptr,
            BinaryNode<T>* parent = NULL,
            BinaryNode<T>* grandParent = NULL,
            int level = 0
        );

        void leaves(BinaryNode<T>* node, std::list<T>& result);

        void preorder(BinaryNode<T>* node, std::vector<T>& result);
        void inorder(BinaryNode<T>* node, std::vector<T>& result);
        void postorder(BinaryNode<T>* node, std::vector<T>& result);

        BinaryNode<T>* mirror(BinaryNode<T>* ptr);

        void getPathTo(const T& value, BinaryNode<T>* ptr, std::list<T>& path, bool& isFound);

        bool isomorphic(BinaryNode<T>* ptr, BinaryNode<T>* ptrOther);

        void makeTreeFromMap(BinaryNode<T>* parent, std::list<T>& children, std::unordered_map<T, std::list<T> >& nodes);

        void height(BinaryNode<T>* ptr, int& maxDepth, int depth = -1);

        void copyNodes(BinaryNode<T>* source, BinaryNode<T>*& destination, int& size);
        void destroyNodes(BinaryNode<T>* ptr, int& size);
};

namespace BinaryTreeUtils {
    
    template <typename T>
    bool isAllNull(std::queue<T>& q);

    template <typename T>
    std::unordered_map<T, int> mapVector(const std::vector<T>& v);
}

#include "BinaryTree.cpp"

#endif
