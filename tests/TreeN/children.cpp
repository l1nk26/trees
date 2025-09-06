#include <Tree.hpp>
#include <unordered_map>
#include <list>
#include <cassert>
#include <iostream>

using namespace std;

int main() {

  unordered_map<string, list<string> > nodes = {
    {"A", {"B", "C", "D"}}, 
    {"B", {"E", "F"}}, 
    {"C", {"G", "H"}}, 
    {"G", {"I", "J"}}
  };
  Tree<string> tree(nodes);

  list<Tree<string> > childrenL = tree.children();
  vector<Tree<string> > children(childrenL.begin(), childrenL.end());

  assert(children.size() == 3);

  assert(children[0].rootValue() == "B");
  assert(children[1].rootValue() == "C");
  assert(children[2].rootValue() == "D");

  assert(children[0].getSize() == 3);
  assert(children[1].getSize() == 5);
  assert(children[2].getSize() == 1);

  vector<string> childrenOfB = children[0].childrenOf("B");
  assert(childrenOfB.size() == 2);
  assert(childrenOfB[0] == "E");
  assert(childrenOfB[1] == "F");

  return 0;
}
