#include <Tree.hpp>
#include <TreeNode.hpp>
#include <list>
#include <queue>
#include <vector>
#include <cstddef>
#include <stdexcept>

template <typename T>
Tree<T>::Tree() : 
    root(NULL), 
    size(0), 
    cacheNode(NULL),
    cacheParent(NULL),
    cacheGrandParent(NULL)
{}

template <typename T>
Tree<T>::Tree(const Tree<T>& other) {
    int _size = 0;
    copyNodes(other.root, root, _size);
    size = other.size;
    cacheNode = NULL;
    cacheParent = NULL;
    cacheGrandParent = NULL;
}

template <typename T>
Tree<T>::Tree(std::unordered_map<T, std::unordered_set<T> >& nodes) : Tree() {
    T rootValue = findRoot(nodes);

    root = new TreeNode<T>(rootValue);
    ++size;

    makeTreeFromMap(root, nodes[rootValue], nodes);
}

template <typename T>
Tree<T>::~Tree() {
    destroyNodes(root);
}

template <typename T>
bool Tree<T>::isEmpty() {
    return size == 0;
}

template <typename T>
T& Tree<T>::rootValue() {
    if (isEmpty()) {
        throw std::runtime_error("Tree is empty");
    }
    return root->getValue();
}

template <typename T>
std::vector<Tree<T> > Tree<T>::children() {

    std::vector<T>result;
    std::list<Tree<T> > aux;
    
    TreeNode<T>* child = root->getLeftChild();

    while (child != NULL) {
        Tree<T> subtree;
        copySubtree(child, subtree.root, subtree.size);
        child = child->getRightSibling();
        aux.push_back(subtree);
    }

    return result;
}

template <typename T>
std::vector<T> Tree<T>::preorder() {
    std::list<T> aux;
    preorder(root, aux);
    std::vector<T> result(aux.begin(), aux.end());
    return result;
}

template <typename T>
std::vector<T> Tree<T>::inorder() {
    std::list<T> aux;
    inorder(root, aux);
    std::vector<T> result(aux.begin(), aux.end());
    return result;
}

template <typename T>
std::vector<T> Tree<T>::postorder() {
    std::list<T> aux;
    postorder(root, aux);
    std::vector<T> result(aux.begin(), aux.end());
    return result;
}

template <typename T>
std::vector<T> Tree<T>::byLevels() {
    std::list<T> aux;

    std::queue<TreeNode<T>*> q;
    int levelSize;

    if (root != NULL) {
        q.push(root);
    }

    while (!q.empty()) {
        levelSize = q.size();

        for (int i = 0; i < levelSize; ++i) {
            TreeNode<T>* current = q.front();
            q.pop();
            aux.push_back(current->getValue());

            TreeNode<T>* child = current->getLeftChild();
            while (child != NULL) {
                q.push(child);
                child = child->getRightSibling();
            }
        }
    }

    std::vector<T> result(aux.begin(), aux.end());

    return result;
}

template <typename T>
int Tree<T>::getSize() {
    return size;
}

template <typename T>
void Tree<T>::clear() {
    destroyNodes(root);
    root = NULL;
    size = 0;
    cacheNode = NULL;
    cacheGrandParent = NULL;
    cacheParent = NULL;
}

template <typename T>
int Tree<T>::height() {
    int result = -1;
    TreeNode<T>* current = root;

    while (current != NULL) {
        result++;
        current = current->getLeftChild();
    }

    return result;
}

template <typename T>
std::vector<T> Tree<T>::getLeaves() {
    std::list<T> aux;
    getLeaves(root, aux); 
    std::vector<T> result;  
    return result;
}

template <typename T>
bool Tree<T>::exists(const T& value) {
    return findNode(value) != NULL;
}

template <typename T>
T Tree<T>::lowestCommonAncestor(const T& value1, const T& value2) {
    int found = 0;
    TreeNode<T>* ancestor = NULL;
    lowestCommonAncestor(root, value1, value2, found, ancestor);
    if (ancestor == NULL) {
        throw std::runtime_error("lowestCommonAcestor: alguno de los 2 valores no existe en el arbol\n");
    } 
    return ancestor->getValue();
}

template <typename T>
std::vector<T> Tree<T>::getPathTo(const T& value) {
    std::list<T> aux;
    bool isFound = false;
    getPathTo(value, aux, isFound);
    std::vector<T> result(aux.begin(), aux.end());
    return result;
}

