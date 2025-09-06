#include <iostream>
#include <list>
#include <Tree.hpp>
#include <containersOverload.hpp>
#include <cassert>

using namespace std;

int main() {

    unordered_map<string, list<string> > nodes;

    nodes["A"] = {"B", "C", "D"};
    nodes["B"] = {"E", "F"};
    nodes["C"] = {"G", "H"};
    nodes["G"] = {"I", "J"};
   
    Tree<string> tree(nodes);

    vector<vector<string> > levels = tree.allLevels();

    assert(levels.size() == 4);

    assert(tree.level(0) == levels[0]);
    assert(tree.level(1) == levels[1]);
    assert(tree.level(2) == levels[2]);
    assert(tree.level(3) == levels[3]);

    return 0;
}
