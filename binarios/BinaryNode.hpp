#ifndef BINARY_NODE
#define BINARY_NODE
#include <cstddef>

template <typename T>
class BinaryNode {

    public:
        BinaryNode(
            T value,
            BinaryNode* left = NULL,
            BinaryNode* right = NULL
        ) : 
            value(value), 
            left(left), 
            right(right) 
        {}

        BinaryNode(const BinaryNode& other) : 
            value(other.value), 
            left(other.left ? new BinaryNode(*other.left) : NULL), 
            right(other.right ? new BinaryNode(*other.right) : NULL) 
        {}

        ~BinaryNode() {
            if (left != NULL) delete left;
            if (right != NULL) delete right;
        }

        T getValue() {return value;};
        void setValue(T value) {this->value = value;}

        BinaryNode* getLeft() {return left;};
        void setLeft(BinaryNode* left) {this->left = left;}

        BinaryNode* getRight() {return right;};
        void setRight(BinaryNode* right) {this->right = right;}

        bool isLeaf() {return left == NULL && right == NULL;}

    private:
        T value;
        BinaryNode* left;
        BinaryNode* right;
};

#endif