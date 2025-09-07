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

        T getValue() {return value;};
        void setValue(T value) {this->value = value;}

        BinaryNode* getLeft() {return left;};
        void setLeft(BinaryNode* left) {this->left = left;}

        BinaryNode* getRight() {return right;};
        void setRight(BinaryNode* right) {this->right = right;}

    private:
        T value;
        BinaryNode* left;
        BinaryNode* right;
};

#endif
