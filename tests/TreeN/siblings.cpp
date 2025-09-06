#include <Tree.hpp>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <iostream>
#include <containersOverload.hpp>

using namespace std;

int main() {

  unordered_map<string, list<string> > nodes = {
    {"A", {"B", "C", "D"}}, 
    {"B", {"E", "F"}}, 
    {"C", {"G", "H"}}, 
    {"G", {"I", "J"}}
  };
  Tree<string> tree(nodes);

  vector<string> cousins = tree.siblingsOf("B");
  assert(cousins.size() == 2);

  vector<string> testSiblings = {"C", "D"};

  assert(cousins == testSiblings);

  return 0;
}
