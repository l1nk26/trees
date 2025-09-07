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
    size(0) 
{}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& other) : 
    root(NULL), 
    size(0) 
{
    copyNodes(other.root, root, size);
}

template <typename T>
BinaryTree<T>::~BinaryTree() {
    int aux = 0;
    destroyNodes(root, aux);
}

template <typename T>
void BinaryTree<T>::makeFromInorderPreorder(std::list<T>& inorder, std::list<T>& preorder) {
    this->clear();
    std::vector<T> inorderV(inorder.begin(), inorder.end());
    std::unordered_map<T, int> inorderMap = BinaryTreeUtils::mapVector(inorderV);
    root = makeFromInorderPreorder(inorderV, preorder, 0, inorder.size() - 1, 0, inorderMap);
}

template <typename T>
BinaryNode<T>* BinaryTree<T>::makeFromInorderPreorder(
    std::vector<T>& inorder, 
    std::list<T>& preorder, 
    int min, int max, int height, 
    std::unordered_map<T, int>& inorderMap
) {

    if (min > max || preorder.empty()) return NULL;
    ++size;

    BinaryNode<T>* newNode = new BinaryNode<T>(preorder.front());
    preorder.pop_front();

    int inorderIndex = inorderMap[newNode->getValue()];

    newNode->setLeft(makeFromInorderPreorder(inorder, preorder, min, inorderIndex - 1, height + 1, inorderMap));

    newNode->setRight(makeFromInorderPreorder(inorder, preorder, inorderIndex + 1, max, height + 1, inorderMap));

    return newNode;
}

template <typename T>
void BinaryTree<T>::makeFromInorderPostorder(std::list<T>& inorder, std::list<T>& postorder) {
    this->clear();
    std::vector<T> inorderV(inorder.begin(), inorder.end());
    std::unordered_map<T, int> inorderMap = BinaryTreeUtils::mapVector(inorderV);

    root = makeFromInorderPostorder(inorderV, postorder, 0, inorder.size() - 1, 0, inorderMap);
}

template <typename T>
BinaryNode<T>* BinaryTree<T>::makeFromInorderPostorder(
    std::vector<T>& inorder, 
    std::list<T>& postorder, 
    int min, int max, int height,
    std::unordered_map<T, int>& inorderMap
    ) {
    if (min > max || postorder.empty()) return NULL;
    ++size;

    BinaryNode<T>* newNode = new BinaryNode<T>(postorder.back());
    postorder.pop_back();

    int inorderIndex = inorderMap[newNode->getValue()];

    newNode->setRight(makeFromInorderPostorder(inorder, postorder, inorderIndex + 1, max, height + 1, inorderMap));

    newNode->setLeft(makeFromInorderPostorder(inorder, postorder, min, inorderIndex - 1, height + 1, inorderMap));

    return newNode;
}