template <typename T>
Tree<T> Tree<T>::mirror() {

    Tree<T> result;
    
    mirror(result.root, root);
    result.size = size;

    return result;
}

template <typename T>
void Tree<T>::insertTree(const Tree<T>& tree) {
    TreeNode<T>* newNodeOfSubTree = NULL;
    TreeNode<T>* aux;
    int _size = 0;
    copyNodes(tree.root, newNodeOfSubTree, _size);
    if (root == NULL) {
        root = newNodeOfSubTree;
    } else if (root->getLeftChild() == NULL) {
        root->setLeftChild(newNodeOfSubTree);
    } else {
        aux = root->getLeftChild();
        while (aux->getRightSibling() != NULL) {
            aux = aux->getRightSibling();
        }
        aux->setRightSibling(newNodeOfSubTree);
    }
}

template <typename T>
Tree<T> Tree<T>::getSubtreeByValue(const T& value) {
    Tree<T> result;
    TreeNode<T>* ptrValue = findNode(value);
    int size = 0;

    copyNodes(ptrValue, result, size);

    result->size = size;

    return result;
}

template <typename T>
Tree<T> Tree<T>::getSubtreeByPosition(int position) {
    Tree<T> result;
    int i = 0;
    TreeNode<T>* ptr;
    int size = 0;

    if (root != NULL) {
        ptr = root;
        while (ptr->getLeftChild() != NULL && i < position) {
            ptr = ptr->getLeftChild();
            i++;
        }
        if (i == position) {
            copyNodes(ptr, result.root, size);
            result.size = size;
        }
    }

    return result;
}

template <typename T>
void Tree<T>::removeSubtree(int position) {
    TreeNode<T>* ptr;
    int i = 0;
    ptr = root;

    
    if (position == 0) {
        clear();
    } else if (root != NULL){

        while (ptr->getLeftChild() != NULL && i + 1 < position) {
            ptr = ptr->getLeftChild();
            i++;
        }
        if (i + 1 == position && ptr->getLeftChild() != NULL) {
            destroyNodes(ptr->getLeftChild);
            ptr->setLeftChild(NULL);
        }
    }
    cacheGrandParent = NULL;
    cacheNode = NULL;
    cacheParent = NULL;
}

template <typename T>
T Tree<T>::parentOf(const T& value) {
    TreeNode<T>* node = findNode(value);
    if (node == NULL) {
        throw std::runtime_error("el nodo no existe");
    } else if (cacheParent == NULL) {
        throw std::runtime_error("el padre no existe");
    }
    return cacheParent->getValue();
}


template <typename T>
T Tree<T>::grandParentOf(const T& value) {
    TreeNode<T>* node = findNode(value, root, NULL);
    if (node == NULL) {
        throw std::runtime_error("el nodo no existe o no tiene abuelo");
    } else if (cacheGrandParent == NULL) {
        throw std::runtime_error("el abuelo no existe");
    }
    return cacheGrandParent->getValue();
}

template <typename T>
std::vector<T> Tree<T>::cousinsOf(const T& value) {
    TreeNode<T>* node = findNode(value);
    std::list<T> aux;

    if (node != NULL && cacheGrandParent != NULL) {
        TreeNode<T>* uncle = cacheGrandParent->getLeftChild();
        while (uncle != NULL) {
            if (uncle == cacheParent) continue;

            TreeNode<T>* cousin = uncle->getLeftChild();
            while (cousin != NULL) {
                aux.push_back(cousin->getValue());
                cousin = cousin->getRightSibling();
            }
            uncle = uncle->getRightSibling();
        }
    }
    std::vector<T> result(aux.begin(), aux.end());

    return result;
}

template <typename T>
std::vector<T> Tree<T>::siblingsOf(const T& value) {
    TreeNode<T>* node = findNode(value);
    std::list<T> aux;

    if (node != NULL && cacheParent != NULL) {
        TreeNode<T>* sibling = cacheParent->getLeftChild();
        while (sibling != NULL) {
            aux.push_back(sibling->getValue());
            sibling = sibling->getRightSibling();
        }
    }
    std::vector<T> result(aux.begin(), aux.end());

    return result;
}

template <typename T>
bool Tree<T>::haveParent(const T& value) {
    TreeNode<T>* node = findNode(value);
    return (node != NULL && cacheGrandParent != NULL);
}

template <typename T>
bool Tree<T>::haveGrandParent(const T& value) {
    TreeNode<T>* node = findNode(value);

    return (node != NULL && cacheGrandParent != NULL);
}

