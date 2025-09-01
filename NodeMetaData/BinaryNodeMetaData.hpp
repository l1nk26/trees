#ifndef BINARY_NODE_META_DATA
#define BINARY_NODE_META_DATA
#include <BinaryNode.hpp>
#include <list>
#include <cstddef>

template <typename T>
class BinaryNodeMetaData {
  
    public:
        BinaryNodeMetaData(BinaryNode<T>* node = NULL, BinaryNode<T>* parent = NULL, BinaryNode<T>* grandParent = NULL, int level = -1) : 
            node(node), 
            parent(parent), 
            grandParent(grandParent),
            level(level)
        {}

        BinaryNode<T>* getNode() { return node;}
        BinaryNode<T>* getParent() { return parent;}
        BinaryNode<T>* getGrandParent() { return grandParent;}
        int getLevel() { return level;}
        
        std::list<T>& getPathFromRoot() { return pathFromRoot;}

        void setNode(BinaryNode<T>* node) { this->node = node;}
        void setParent(BinaryNode<T>* parent) { this->parent = parent;}
        void setGrandParent(BinaryNode<T>* grandParent) { this->grandParent = grandParent;}
        void setLevel(int level) { this->level = level;}

        void setPathFromRoot(std::list<T>& pathFromRoot) { this->pathFromRoot = pathFromRoot;}
    private:
        BinaryNode<T>* node;
        BinaryNode<T>* parent;
        BinaryNode<T>* grandParent;
        int level;

        std::list<T> pathFromRoot;
};
#endif
