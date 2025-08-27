#include "BinaryTree.hpp"
#include <queue>
#include <cstddef>
#include <list>
#include <queue>
#include <cmath>

template <typename T>
BinaryTree<T>::BinaryTree() 
: 
    root(NULL), 
    size(0), 
    height(-1)  
{}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& other) : 
    root(NULL), 
    size(0), 
    height(0) 
{

    BinaryNode<T>* current = other.root;

    while (current != NULL) {
        current = current->getLeft();
    }

}

template <typename T>
BinaryTree<T>::~BinaryTree() {
    if (root != NULL) delete root;
}

template <typename T>
void BinaryTree<T>::makeFromInorderPreorder(std::list<T>& inorder, std::list<T>& preorder) {
    this->clear();
    std::vector<T> inorderL(inorder.begin(), inorder.end());
    root = makeFromInorderPreorder(inorderL, preorder, 0, inorder.size() - 1, 0);
}

template <typename T>
BinaryNode<T>* BinaryTree<T>::makeFromInorderPreorder(std::vector<T>& inorder, std::list<T>& preorder, int min, int max, int height) {
    if (min > max || preorder.empty()) return NULL;
    size++;
    if (height > this->height) this->height = height;

    BinaryNode<T>* newNode = new BinaryNode<T>(preorder.front());
    preorder.pop_front();

    int inorderIndex = BinaryTreeUtils::indexOf(newNode->getValue(), inorder);

    newNode->setLeft(makeFromInorderPreorder(inorder, preorder, min, inorderIndex - 1, height + 1));

    newNode->setRight(makeFromInorderPreorder(inorder, preorder, inorderIndex + 1, max, height + 1));

    return newNode;
}

template <typename T>
void BinaryTree<T>::makeFromInorderPostorder(std::list<T>& inorder, std::list<T>& postorder) {
    this->clear();
    std::vector<T> inorderL(inorder.begin(), inorder.end());

    root = makeFromInorderPostorder(inorderL, postorder, 0, inorder.size() - 1, 0);
}

template <typename T>
BinaryNode<T>* BinaryTree<T>::makeFromInorderPostorder(std::vector<T>& inorder, std::list<T>& postorder, int min, int max, int height) {
    if (min > max || postorder.empty()) return NULL;

    size++;
    if (height > this->height) this->height = height;

    BinaryNode<T>* newNode = new BinaryNode<T>(postorder.back());
    postorder.pop_back();

    int inorderIndex = BinaryTreeUtils::indexOf(newNode->getValue(), inorder);

    newNode->setRight(makeFromInorderPostorder(inorder, postorder, inorderIndex + 1, max, height + 1));

    newNode->setLeft(makeFromInorderPostorder(inorder, postorder, min, inorderIndex - 1, height + 1));

    return newNode;

}

template <typename T>
void BinaryTree<T>::bfs(void (*fun)(const T& value), BinaryNode<T>* node) {
    if (root == NULL) return;

    std::queue<BinaryNode<T>*> queue;
    queue.push(root);

    while (!queue.empty()) {
        BinaryNode<T>* current = queue.front();
        queue.pop();
        fun(current->getValue());

        if (current->getLeft() != NULL) {
            queue.push(current->getLeft());
        }
        if (current->getRight() != NULL) {
            queue.push(current->getRight());
        }
    }
}

template <typename T>
void BinaryTree<T>::dfs(void (*fun)(const T& value), BinaryNode<T>* node) {
    if (node == NULL) return;

    fun(node->getValue());
    dfs(fun, node->getLeft());
    dfs(fun, node->getRight());
}

template <typename T>
T& BinaryTree<T>::getRootValue() {
    if (root == NULL) throw std::runtime_error("Tree is empty");
    return root->getValue();
}

template <typename T>
bool BinaryTree<T>::isEmpty() {
    return size == 0;
}

template <typename T>
int BinaryTree<T>::getSize() {
    return size;
}

template <typename T>
int BinaryTree<T>::getHeight() {
    return height;
}

template <typename T>
void BinaryTree<T>::makeSubTreeFromNode(const T& value, BinaryTree<T>& dest) {
    dest.clear();

    BinaryNode<T>* node = getNode(value);

    if (node == NULL) return;

    makeSubTreeFromNode(node, dest);
}

template <typename T>
void BinaryTree<T>::makeSubTreeFromNode(const BinaryNode<T>* node, BinaryTree<T>& dest) {
    dest.clear();

    if (node == NULL) return;

    dest.root = new BinaryNode<T>(*node);

    std::queue<BinaryNode<T>*> queue;
    queue.push(dest.root);

    while (!queue.empty()) {

        int size = queue.size();

        for (int i = 0; i < size; i++) {
            if (queue.front() == NULL) {
                queue.pop();
                continue;
            }
            queue.push(queue.front()->getLeft());
            queue.push(queue.front()->getRight());
            queue.pop();
            dest.size++;
        }
        dest.height++;
    }
}

