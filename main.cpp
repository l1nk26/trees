#include <iostream>
#include <unordered_map>
#include <Tree.hpp>
#include <containersOverload.hpp>

using namespace std;

int main() {

    unordered_map<string, list<string> > nodes;

    nodes["A"] = {"B", "C", "D"};
    nodes["B"] = {"E", "F"};
    nodes["C"] = {"G", "H"};
    nodes["G"] = {"I", "J"};
   
    Tree<string> tree(nodes);

    vector<vector<string> > levels = tree.allLevels();

    cout << levels << endl;

    return 0;
}
