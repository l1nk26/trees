#ifndef TREE
#define TREE
#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <TreeNode.hpp>

#define NOT_REPEATED_VALUES true

template <typename T>
class Tree {
    
    public:

        Tree();
        Tree(const Tree<T>& other);
        Tree(std::unordered_map<T, std::unordered_set<T> >& nodes);
        ~Tree();

        bool isEmpty();
        T& rootValue();

        std::vector<Tree<T> > children();

        std::vector<T> preorder();
        std::vector<T> inorder();
        std::vector<T> postorder();
        std::vector<T> byLevels();

        int getSize();

        void clear();

        int height();

        std::vector<T> getLeaves();
        
        bool exists(const T& value);
        
        T lowestCommonAncestor(const T& value1, const T& value2);
        
        std::vector<T> getPathTo(const T& value);
        
        Tree<T> mirror();
        
        void insertTree(const Tree<T>& tree);

        Tree<T> getSubtreeByValue(const T& value);
        Tree<T> getSubtreeByPosition(int position);
        void removeSubtree(int position);

        T parentOf(const T& value);
        T grandParentOf(const T& value);
        std::vector<T> cousinsOf(const T& value);
        std::vector<T> siblingsOf(const T& value);
        std::vector<T> childrenOf(const T& value);

        bool haveParent(const T& value);
        bool haveGrandParent(const T& value);

        std::vector<T> level(int index);

        bool isomorphic(const Tree<T>& other);

        bool operator==(Tree<T>& other);

        bool operator!=(Tree<T>& other);

        Tree<T>& operator=(const Tree<T>& other);

        template <typename U>
        friend std::ostream& operator<<(std::ostream& os, const Tree<U>& tree);

    private:
        TreeNode<T>* root;
        int size;
        TreeNode<T>* cacheNode;
        TreeNode<T>* cacheParent;
        TreeNode<T>* cacheGrandParent;

        TreeNode<T>* findNode(const T& value);
        TreeNode<T>* findNode(const T& value, TreeNode<T>* ptr);
        TreeNode<T>* findNodeByPosition(int position);

        void copyNodes(TreeNode<T>* node, TreeNode<T>*& copy, int& size);
        void destroyNodes(TreeNode<T>* node);

        void getLeaves(TreeNode<T>* node, std::list<T>& result);

        void preorder(TreeNode<T>* node, std::list<T>& result);
        void inorder(TreeNode<T>* node, std::list<T>& result);
        void postorder(TreeNode<T>* node, std::list<T>& result);

        TreeNode<T>* mirror(TreeNode<T>* ptr);

        void lowestCommonAncestor(TreeNode<T>* ptr, const T& value1, const T& value2, int& found, T*& ancestor);

        void getPathTo(const T& value, TreeNode<T>* ptr, std::list<T>& path, bool& isFound);

        bool isomorphic(TreeNode<T>* ptr, TreeNode<T>* ptrOther);

        T findRoot(std::unordered_map<T, std::unordered_set<T> > nodes);

        void makeTreeFromMap(TreeNode<T>* parent, std::unordered_set<T>& children, std::unordered_map<T, std::unordered_set<T> >& nodes);
};

#include "Tree.cpp"

#endif