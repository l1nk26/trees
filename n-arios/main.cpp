#include <iostream>
#include <unordered_map>
#include <Tree.hpp>

using namespace std;

int main() {

    unordered_map<string, unordered_set<string> > nodes;

    nodes["A"] = {"B", "C", "D"};
    nodes["B"] = {"E", "F"};
   

    Tree<string> tree(nodes);

    cout << tree;
    
    
    return 0;
}