template <typename T>
T& BinaryTree<T>::rootValue() {
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
int BinaryTree<T>::height() {
    int maxDepth = -1;
    height(root, maxDepth);
    return maxDepth;
}

template <typename T>
BinaryTree<T> BinaryTree<T>::leftChild() {
    BinaryTree<T> tree;

    if (root != NULL) {
        copyNodes(root->getLeft(), tree.root, tree.size);
    }

    return tree;
}

template <typename T>
BinaryTree<T> BinaryTree<T>::rightChild() {

    BinaryTree<T> tree; 
    if (root != NULL) {
        copyNodes(root->getRight(), tree.root, tree.size);
    }
    return tree;
}

template <typename T>
void BinaryTree<T>::clear() {
    size = 0;
    int aux = 0;
    destroyNodes(root, aux);
    root = NULL;
}

template <typename T>
bool BinaryTree<T>::exists(const T& value) {
    BinaryNodeMetaData<T>& metaData = getBinaryNodeMetaData(value);

    return metaData.getNode() != NULL;
}

template <typename T>
std::list<T> BinaryTree<T>::pathTo(const T& value) {

    BinaryNodeMetaData<T>& metaData = getBinaryNodeMetaData(value);
    std::list<T> result = metaData.getPathFromRoot();
    return result;
}

template <typename T>
T BinaryTree<T>::parentOf(const T& value) {

    BinaryNodeMetaData<T>& metaData = getBinaryNodeMetaData(value);
    if (metaData.getParent() != NULL) {
        throw std::runtime_error("No parent");
    }
    return metaData.getParent()->getValue();
}

template <typename T>
T BinaryTree<T>::grandParentOf(const T& value) {

    BinaryNodeMetaData<T>& metaData = getBinaryNodeMetaData(value);

    if (metaData.getGrandParent() != NULL) {
        throw std::runtime_error("No grand parent");
    }
    return metaData.getGrandParent()->getValue();
}

template <typename T>
std::vector<T> BinaryTree<T>::cousinsOf(const T& value) {

    BinaryNodeMetaData<T>& metaData = getBinaryNodeMetaData(value);
    std::vector<T> result;
    result.reserve(4);

    if (metaData.getGrandParent() != NULL) {
        
        BinaryNode<T>* left = metaData.getGrandParent()->getLeft();
        BinaryNode<T>* right = metaData.getGrandParent()->getRight();

        if (left != NULL) {
            if (left->getLeft() != NULL) {
                result.push_back(left->getLeft()->getValue());
            }
            if (left->getRight() != NULL) {
                result.push_back(left->getRight()->getValue());
            }
        }
        if (right != NULL) {
            if (right->getLeft() != NULL) {
                result.push_back(right->getLeft()->getValue());
            }
            if (right->getRight() != NULL) {
                result.push_back(right->getRight()->getValue());
            }
        }

    }

    return result;
}

template <typename T>
T BinaryTree<T>::siblingOf(const T& value) {

    BinaryNodeMetaData<T>& metaData = getBinaryNodeMetaData(value);
    BinaryNode<T>* parent = metaData.getParent();
    BinaryNode<T>* sibling;

    if (parent == NULL || parent->getLeft() != NULL || parent->getRight() != NULL) {
        throw std::runtime_error("no sibling");
    }
    
    if (parent->getLeft()->getValue() == value) {
        sibling = parent->getRight();
    } else {
        sibling = parent->getLeft();
    }

    return sibling->getValue(); 
}

template <typename T>
T BinaryTree<T>::leftChildOf(const T& value) {

    BinaryNodeMetaData<T>& metaData = getBinaryNodeMetaData(value);

    if (metaData.getNode() == NULL || metaData.getNode()->getLeft() == NULL) {
        throw std::runtime_error("No left child");
    }
    return metaData.getLeft()->getValue();
}

template <typename T>
T BinaryTree<T>::rightChildOf(const T& value) {

    BinaryNodeMetaData<T>& metaData = getBinaryNodeMetaData(value);

    if (metaData.getNode() == NULL || metaData.getNode()->getRight() == NULL) {
        throw std::runtime_error("No left child");
    }
    return metaData.getRight()->getValue();
}

template <typename T>
int BinaryTree<T>::levelOf(const T& value) {

    BinaryNodeMetaData<T>& metaData = getBinaryNodeMetaData(value);

    return metaData.getLevel();
}


template <typename T>
bool BinaryTree<T>::haveParent(const T& value) {

    BinaryNodeMetaData<T>& metaData = getBinaryNodeMetaData(value);

    return metaData.getParent() != NULL;
}

template <typename T>
bool BinaryTree<T>::haveGrandParent(const T& value) {

    BinaryNodeMetaData<T>& metaData = getBinaryNodeMetaData(value);

    return metaData.getGrandParent() != NULL;
}

template <typename T>
bool BinaryTree<T>::operator==(const BinaryTree<T>& other) {
    if (this == &other) return true;

    if (size != other.size) return false;

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

        if (node1 == NULL || node2 == NULL) {
            isEqual = node1 == node2;
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
        copyNodes(other.root, root, size);
    }
    return *this;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const BinaryTree<T>& binaryTree){

    std::queue<BinaryNode<T>*> q;

    q.push(binaryTree.root);
    int height = binaryTree.height();

    int level = 0;
    do {

        for (int i = 0; i < height*10/ pow(2, level); i++) {
            os << " ";
        }

        int size = q.size();

        for (int i = 0; i < size; i++) {
            
            if (q.front() == NULL) { 
                for (int i = 0; i < height*10/pow(2, level)*2; i++) {
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
            for (int i = 0; i < height*10/pow(2, level)*2; i++) {
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
BinaryNodeMetaData<T>& BinaryTree<T>::getBinaryNodeMetaData(const T& value) {
    
    static std::unordered_map<T, BinaryNodeMetaData<T> > cacheNodes;
    static BinaryNodeMetaData<T> empty;
    bool isFound = false;

    if (cacheNodes.find(value) == cacheNodes.end()) {
        cacheNodes[value]; // construye la metadata del nodo
        getBinaryNodeMetaData(value, cacheNodes[value], isFound, root);
        if (!isFound) {
            cacheNodes.erase(value); 
        } else {
            BinaryNode<T>* left = cacheNodes[value].getNode()->getLeftChild();

            if (left != NULL) {
                cacheNodes[left->getValue()];
                cacheNodes[left->getValue()].setNode(left);
                cacheNodes[left->getValue()].setParent(cacheNodes[value].getNode());
                cacheNodes[left->getValue()].setGrandParent(cacheNodes[value].getParent());
                cacheNodes[left->getValue()].setLevel(cacheNodes[value].getLevel() + 1);
                cacheNodes[left->getValue()].setPathFromRoot(cacheNodes[value].getPathFromRoot());
                cacheNodes[left->getValue()].getPathFromRoot().push_back(left->getValue());
            }
            
            BinaryNode<T>* right = cacheNodes[value].getNode()->getRightChild();

            if (right != NULL) {
                cacheNodes[right->getValue()];
                cacheNodes[right->getValue()].setNode(right);
                cacheNodes[right->getValue()].setParent(cacheNodes[value].getNode());
                cacheNodes[right->getValue()].setGrandParent(cacheNodes[value].getParent());
                cacheNodes[right->getValue()].setLevel(cacheNodes[value].getLevel() + 1);
                cacheNodes[right->getValue()].setPathFromRoot(cacheNodes[value].getPathFromRoot());
                cacheNodes[right->getValue()].getPathFromRoot().push_back(right->getValue());
            }
        }
    } else {
        isFound = true;
    }
    
    if (isFound) {
        return cacheNodes[value];
    } else {
        return empty;
    }
}

template <typename T>
void BinaryTree<T>::getBinaryNodeMetaData(
        const T& value, 
        BinaryNodeMetaData<T>& metaData,
        bool& isFound,
        BinaryNode<T>* ptr,
        BinaryNode<T>* parent,
        BinaryNode<T>* grandParent,
        int level
    )
{
    if (ptr == NULL) return;

    metaData.getPathFromRoot().push_back(ptr->getValue());

    if (value == ptr->getValue()) {
        metaData.setNode(ptr);
        metaData.setParent(parent);
        metaData.setGrandParent(grandParent);
        metaData.setLevel(level);
        isFound = true;
    } else {
        getBinaryNodeMetaData(value, metaData, isFound, ptr->getLeft(), ptr, parent, level + 1);
        if (!isFound) {
            getBinaryNodeMetaData(value, metaData, isFound, ptr->getRight(), ptr, parent, level + 1);
        }
    }
    if (!isFound) metaData.getPathFromRoot().pop_back();
}

template <typename T>
void BinaryTree<T>::height(BinaryNode<T>* ptr, int& maxDepth, int depth) {
    if (ptr == NULL) return;
    ++depth;
    if (depth > maxDepth) maxDepth = depth;
    height(ptr->getLeft(), maxDepth, depth);
    height(ptr->getRight(), maxDepth, depth);
}

template <typename T>
void BinaryTree<T>::copyNodes(BinaryNode<T>* source, BinaryNode<T>*& destination, int& size) {

    if (source == NULL) return;

    ++size;

    destination = new BinaryNode<T>(source->getValue());
    BinaryNode<T>* left = NULL;
    BinaryNode<T>* right = NULL;

    copyNodes(source->getLeft(), left, size);
    copyNodes(source->getRight(), right, size);

    destination->setLeft(left);
    destination->setRight(right);
}

template <typename T>
void BinaryTree<T>::destroyNodes(BinaryNode<T>* ptr, int& size) {
    if (ptr == NULL) return;
    
    size++;
    destroyNodes(ptr->getLeft(), size);
    destroyNodes(ptr->getRight(), size);
    delete ptr;
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
std::unordered_map<T, int> BinaryTreeUtils::mapVector(const std::vector<T>& v) {
    std::unordered_map<T, int> result;
    for (int i = 0; i < v.size(); i++) {
        result[v[i]] = i;
    }
    return result;
}