template <typename T>
std::vector<T> Tree<T>::level(int index) {
    TreeNode<T>* ptr = root;
    std::list<T> aux;
    int i = 0;

    while (ptr != NULL && i < index) {
        ptr = ptr->getLeftChild();
    }
    while (ptr != NULL) {
        aux.push_back(ptr->getValue());
        ptr = ptr->getRightSibling();
    }
    std::vector<T> result(aux.begin(), aux.end());

    return result;
}

template <typename T>
bool Tree<T>::operator==(Tree<T>& other) {
    return preorder() == other.preorder();
}

template <typename T>
bool Tree<T>::operator!=(Tree<T>& other) {
    return !(*this == other);
}

template <typename T>
Tree<T>& Tree<T>::operator=(const Tree<T>& other) {
    if (this == &other) {
        return *this;
    }

    this->clear();
    int _size = 0;

    copyNodes(other.root, this->root, _size);
    this->size = other.size;
    cacheGrandParent = NULL;
    cacheNode = NULL;
    cacheParent = NULL;
}

template <typename T>
TreeNode<T>* Tree<T>::findNode(const T& value) {

    TreeNode<T>* node = NULL;

    if (NOT_REPEATED_VALUES && cacheNode != NULL && cacheNode->getValue() == value) {
        node = cacheNode;
    } else {
        cacheGrandParent = NULL;
        cacheParent = NULL;
        cacheNode = NULL;

        node = findNode(value, root);
    }

    return node;
}

template <typename T>
TreeNode<T>* Tree<T>::findNode(const T& value, TreeNode<T>* ptr) {

    TreeNode<T>* node = NULL;
    
    if (ptr != NULL) {
        if (ptr->getValue() == value) {
            node = ptr;
            cacheNode = node;
        } else {
            cacheGrandParent = cacheParent;
            cacheParent = ptr;
            TreeNode<T>* child = ptr->getLeftChild();
            while (child != NULL && node != NULL) {
                node = findNode(value, child);
                child = child->getRightSibling();
            }
        }
    }

    return node;
}

template <typename T>
TreeNode<T>* Tree<T>::findNodeByPosition(int position) {
    TreeNode<T>* result = root;
    int i = 0;

    while (result != NULL && i < position) {
        result = result->getLeftChild();
        i++;
    }

    return result;
}

template <typename T>
void Tree<T>::copyNodes(TreeNode<T>* root, TreeNode<T>*& copy, int& size) {

    if (root != NULL) {
        copy = new TreeNode<T>(root->getValue());
        ++size;

        TreeNode<T>* child = root->getLeftChild();
        TreeNode<T>* childCopy;
        TreeNode<T>* dummy = new TreeNode<T>();
        TreeNode<T>* current = dummy;

        while (child != NULL) {
            copyNodes(child, childCopy, size);
            current->setRightSibling(childCopy);
            current = current->getRightSibling();
            child = child->getRightSibling();
        }

        copy->setLeftChild(dummy->getRightSibling());
        delete dummy;
    }
}

template <typename T>
void Tree<T>::destroyNodes(TreeNode<T>* root) {
    if (root == NULL) return;

    destroyNodes(root->getLeftChild());
    destroyNodes(root->getRightSibling());
    delete root;
}

template <typename T>
void Tree<T>::getLeaves(TreeNode<T>* ptr, std::list<T>& result) {

    if (ptr == NULL) return;
    

    if (ptr->getLeftChild() == NULL) {
        result.push_back(ptr->getValue());
    } else {
        getLeaves(ptr->getLeftChild);
        getLeaves(ptr->getRightSibling);
    }
}

template <typename T>
void Tree<T>::preorder(TreeNode<T>* ptr, std::list<T>& result) {
    
    if (ptr == NULL) return;

    result.push_back(ptr->getValue());
    preorder(ptr->getLeftChild(), result);
    preorder(ptr->getRightSibling(), result);
}

template <typename T>
void Tree<T>::inorder(TreeNode<T>* ptr, std::list<T>& result) {

    if (ptr == NULL) return;
    

    inorder(ptr->getLeftChild(), result);
    result.push_back(ptr->getValue());
    inorder(ptr->getRightSibling(), result);
}

template <typename T>
void Tree<T>::postorder(TreeNode<T>* ptr, std::list<T>& result) {

    if (ptr == NULL) return;
    

    postorder(ptr->getLeftChild(), result);
    postorder(ptr->getRightSibling(), result);    
    result.push_back(ptr->getValue());
}

