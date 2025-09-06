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

  vector<string> testPath = {"A", "B", "E"};
  assert(tree.pathTo("E") == testPath);

  vector<string> testPath2 = {"A", "C", "G", "I"};
  assert(tree.pathTo("I") == testPath2);

  return 0;
}
