#include <iostream>
#include <unordered_map>
#include <Tree.hpp>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
  os << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
      os << *it << ", ";
  }
  if (!v.empty()) {
      os << "\b\b";
  }
  os << "]";
  return os;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
  os << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
      os << *it << ", ";
  }
  if (!v.empty()) {
      os << "\b\b";
  }
  os << "]";
  return os;
}

int main() {

    unordered_map<string, unordered_set<string> > nodes;

    nodes["A"] = {"B", "C", "D"};
    nodes["B"] = {"E", "F"};
   
    Tree<string> tree(nodes);

    vector<vector<string> > levels = tree.allLevels();

    cout << levels;

    return 0;
}
