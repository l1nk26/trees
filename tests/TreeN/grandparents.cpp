#include <Tree.hpp>
#include <unordered_map>
#include <list>
#include <cassert>

using namespace std;

int main() {

  unordered_map<string, list<string> > nodes = {
    {"A", {"B", "C", "D"}}, 
    {"B", {"E", "F"}}, 
    {"C", {"G", "H"}}, 
    {"G", {"I", "J"}}
  };
  Tree<string> tree(nodes);

  assert(!tree.haveGrandParent("A"));
  assert(!tree.haveGrandParent("B"));
  assert(!tree.haveGrandParent("C"));
  assert(!tree.haveGrandParent("D"));
  assert(tree.haveGrandParent("F"));
  assert(tree.haveGrandParent("G"));
  assert(tree.haveGrandParent("H"));
  assert(tree.haveGrandParent("I"));
  assert(tree.haveGrandParent("J"));

  assert(tree.grandParentOf("E") == "A");
  assert(tree.grandParentOf("F") == "A");

  assert(tree.grandParentOf("G") == "A");
  assert(tree.grandParentOf("H") == "A");

  assert(tree.grandParentOf("J") == "C");
  assert(tree.grandParentOf("I") == "C");


  return 0;
}