template <typename T>
TreeNode<T>* Tree<T>::mirror(TreeNode<T>* ptr) {

    if (ptr == NULL) return NULL;

    TreeNode<T>* newNode = new TreeNode<T>(ptr->getValue());
    TreeNode<T>* child = ptr->getLeftChild();
    TreeNode<T>* dummy = new TreeNode<T>();
    TreeNode<T>* current = NULL;
    

    while (child != NULL) {
        current = mirror(child);
        current->setRightSibling(dummy->getRightSibling());
        dummy->setRightSibling(current);

        child = child->getRightSibling();
    }
    newNode->setLeftChild(current);
    free(dummy);

    return newNode;
}

template <typename T>
void Tree<T>::lowestCommonAncestor(TreeNode<T>* ptr, const T& value1, const T& value2, int& found, T*& ancestor) {

    if (ptr == NULL) return;

    TreeNode<T>* child = ptr->getLeftChild();

    while (child != NULL && found < 2) {
        lowestCommonAncestor(child, value1, value2, found, ancestor);
        child = child->getRightSibling();
    }

    if (found == 2) {
        ancestor = ptr;
        found = 3;
    } else if (ptr->getValue() == value1 || ptr->getValue() == value2) {
        ++found;
    }
}

template <typename T>
void Tree<T>::getPathTo(const T& value, TreeNode<T>* ptr, std::list<T>& path, bool& isFound) {
    
    if (ptr == NULL) return;

    path.push_back(ptr->getValue());

    if (ptr->getValue() == value) {
        isFound = true;
    } else {
        TreeNode<T>* child = ptr->getLeftChild();
        while (child != NULL && !isFound) {
            getPathTo(value, child, path, isFound);
            child = child->getRightSibling();
        }
    }
    
}

template <typename T>
bool Tree<T>::isomorphic(const Tree<T>& other) {
    return isomorphic(root, other->root);
}

template <typename T>
bool Tree<T>::isomorphic(TreeNode<T>* ptr, TreeNode<T>* ptrOther) {
    
    if (ptr == NULL || ptrOther == NULL) return ptr == ptrOther;

    TreeNode<T>* child = ptr->getLeftChild();
    TreeNode<T>* childOther = ptrOther->getLeftChild();
    bool result = true;

    while (child != NULL && childOther != NULL && result) {
        result = isomorphic(child->getRightSibling(), childOther->getRightSibling());
        child = child->getRightSibling();
        childOther = childOther->getRightSibling();
    }

    return result && child == childOther;
}

template <typename T>
T Tree<T>::findRoot(std::unordered_map<T, std::unordered_set<T> > nodes) {

    bool isRoot = false;
    T root;

    auto it = nodes.begin();
    while (it != nodes.end() && !isRoot) {
        auto that = nodes.begin();
        isRoot = true;
        while (that != nodes.end() && isRoot) {

            if (that->second.find(it->first) != that->second.end()) {
                isRoot = false;
            }

            ++that;
        }
        if (isRoot) {
            root = it->first;
        }
    
        ++it;
    }

    return root;
}

template <typename T>
void Tree<T>::makeTreeFromMap(TreeNode<T>* parent, std::unordered_set<T>& children, std::unordered_map<T, std::unordered_set<T> >& nodes) {

    if (children.empty()) return;
    
    for (auto it = children.begin(); it != children.end(); ++it) {
        TreeNode<T>* child = new TreeNode<T>(*it);
        addChild(parent, child);
        ++size;
        if (nodes.find(*it) == nodes.end()) continue;
         
        makeTreeFromMap(child, nodes[*it], nodes);
    }
}

template <typename T>
void addChild(TreeNode<T>* parent, TreeNode<T>* child) {
    if (parent->getLeftChild() == NULL) {
        parent->setLeftChild(child);
    } else {
        TreeNode<T>* current = parent->getLeftChild();
        while (current->getRightSibling() != NULL) {
            current = current->getRightSibling();
        }
        current->setRightSibling(child);
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Tree<T>& tree) {
    os << "Tree(size=" << tree.size << "): ";
    if (tree.root == NULL) {
        os << "Empty";
    } else {
        std::queue<TreeNode<T>*> q;
        q.push(tree.root);
        while (!q.empty()) {
            TreeNode<T>* current = q.front();
            q.pop();
            os << "\n" << *current;
            TreeNode<T>* child = current->getLeftChild();
            while (child != NULL) {
                q.push(child);
                child = child->getRightSibling();
            }
        }
    }
    return os;
}