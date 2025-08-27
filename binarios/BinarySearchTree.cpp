#include "BinarySearchTree.hpp"
#include "BinaryNode.hpp"
#include <cstddef>

template <typename T>
void BinarySearchTree<T>::insert(T value) {

    BinaryNode<T>* newNode = new BinaryNode<T>(value);

    if (this->root == NULL) {
        this->root = newNode;
        this->size++;
        this->height = 0;
        return;
    }

    BinaryNode<T>* current = this->root;
    int newHeight = 0;

    while (true) {
        newHeight++;
        if (value < current->getValue()) {
            if (current->getLeft() != NULL) {
                current = current->getLeft();
            } else {
                current->setLeft(newNode);
                break;
            }
        } else {
            if (current->getRight() != NULL) {
                current = current->getRight();
            } else {
                current->setRight(newNode);
                break;
            }
        }
    }
    this->height = (this->height < newHeight) ? newHeight : this->height;
    this->size++;
}

template <typename T>
bool BinarySearchTree<T>::contains(T value) {

    BinaryNode<T>* current = this->root;

    while (current != NULL) {
        if (value == current->getValue()) {
            return true;
        } else if (value < current->getValue()) {
            current = current->getLeft();
        } else {
            current = current->getLeft();
        }
    }
    return false;
}

