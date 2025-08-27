#ifndef TREENODE
#define TREENODE
#include <cstddef>

template <typename T>
class TreeNode {
    public:

        TreeNode() : 
            leftChild(NULL),
            rightSibling(NULL)
        {}

        TreeNode(const T& value) : 
            value(value), 
            leftChild(NULL), 
            rightSibling(NULL) 
        {}

        T& getValue() { return value; }

        TreeNode<T>* getLeftChild() { return leftChild; }

        TreeNode<T>* getRightSibling() { return rightSibling; }

        void setValue(const T& value) { this->value = value; }

        void setLeftChild(TreeNode<T>* child) { leftChild = child; }

        void setRightSibling(TreeNode<T>* sibling) { rightSibling = sibling; }

        template <typename U>
        friend std::ostream& operator<<(std::ostream& os, const TreeNode<U>& node);

    private:
        T value;
        TreeNode<T>* leftChild;
        TreeNode<T>* rightSibling;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const TreeNode<T>& node) {
    os << "value: " <<  node.value << ", ";

    os << ", children: ";
    TreeNode<T>* current = node.leftChild;
    while (current != NULL) {
        os << current->value << " ";
        current = current->rightSibling;
    }

    return os;
}

#endif