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

  assert(!tree.haveParent("A"));
  assert(tree.haveParent("B"));
  assert(tree.haveParent("C"));
  assert(tree.haveParent("D"));
  assert(tree.haveParent("F"));
  assert(tree.haveParent("G"));
  assert(tree.haveParent("H"));
  assert(tree.haveParent("I"));
  assert(tree.haveParent("J"));

  assert(tree.parentOf("B") == "A");
  assert(tree.parentOf("C") == "A");
  assert(tree.parentOf("D") == "A");

  assert(tree.parentOf("E") == "B");
  assert(tree.parentOf("F") == "B");

  assert(tree.parentOf("G") == "C");
  assert(tree.parentOf("H") == "C");

  assert(tree.parentOf("J") == "G");
  assert(tree.parentOf("I") == "G");

  assert(!(tree.parentOf("B") == "B"));


  return 0;
}
