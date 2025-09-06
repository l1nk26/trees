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

  assert(tree.exists("A"));
  assert(tree.exists("B"));
  assert(tree.exists("C"));
  assert(tree.exists("D"));
  assert(tree.exists("E"));
  assert(tree.exists("F"));
  assert(tree.exists("G"));
  assert(tree.exists("H"));
  assert(tree.exists("I"));
  assert(tree.exists("J"));

  assert(tree.exists("A"));
  assert(tree.exists("B"));
  assert(tree.exists("C"));
  assert(tree.exists("D"));
  assert(tree.exists("E"));
  assert(tree.exists("F"));
  assert(tree.exists("G"));
  assert(tree.exists("H"));
  assert(tree.exists("I"));
  assert(tree.exists("J"));

  assert(!tree.exists("1"));
  assert(!tree.exists("2"));
  assert(!tree.exists("3"));
  assert(!tree.exists("4"));
  assert(!tree.exists("5"));

  return 0;
}
