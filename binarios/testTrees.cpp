
#include <cassert>
#include <list>
#include <iostream>
#include "BinaryTree.hpp"

void printInt(const int& value) {
    std::cout << value << " ";
}

int main() {
    // 1. Árbol vacío
    BinaryTree<int> tree;
    assert(tree.isEmpty());
    assert(tree.getSize() == 0);
    assert(tree.getHeight() == -1);

    // 2. Construcción desde inorden y preorden
    std::list<int> inorder  = {4, 2, 5, 1, 6, 3, 7};
    std::list<int> preorder = {1, 2, 4, 5, 3, 6, 7};
    tree.makeFromInorderPreorder(inorder, preorder);
    assert(!tree.isEmpty());
    assert(tree.getSize() == 7);
    assert(tree.getHeight() == 2);


    // 3. Comparación de árboles
    BinaryTree<int> tree2;
    std::list<int> inorder2  = {4, 2, 5, 1, 6, 3, 7};
    std::list<int> preorder2 = {1, 2, 4, 5, 3, 6, 7};
    tree2.makeFromInorderPreorder(inorder2, preorder2);
    assert(tree == tree2);

    // 4. Subárbol izquierdo
    BinaryTree<int> leftSubtree;
    tree.makeSubTreeFromLeft(leftSubtree);
    assert(leftSubtree.getSize() == 3);

    // 5. Subárbol derecho
    BinaryTree<int> rightSubtree;
    tree.makeSubTreeFromRight(rightSubtree);
    assert(rightSubtree.getSize() == 3);

    // 6. Limpieza
    tree.clear();
    assert(tree.isEmpty());
    assert(tree.getSize() == 0);

    std::cout << "Todos los tests pasaron correctamente." << std::endl;
    return 0;
}
