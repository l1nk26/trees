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

  vector<string> preorder = tree.preorder();
  vector<string> postorder = tree.postorder();
  vector<string> inorder = tree.inorder();

  vector<string> preorderTest = {"A", "B", "E", "F", "C", "G", "I", "J", "H", "D"};
  assert(preorder == preorderTest);

  vector<string> postorderTest = {"E", "F", "B", "I", "J", "G", "H", "C", "D", "A"};
  assert(postorder == postorderTest);

  vector<string> inorderTest = {"E", "B", "F", "A", "I", "G", "J", "C", "H", "D"};
  assert(inorder == inorderTest);

  return 0;
}
