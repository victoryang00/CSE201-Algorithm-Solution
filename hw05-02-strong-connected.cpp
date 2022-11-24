#include <bits/stdc++.h>
#include <type_traits>
using namespace std;

class Node;
int dfs(Node *i, int currentTime);
bool check_unvisited(Node *u);
class Node {
public:
  int entrytime;
  int finishTime;
  enum state { unvisited, in_progress, all_done };
  state currState;
  list<Node *> *neighbors;
  int id;

  Node(int id) {
    this->neighbors = new list<Node *>();
    this->currState = unvisited;
    this->id = id;
  };
  template <typename... Rest> void addEdge(Node *e, Rest &&...args) {
    static_assert((std::is_constructible_v<Node *, Rest &&> && ...));
    this->neighbors->push_back(e);
    (this->neighbors->push_back(std::forward<Rest>(args)), ...);
  };
  Node *get_transpose() {
    auto g = new Node(this->id);
    for (int i = 0; i < this->neighbors->size(); i++) {
      for (int j = 0; j < this->neighbors[j].size(); j++) {
        std::list<Node *> l; // look, no pointers!
        auto l_front = this->neighbors->begin();

        std::advance(l_front, i);
        g->addEdge(&(*l_front)[j]);
      }
    }
    return g;
  }
  bool isSC(vector<Node *> all_nodes) {
    dfs(this, 0);

    for (auto v : all_nodes)
      if (check_unvisited(v)) {
        return false;
      }

    auto g = this->get_transpose();

    dfs(g, 0);
    for (auto v : all_nodes)
      if (check_unvisited(v)) {
        return false;
      }
  }
};

bool check_unvisited(Node *u) {
  if (u->currState == Node::unvisited) {
    return true;
  }
  return false;
}
int dfs(Node *u, int currentTime) {
  u->entrytime = currentTime;
  currentTime++;
  u->currState = Node::in_progress;
  for (auto v : *u->neighbors) {
    if (v->currState == Node::unvisited) {
      currentTime = dfs(v, currentTime);
      currentTime++;
    }
  }
  u->finishTime = currentTime;
  u->currState = Node::all_done;
  return currentTime;
}

int main() {
  auto a = Node(1);
  auto b = Node(2);
  auto c = Node(3);
  auto d = Node(4);
  auto e = Node(5);
  a.addEdge(&b, &c);
  b.addEdge(&e);
  c.addEdge(&d);
  d.addEdge(&e);
  auto v = {&a, &b, &c, &d, &e};
  dfs(&a, 0);
  std::cout << c.isSC(v) << "\n";
}