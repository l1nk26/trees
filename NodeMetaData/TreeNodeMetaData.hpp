#ifndef TREE_NODE_META_DATA
#define TREE_NODE_META_DATA
#include <TreeNode.hpp>
#include <list>
#include <cstddef>

template <typename T>
class TreeNodeMetaData {
  
    public:
        TreeNodeMetaData(TreeNode<T>* node = NULL, TreeNode<T>* parent = NULL, TreeNode<T>* grandParent = NULL, int level = -1) : 
            node(node), 
            parent(parent), 
            grandParent(grandParent),
            level(level)
        {}

        TreeNode<T>* getNode() { return node;}
        TreeNode<T>* getParent() { return parent;}
        TreeNode<T>* getGrandParent() { return grandParent;}
        int getLevel() { return level;}
        
        std::list<T>& getPathFromRoot() { return pathFromRoot;}

        void setNode(TreeNode<T>* node) { this->node = node;}
        void setParent(TreeNode<T>* parent) { this->parent = parent;}
        void setGrandParent(TreeNode<T>* grandParent) { this->grandParent = grandParent;}
        void setLevel(int level) { this->level = level;}

        void setPathFromRoot(std::list<T>& pathFromRoot) { this->pathFromRoot = pathFromRoot;}
    private:
        TreeNode<T>* node;
        TreeNode<T>* parent;
        TreeNode<T>* grandParent;

        int level;

        std::list<T> pathFromRoot;
};
#endif
