#include <Tree.hpp>
#include <unordered_map>
#include <list>
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

  vector<string> leaves = tree.leaves();
  vector<string> testLeaves = {"E", "F", "I", "J", "H", "D"};
  assert(leaves == testLeaves);

  return 0;
}