template <typename T>
void BinaryTree<T>::makeSubTreeFromLeft(BinaryTree<T>& dest) {
    dest.clear();
    if (root == NULL || root->getLeft() == NULL) return;

    makeSubTreeFromNode(root->getLeft()->getValue(), dest);
}

template <typename T>
void BinaryTree<T>::makeSubTreeFromRight(BinaryTree<T>& dest) {
    dest.clear();
    if (root == NULL || root->getRight() == NULL) return;

    makeSubTreeFromNode(root->getRight()->getValue(), dest);
}

template <typename T>
void BinaryTree<T>::clear() {
    size = 0;
    height = -1;
    if (root) delete root;
    root = NULL;
}

template <typename T>
bool BinaryTree<T>::operator==(const BinaryTree<T>& other) {
    if (this == &other) return true;

    if (size != other.size) return false;

    if (height != other.height) return false;

    bool isEqual = true;
    std::queue<BinaryNode<T>*> queue1;
    std::queue<BinaryNode<T>*> queue2;

    queue1.push(root);
    queue2.push(other.root);

    while (!queue1.empty() && !queue2.empty() && isEqual) {

        BinaryNode<T>* node1 = queue1.front();
        BinaryNode<T>* node2 = queue2.front();
        queue1.pop();
        queue2.pop();

        if (node1 == NULL && node2 == NULL) continue;

        if (node1 == NULL || node2 == NULL) {
            isEqual = false;
        }else if (node1->getValue() != node2->getValue()) {
            isEqual = false;
        }else {
            queue1.push(node1->getLeft());
            queue1.push(node1->getRight());
    
            queue2.push(node2->getLeft());
            queue2.push(node2->getRight());
        }
    }
    return isEqual;
}

template <typename T>
bool BinaryTree<T>::operator!=(const BinaryTree<T>& other) {
    return !(*this == other);
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other) {
    if (this != &other) {
        this->clear();
        if (other.root != NULL) {
            this->root = new BinaryNode<T>(*other.root);
            this->size = other.size;
            this->height = other.height;
        }
    }
    return *this;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const BinaryTree<T>& binaryTree){

    std::queue<BinaryNode<T>*> q;

    q.push(binaryTree.root);

    int level = 0;
    do {

        for (int i = 0; i < binaryTree.height*10/ pow(2, level); i++) {
            os << " ";
        }

        int size = q.size();

        for (int i = 0; i < size; i++) {
            
            if (q.front() == NULL) { 
                for (int i = 0; i < binaryTree.height*10/pow(2, level)*2; i++) {
                    os << " ";
                }
                q.push(NULL);
                q.push(NULL);
                q.pop();
                continue;
            }

            q.push(q.front()->getLeft());
            q.push(q.front()->getRight());

            os << q.front()->getValue();
            for (int i = 0; i < binaryTree.height*10/pow(2, level)*2; i++) {
                os << " ";
            }
            q.pop();
        }
        
        os << "\n";
        level++;
    } while (!BinaryTreeUtils::isAllNull(q));
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, BinaryTree<T>& binaryTree) {
    std::string type1;
    std::string type2;

    std::list<T> traverse1;
    std::list<T> traverse2;

    is >> type1;
    while (is.get() == ' ') {
        T temp;
        is >> temp;
        traverse1.push_back(temp);
    }

    is >> type2;
    while (is.get() == ' ' && !is.eof()) {
        T temp;
        is >> temp;
        traverse2.push_back(temp);
    }

    if (type1 == "INORDEN") {
        if (type2 == "PREORDEN") {
            binaryTree.makeFromInorderPreorder(traverse1, traverse2);
        } else {
            binaryTree.makeFromInorderPostorder(traverse1, traverse2);
        }
    } else if (type2 == "INORDEN") {
        if (type1 == "PREORDEN") {
            binaryTree.makeFromInorderPreorder(traverse2, traverse1);
        } else {
            binaryTree.makeFromInorderPostorder(traverse2, traverse1);
        }
    }

    return is;
}

template <typename T>
int BinaryTreeUtils::indexOf(const T& value, const std::vector<T>& v) {
    int size = v.size();
    for (int i = 0; i < size; i++) {
        if (value == v[i]) return i;
    }
    return -1;
}

template <typename T>
bool BinaryTreeUtils::isAllNull(std::queue<T>& q) {
    int size = q.size();
    bool res = true;
    for (int i = 0; i < size; i++) {
        if (q.front() != NULL) res = false;
        q.push(q.front());
        q.pop();
    }
    return res;
}

template <typename T>
BinaryNode<T>* BinaryTree<T>::getNode(const T& value) {
    if (root == NULL) return NULL;

    std::queue<BinaryNode<T>*> queue;
    queue.push(root);

    while (!queue.empty()) {
        BinaryNode<T>* current = queue.front();
        queue.pop();

        if (current->getValue() == value) {
            return current;
        }

        if (current->getLeft() != NULL) {
            queue.push(current->getLeft());
        }
        if (current->getRight() != NULL) {
            queue.push(current->getRight());
        }
    }

    return NULL;
}