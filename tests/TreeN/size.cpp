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

  assert(tree.getSize() == 10);
  tree.clear();
  assert(tree.isEmpty());
  assert(tree.getSize() == 0);

  return 0;
}
